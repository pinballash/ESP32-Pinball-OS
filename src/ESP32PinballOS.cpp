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
#include "WIFI\wifi_functions.h"
//settings from a file on the spiffs file system
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include "SETTINGS\JSON_settings.h"
#include "FILES\setupSPIFFS.h"


//these files set up switches and colis - later it would be good to do this based on a config file - this means we can have a web ui that gives configuration away from code
#include "WIFI\userSettings.h"
#include "SETTINGS\globalVariables.h"
#include "LIGHTING\ledLights.h"
#include "LOGIC\CoreMachineOperations.h"
//#include "DISPLAY\DMDDisplay.h"
#include "DISPLAY\LCDDisplay.h"
#include "CHIMES\chimeEffects.h"
#include "WEB\Web_operations.h"
#include "LOGIC\machineState.h"
#include "SHIFT-REGISTERS\setupShifts.h"

void setup() {
  // Setup Serial Monitor
  Serial.begin(115200);
  lcd.init(I2C_SDA, I2C_SCL); // initialize the lcd to use user defined I2C pins
	lcd.backlight();
	lcd.setCursor(0,0);
	lcd.print("ESP32 PinballOS");
	lcd.setCursor(0,1);
	lcd.print("by Ash Earl");
	lcd.setCursor(0,2);
	lcd.print("Booting");
	lcd.setCursor(0,3);
	lcd.print("Please wait...");
  
  //Need to set up LEDs, flippers, high power relay
  pinMode(flipper1Pin, INPUT);
  pinMode(flipper2Pin, INPUT);
  pinMode(hvrPin, OUTPUT);
  //turn off High Voltage Relay
  digitalWrite(hvrPin, HIGH);

  setupShifts();
  setupFileSystem();
  createSwitchObjects();
  createSwitchScoreObjects();
  loadDefaultScoresToGameObjects();
  createCoilObjects();
  createSwitchCoilBindings();
  createLedObjects();

  //set up timer and interupts for scaning switch matric on core 1
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 1000, true); //1000 times a second
  timerAlarmEnable(Timer0_Cfg);

  //set up the processess that will function as separate threads
  //set up loop handling rules
  xTaskCreatePinnedToCore(
    ProcessSwitchesAndRulesFunction,
    "ProcessSwitchesAndRules",
    5000,
    NULL,
    RULES_CPU_Task_Priority,
    &ProcessSwitchesAndRules,
    RULES_CPU_Core_Selection);

  //set up led handling loop
  xTaskCreatePinnedToCore(
    ProcessLedsFunction,
    "ProcessLeds",
    20000,
    NULL,
    LED_CPU_Task_Priority,
    &ProcessLeds,
    LED_CPU_Core_Selection);
  
  //set up display handling
  xTaskCreatePinnedToCore(
    DisplayControllerFunction,
    "DisplayController",
    5000,
    NULL,
    DISPLAY_CPU_Task_Priority,
    &DisplayController,
    DISPLAY_CPU_Core_Selection);
  
  
  //set up web operations
  xTaskCreatePinnedToCore(
    WebOperationsFunction,
    "WebOperationsTask",
    20000,
    NULL,
    WEB_CPU_Task_Priority,
    &WebOperationsTask,
    WEB_CPU_Core_Selection);
 

  if(webOn == true)
  {
    WiFi.begin(setting_SSID, setting_SSIDPassword);
      // Wait for connection

      int WifiWaitCounter = 0;
      int MaxWait = 5;
  
      g_myPinballGame.setDMDTopLine("Wi-Fi Connecting");
      while ((WiFi.status() != WL_CONNECTED) && (WifiWaitCounter < MaxWait)) 
      {
        delay(1000);
        //Serial.print(".");
        WifiWaitCounter++;
      }
        
      if(WiFi.status() ==  WL_CONNECTED)
      {
        WifiConnected = true;
        localIP = WiFi.localIP();
        g_myPinballGame.setDMDTopLine("Connected           ");
        
        if (!MDNS.begin(host)) { //http://<host>.local
          while (1) {
            delay(1000);
          }
        }else{
          g_myPinballGame.setDMDBottomLine(WiFi.localIP().toString());
        }
      }else
      {
        
        startSoftAccessPoint(softAPssid, softAPpassword, softAPlocalIP, softAPgatewayIP);
        setUpDNSServer(dnsServer, softAPlocalIP);
        server.begin();
        localIP = WiFi.softAPIP();
        g_myPinballGame.setDMDBottomLine(WiFi.softAPIP().toString());
        if (!MDNS.begin(host)) { //http://<host>.local
          while (1) {
            delay(1000);
          }
          
        }
        
        g_myPinballGame.setDMDTopLine((String)localIP);
        delay(1000);
        wifiSoftAPInUse = true;
        g_myPinballGame.setDMDBottomLine("SOFT AP ONLINE");
  }
      
      }
      else
      {
        g_myPinballGame.setDMDBottomLine("                    ");
      }

    changeState(1); 

    FastLED.addLeds<WS2812B, 16, GRB>(ledArray, NUM_LEDS);
    FastLED.setBrightness(8);


}

void loop() {
  

  /*if(tso_PinballGame != "")
  {
    Serial.println("[TSO_PG]"+tso_PinballGame);
    tso_PinballGame = "";
  }


  if(tso_PinballSwitch != "")
  {
    Serial.println("[TSO_PS]"+tso_PinballSwitch);
    tso_PinballSwitch = "";
  }


  
 if(tso_PinballCoil != "")
  {
    Serial.println("[TSO_PC]"+tso_PinballCoil);
    tso_PinballCoil = "";
  }

  

  if(tso_PinballDisplay != "")
  {
    Serial.println("[TSO_PD]"+tso_PinballDisplay);
    tso_PinballDisplay = "";
  }

  if(tso_PinballAudio != "")
  {
    Serial.println("[TSO_PA]"+tso_PinballAudio);
    tso_PinballAudio = "";
  }

  if(tso_SwitchesAndRules != "")
  {
    Serial.println("[TSO_SaR]"+tso_SwitchesAndRules);
    tso_SwitchesAndRules = "";
  }

  if(tso_Webserver != "")
  {
    Serial.println("[TSO_WEB]"+tso_Webserver);
    tso_Webserver = "";
  }
 

  //vTaskDelay(5000);//do nothing
  if((millis() > mainLoopMillis + 5000) && (memoryStats == true))
  {
    mainLoopMillis = millis();
    Serial.println("[Main Loop][MEM Stat] Stack High Water Mark: " + String(uxTaskGetStackHighWaterMark( NULL )));
    Serial.println("[Main Loop][MEM Stat] Free memory: " + String(esp_get_free_heap_size()) + " bytes");
    Serial.println("[Main Loop][MEM Stat] Display Controller Stack High Water Mark: " + String(uxTaskGetStackHighWaterMark(DisplayController)));
    Serial.println("[Main Loop][MEM Stat] WebOperations Stack High Water Mark: " + String(uxTaskGetStackHighWaterMark(WebOperationsTask)));
    Serial.println("[Main Loop][MEM Stat] Process Switches Stack High Water Mark: " + String(uxTaskGetStackHighWaterMark(ProcessSwitchesAndRules)));
    Serial.println("[Main Loop][MEM Stat] Led High Water Mark: " + String(uxTaskGetStackHighWaterMark(ProcessLeds)));
    //audios[0].AudioObject->fireAudio();
    //ProcessAudioShifts(audios[0].AudioObject); 
    //write_sr_audio();
  }*/
  
}

