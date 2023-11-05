//ESP32PinballOS
//Version 0.0.2
//0.0.2 - Updating to account for differnet PCB design.  The shift registers are connected differently
//a pair of inouts shared for switch matrix and audio, 
//and then a single IC for switch matrix out, 
//one IC for audio and two for outputs to solenoids
#include <Arduino.h>
//Over The Air Updater 
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "setupSPIFFS.h"

#include "jsonSettings.h"
//these files set up switches and colis - later it would be good to do this based on a config file - this means we can have a web ui that gives configuration away from code
#include "userSettings.h"

int WEBHz = 0;
int CMOHz = 0;
int DisplayControllerHz = 0;


int MachineState = 0; //this can be Bootup-0, Atract-1, Game-2, End Game-3, End Ball-4
int lastMachineState = 0;
bool forceDisplayUpdate = false;
bool WifiConnected = false;
String ScoreboardTText = "";
String ScoreboardTRText = "";
String ScoreboardTLText = "";
String ScoreboardBText = "";

#include "CoreMachineOperations.h"
#include "DMDDisplay.h"
#include "WebOperations.h"
#include "machineState.h"

void setup() {
  // put your setup code here, to run once:
  // Setup Serial Monitor
  Serial.begin(115200);

  //Need to set up LEDs, flippers, high power relay

  pinMode(flipper1Pin, INPUT);
  
  //attachInterrupt(flipper1Pin, fireFlipper1, RISING);
  //attachInterrupt(flipper1Pin, releaseFlipper1, FALLING);
  pinMode(flipper2Pin, INPUT);

  //attachInterrupt(flipper2Pin, fireFlipper2, RISING);
  //attachInterrupt(flipper2Pin, releaseFlipper2, FALLING);

  pinMode(hvrPin, OUTPUT);
  //turn off High Voltage Relay
  digitalWrite(hvrPin, LOW);

  // Setup pins for Switch Matrix Out
  pinMode(osr1latchPin, OUTPUT);
  pinMode(osr1clockPin, OUTPUT);
  pinMode(osr1dataPin, OUTPUT);

  // Setup pin for Audio Out
  pinMode(osr2latchPin, OUTPUT);
  pinMode(osr2clockPin, OUTPUT);
  pinMode(osr2dataPin, OUTPUT);
  
  // Setup pins for Coil Out
  pinMode(osr3latchPin, OUTPUT);
  pinMode(osr3clockPin, OUTPUT);
  pinMode(osr3dataPin, OUTPUT);
  
  // Setup 74HC165 connections for SMatrix in and Audio in
  pinMode(isrload, OUTPUT);
  pinMode(isrclockEnablePin, OUTPUT);
  pinMode(isrclockIn, OUTPUT);
  pinMode(isrdataIn, INPUT);
  
  // Set all outputs to zero
  //Open latch
  digitalWrite(osr1latchPin, LOW);
  digitalWrite(osr2latchPin, LOW);
  digitalWrite(osr3latchPin, LOW);
  // Shift out the bits
  shiftOut(osr1dataPin, osr1clockPin, MSBFIRST, 0);
  shiftOut(osr2dataPin, osr2clockPin, MSBFIRST, 0);
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, 0);
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, 0); // 2 registers so we have to shift both
  // Close Latch
  digitalWrite(osr1latchPin, HIGH);
  digitalWrite(osr2latchPin, HIGH);
  digitalWrite(osr3latchPin, HIGH);


  Serial.println("Flushing the shift registers.");
  write_sr_matrix(); // flush out the shift registers
  write_sr_audio(); // flush out the shift registers
  write_sr_coils(); // flush out the shift registers
  Serial.println(".");
  read_sr(); // read the shift registers. get rid of any spurious crap on power up.
  Serial.println(".");
  delay(200);
  Serial.println(".");
  write_sr_matrix(); // flush out the shift registers
  write_sr_audio(); // flush out the shift registers
  write_sr_coils(); // flush out the shift registers
  Serial.println(".");
  read_sr(); // read again after a short delay
  Serial.println(".");
  delay(1000);
  Serial.println("done.");
  Serial.println("Now read settings files...");
  Serial.println("Starting SPIFFS"); // Alan - Not needed at present but we WILL use it later
  
  // Create a eSPIFFS class
  #ifndef USE_SERIAL_DEBUG_FOR_eSPIFFS


    // Check Flash Size - Always try to incorrperate a check when not debugging to know if you have set the SPIFFS correctly
    if (!fileSystem.checkFlashConfig()) {
      Serial.println("Flash size was not correct!");
      if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
          Serial.println("SPIFFS Mount Failed");
          Serial.println("Formatting the file system, please wait for a few minutes, I will reboot");
          return;
      }
      listDir(SPIFFS, "/", 0);
      writeFile(SPIFFS, "/hello.txt", "Hello ");
      appendFile(SPIFFS, "/hello.txt", "World!\r\n");
      readFile(SPIFFS, "/hello.txt");
      renameFile(SPIFFS, "/hello.txt", "/foo.txt");
      readFile(SPIFFS, "/foo.txt");
      deleteFile(SPIFFS, "/foo.txt");
      testFileIO(SPIFFS, "/test.txt");
      deleteFile(SPIFFS, "/test.txt");
      Serial.println( "Test complete" );
      ESP.restart();
    }else
    {
      //load config or create first one
      fileSystem.openFromFile(localConfigFile, configJsonDocument);  // This will open the value of writeToFlash

      if (configJsonDocument.isNull()) {
        Serial.println();
        Serial.println("** Need to set up our config files - this is a clean install **");
        listDir(SPIFFS, "/", 0);
        createConfigFiles();
      } else {
        Serial.println();
        Serial.println("**  Need to open up last saved config files **");
        listDir(SPIFFS, "/", 0);
        openConfigFiles();
      }
    }
  #else
    // Create fileSystem with debug output
    eSPIFFS fileSystem(&Serial);  // Optional - allow the methods to print debug
  #endif

  Serial.print("Setup running on core ");
  Serial.println(xPortGetCoreID());

  xTaskCreatePinnedToCore(
    MonitorSwitchesAndRegisterFunction,
    "MonitorSwitchesAndRegister",
    10000,
    NULL,
    1,
    &MonitorSwitchesAndRegister,
    0);

  xTaskCreatePinnedToCore(
    WebOperationsFunction,
    "WebOperationsTask",
    10000,
    NULL,
    2,
    &WebOperationsTask,
    1);


  // setup dot matrix display stuff
  xTaskCreatePinnedToCore(
    DisplayBootModeFunction,
    "DisplayBootMode",
    10000,
    NULL,
    99,
    &DisplayBootMode,
    1);
  

// setup dot matrix display stuff
  xTaskCreatePinnedToCore(
    DisplayControllerFunction,
    "DisplayController",
    10000,
    NULL,
    10,
    &DisplayController,
    1);

    //OTA Updater
    // Connect to WiFi network
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection

    int WifiWaitCounter = 0;
    int MaxWait = 20;
    
    ScoreboardTText = "Wi-Fi Connecting";
    while ((WiFi.status() != WL_CONNECTED) && (WifiWaitCounter < MaxWait)) 
    {
      delay(500);
      Serial.print(".");
      WifiWaitCounter++;
    }
    WifiConnected = WiFi.status();
    
    if(WifiConnected == true)
    {
      WifiConnected = true;
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      ScoreboardBText = "CONNECTED";
      /*use mdns for host name resolution*/
      if (!MDNS.begin(host)) { //http://<host>.local
        Serial.println("Error setting up MDNS responder!");
        while (1) {
          delay(1000);
        }
        ScoreboardTText = (String)host + ".local";
        Serial.println("mDNS responder started");
      }
    }else
    {
      WifiConnected = false;
      ScoreboardBText = "NOT CONNECTED";
      delay(1000);
    }

    changeState(1); 
}

void loop() {
 
  vTaskDelay(1);//do nothing
}

