//ESP32PinballOS
//Version 0.0.1
#include <Arduino.h>
//Over The Air Updater 
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "userSettings.h"

int core1Hz = 0;
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
  
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  // Setup 74HC165 connections
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
  
  // Set all outputs to zero
  digitalWrite(latchPin, LOW);
  // Shift out the bits
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0); // 4 registers so we have to shift all 4
  // ST_CP HIGH change LEDs
  digitalWrite(latchPin, HIGH);


  Serial.print("Flushing the shift registers.");
  write_sr(); // flush out the shift registers
  Serial.print(".");
  read_sr(); // read the shift registers. get rid of any spurious crap on power up.
  Serial.print(".");
  delay(200);
  Serial.print(".");
  write_sr(); // flush out the shift registers
  Serial.print(".");
  read_sr(); // read again after a short delay
  Serial.print(".");
  delay(1000);
  Serial.println("done.");

  Serial.print("Setup running on core ");
  Serial.println(xPortGetCoreID());

  xTaskCreatePinnedToCore(
    MonitorSwitchesAndRegisterFunction,
    "MonitorSwitchesAndRegister",
    10000,
    NULL,
    1,
    &MonitorSwitchesAndRegister,
    1);

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
 
  //do nothing
}

