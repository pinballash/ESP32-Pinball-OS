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
#include "wifi_functions.h"
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include "jsonSettings.h"
#include "setupSPIFFS.h"


//these files set up switches and colis - later it would be good to do this based on a config file - this means we can have a web ui that gives configuration away from code
#include "userSettings.h"

int WEBHz = 0;
int CMOHz = 0;
int DisplayControllerHz = 0;

unsigned long lastMillisSwINT = 0;

unsigned long lastMillisFlip1 = 0;
int INTHz = 0;
int reportedSwitchMatrixHz = 0;
bool scanInProgress = false;
bool flip1Enabled = false;
bool flip2Enabled= false;
bool flip1Released = true;
bool flip2Released= true;


int MachineState = 0; //this can be Bootup-0, Atract-1, Game-2, End Game-3, End Ball-4
int lastMachineState = 0;
bool forceDisplayUpdate = false;
bool WifiConnected = false;
bool wifiSoftAPInUse = false;
IPAddress localIP;
String localIPURL;	 // a string version of the local IP with http, used for redirecting clients to your webpage



String ScoreboardTText = "";
String ScoreboardTRText = "";
String ScoreboardTLText = "";
String ScoreboardBText = "";

#include "CoreMachineOperations.h"
#include "DMDDisplay.h"
#include "WebOperations.h"
#include "machineState.h"
#include "setupShifts.h"

void setup() {
  // put your setup code here, to run once:
  // Setup Serial Monitor
  Serial.begin(115200);

  //Need to set up LEDs, flippers, high power relay

  pinMode(flipper1Pin, INPUT);
  //attachInterrupt(flipper1Pin, fireFlipper1, HIGH);
  //attachInterrupt(flipper1Pin, releaseFlipper1, LOW);
  
  pinMode(flipper2Pin, INPUT);

  //attachInterrupt(flipper2Pin, fireFlipper2, RISING);
  //attachInterrupt(flipper2Pin, releaseFlipper2, FALLING);

  pinMode(hvrPin, OUTPUT);
  //turn off High Voltage Relay
  digitalWrite(hvrPin, LOW);

  setupShifts();
 
  //Serial.println("Now read settings files...");
  //Serial.println("Starting SPIFFS");

  setupFileSystem();
  

  //Serial.print("Setup running on core ");
  //Serial.println(xPortGetCoreID());

  //Serial.println("Starting Switch Object Creation");
  createSwitchObjects();
  //Serial.println("Starting Coil Object Creation");
  createCoilObjects();
  //Serial.println("Starting Switch Coil bonding");
  createSwitchCoilBindings();

  createLedObjects();

  /*xTaskCreatePinnedToCore(
    MonitorSwitchesAndRegisterFunction,
    "MonitorSwitchesAndRegister",
    10000,
    NULL,
    1,
    &MonitorSwitchesAndRegister,
    0);*/
  
    xTaskCreatePinnedToCore(
    ProcessSwitchesAndRulesFunction,
    "ProcessSwitchesAndRules",
    10000,
    NULL,
    2,
    &ProcessSwitchesAndRules,
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

    //now need some logic here - do we have credentials saved in the config?
    //Yes, try and connect to the wifi, if fail create a soft ap
    //no, create a soft ap
    WiFi.begin(setting_SSID, setting_SSIDPassword);
    //Serial.println("");

    // Wait for connection

    int WifiWaitCounter = 0;
    int MaxWait = 5;
    
    ScoreboardTText = "Wi-Fi Connecting";
    while ((WiFi.status() != WL_CONNECTED) && (WifiWaitCounter < MaxWait)) 
    {
      delay(1000);
      //Serial.print(".");
      WifiWaitCounter++;
    }
       
    if(WiFi.status() ==  WL_CONNECTED)
    {
      WifiConnected = true;
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(setting_SSID);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      localIP = WiFi.localIP();
      ScoreboardBText = "CONNECTED";
      //Serial.println("Setting up MDNS as " + (String)host + ".local");
      /*use mdns for host name resolution*/
      if (!MDNS.begin(host)) { //http://<host>.local
        //Serial.println("Error setting up MDNS responder!");
        while (1) {
          delay(1000);
        }
      }else{
        ScoreboardTText = (String)host + ".local";
        //Serial.println("mDNS responder started");
      }
    }else
    {
      
      startSoftAccessPoint(softAPssid, softAPpassword, softAPlocalIP, softAPgatewayIP);
      setUpDNSServer(dnsServer, softAPlocalIP);
      server.begin();
      Serial.print("AP IP address: ");
      Serial.println(WiFi.softAPIP());
      localIP = WiFi.softAPIP();
      if (!MDNS.begin(host)) { //http://<host>.local
        //Serial.println("Error setting up MDNS responder!");
        while (1) {
          delay(1000);
        }
        
      }
      ScoreboardTText = (String)host + ".local";
      //Serial.println("mDNS responder started");
      //Serial.print("http://");
      //Serial.print(host);
      //Serial.println(".local");
      delay(1000);
      wifiSoftAPInUse = true;
      ScoreboardBText = "NOT CONNECTED";
      ScoreboardTText = "SOFT AP ONLINE";
    }

    changeState(1); 

    Timer0_Cfg = timerBegin(0, 80, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 1000, true);
    timerAlarmEnable(Timer0_Cfg);
}

void loop() {
  if(flip1Enabled == true)
  {
    if (millis() - lastMillisFlip1 > 300 )
    {
      
        Serial.println("ReleaseFlipper1");
        flip1Enabled = false;

    }
  }

  vTaskDelay(1);//do nothing
}

