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

int MachineState = 0; //this can be Bootup-0, Atract-1, Game-2, End Game-3
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

void changeState(int newState)
{
    /* states accepted are Bootup-0, Atract-1, Game-2, End Game-3
    Bootup, this is set during initialisation and cannot be set again
    Atract, this is fired automatically following bootup or end game
    Game, this can be triggered by start button press
    End Game, this is triggered when all balls played
    */
    //lets process based on current state then deal with the change request if we are allowed
    switch(MachineState){
      case 0: //Bootup
          {
            //only one valid change here - from Bootup to Atract
            if(newState == 1)
            {
              //moving from Bootup to Atract : OK
              Serial.println("[Function] changeState - Boot->Atract");
              MachineState = 1;
              lastMachineState = 0;
              forceDisplayUpdate = true;
            }
            break;
          }
      case 1: //Attract
          {
            //only one valid change here - from Atract to Game
            if(newState == 2)
            {
              //moving from Bootup to Atract : OK
              Serial.println("[Function] changeState - Attract->Game");
              ScoreboardTText = "Lets, Play,";
              ScoreboardBText = "Pool!";
              MachineState = 2;
              lastMachineState = 1;
              forceDisplayUpdate = true;
              g_myPinballGame.newGame();
            }
            break;
          }    
      case 2: //Game
          {
            //only one valid change here - from Game to End Game
            if(newState == 3)
            {
              //moving from BGame to End Game : OK
              Serial.println("[Function] changeState - Game->End Game");

              MachineState = 3;
              lastMachineState = 2;
              forceDisplayUpdate = true;
              g_myPinballGame.endGame(); //end the game - this resets a load of stuff, we may want to run this on a new game start??


            }
            break;
          }
      case 3: //End Game
          {
            //Two valid changes here - from End Game to Game and from End Game to Atract (later HSTD entry)
            if(newState == 2)
            {
              //moving from End Game to Game : OK
              Serial.println("[Function] changeState - End Game->Game");
              ScoreboardTText = "Lets, Play,";
              ScoreboardBText = "Pool!";
              MachineState = 2;
              lastMachineState = 3;
              forceDisplayUpdate = true;
              g_myPinballGame.newGame();
            }else if (newState == 1)
            {
              //moving from End Game to Atract : OK
              Serial.println("[Function] changeState - End Game->Attract");
              MachineState = 1;
              lastMachineState = 3;
              forceDisplayUpdate = true;
            }
            break;
          }
    }
    


}


