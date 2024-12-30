#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
// Create fileSystem
eSPIFFS fileSystem;
DynamicJsonDocument configJsonDocument(1024);
bool writeToFlash = false; 

String setting_MachineName = "Your Game Name";
String setting_MachineVersion = "0.1";

String setting_SSID = "YourWiFiHere";
String setting_SSIDPassword = "";

// Define Connections to 74HC595 - Switch Matrix Output Shift Register
int setting_osr1latchPin = 18; 
int setting_osr1clockPin = 5;
int setting_osr1dataPin = 17;

// Define Connections to 74HC595 - Audio Output Shift Register
int setting_osr2latchPin = 2; //changed from 3
int setting_osr2clockPin = 21;
int setting_osr2dataPin = 19;

// Define Connections to 74HC595 - Coil Output Shift Registers
int setting_osr3latchPin = 23;
int setting_osr3clockPin = 22;
int setting_osr3dataPin = 15; //changed from 1

//Comms to 74HC165 - Input Shift Registers
int setting_isrload = 25;
int setting_isrclockEnablePin = 32; //latch
int setting_isrdataIn = 33;
int setting_isrclockIn = 26;

//High Voltage Relay pin
int setting_hvrPin = 27;

//Flipper 1 pin
int setting_flipper1Pin = 34;

//Flipper 2 pin
int setting_flipper2Pin = 35;

//Switch Matrix
int setting_switchMatrixRows = 8;
int setting_switchMatrixColumns = 8;

int setting_ledPin = 16;
int setting_leds = 255;

void createConfigFiles();
void openConfigFiles();
void updateConfigFiles();

const char * localConfigFile = "/ESPPinballOSConfig.json";
void createConfigFiles()
{

    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["Name"] = setting_MachineName;
    jobject["Version"] = setting_MachineVersion;
    jobject["SSID"] = setting_SSID;
    jobject["SSIDPassword"] = setting_SSIDPassword;
    jobject["osr1latchPin"] = setting_osr1latchPin;
    jobject["osr1clockPin"] = setting_osr1clockPin;
    jobject["osr1dataPin"] = setting_osr1dataPin;
    jobject["osr2latchPin"] = setting_osr2latchPin;
    jobject["osr2clockPin"] = setting_osr2clockPin;
    jobject["osr2dataPin"] = setting_osr2dataPin;
    jobject["osr3latchPin"] = setting_osr3latchPin;
    jobject["osr3clockPin"] = setting_osr3clockPin;
    jobject["osr3dataPin"] = setting_osr3dataPin;
    jobject["isrload"] = setting_isrload;
    jobject["isrclockEnablePin"] = setting_isrclockEnablePin;
    jobject["isrdataIn"] = setting_isrdataIn;
    jobject["isrclockIn"] = setting_isrclockIn;
    jobject["hvrPin"] = setting_hvrPin;
    jobject["flipper1Pin"] = setting_flipper1Pin;
    jobject["flipper2Pin"] = setting_flipper2Pin;
    jobject["switchMatrixRows"] = setting_switchMatrixRows;
    jobject["switchMatrixColumns"] = setting_switchMatrixColumns;
    jobject["ledPin"] = setting_ledPin;
    jobject["leds"] = setting_leds;
    fileSystem.saveToFile(localConfigFile,jobject);
    myJsonDocument.clear();
    jobject.clear();
}

void openConfigFiles()
{
    DynamicJsonDocument jsonDocument(1024);
    fileSystem.openFromFile(localConfigFile, jsonDocument);
    //we need to set variables in the software from this json
    setting_MachineName = (const char*)jsonDocument["Name"];
    setting_MachineVersion = (const char*)jsonDocument["Version"];
    setting_SSID = (const char*)jsonDocument["SSID"];
    setting_SSIDPassword = (const char*)jsonDocument["SSIDPassword"];
    setting_osr1latchPin = (int8_t)jsonDocument["osr1latchPin"];
    setting_osr1clockPin = (int8_t)jsonDocument["osr1clockPin"];
    setting_osr1dataPin = (int8_t)jsonDocument["osr1dataPin"];
    setting_osr2latchPin = (int8_t)jsonDocument["osr2latchPin"];
    setting_osr2clockPin = (int8_t)jsonDocument["osr2clockPin"];
    setting_osr2dataPin = (int8_t)jsonDocument["osr2dataPin"];
    setting_osr3latchPin = (int8_t)jsonDocument["osr3latchPin"];
    setting_osr3clockPin = (int8_t)jsonDocument["osr3clockPin"];
    setting_osr3dataPin = (int8_t)jsonDocument["osr3dataPin"];
    setting_isrload = (int8_t)jsonDocument["isrload"];
    setting_isrclockEnablePin = (int8_t)jsonDocument["isrclockEnablePin"];
    setting_isrdataIn = (int8_t)jsonDocument["isrdataIn"];
    setting_isrclockIn = (int8_t)jsonDocument["isrclockIn"];
    setting_hvrPin = (int8_t)jsonDocument["hvrPin"];
    setting_flipper1Pin = (int8_t)jsonDocument["flipper1Pin"];
    setting_flipper2Pin = (int8_t)jsonDocument["flipper2Pin"];
    setting_switchMatrixRows = (int8_t)jsonDocument["switchMatrixRows"];
    setting_switchMatrixColumns = (int8_t)jsonDocument["switchMatrixColumns"];
    setting_ledPin = (int8_t)jsonDocument["ledPin"];
    setting_leds = (int8_t)jsonDocument["leds"];
    jsonDocument.clear();
}

void updateConfigFiles()
{
    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["Name"] = setting_MachineName;
    jobject["Version"] = setting_MachineVersion;
    jobject["SSID"] = setting_SSID;
    jobject["SSIDPassword"] = setting_SSIDPassword;
    jobject["osr1latchPin"] = setting_osr1latchPin;
    jobject["osr1clockPin"] = setting_osr1clockPin;
    jobject["osr1dataPin"] = setting_osr1dataPin;
    jobject["osr2latchPin"] = setting_osr2latchPin;
    jobject["osr2clockPin"] = setting_osr2clockPin;
    jobject["osr2dataPin"] = setting_osr2dataPin;
    jobject["osr3latchPin"] = setting_osr3latchPin;
    jobject["osr3clockPin"] = setting_osr3clockPin;
    jobject["osr3dataPin"] = setting_osr3dataPin;
    jobject["isrload"] = setting_isrload;
    jobject["isrclockEnablePin"] = setting_isrclockEnablePin;
    jobject["isrdataIn"] = setting_isrdataIn;
    jobject["isrclockIn"] = setting_isrclockIn;
    jobject["hvrPin"] = setting_hvrPin;
    jobject["flipper1Pin"] = setting_flipper1Pin;
    jobject["flipper2Pin"] = setting_flipper2Pin;
    jobject["switchMatrixRows"] = setting_switchMatrixRows;
    jobject["switchMatrixColumns"] = setting_switchMatrixColumns;
    jobject["ledPin"] = setting_ledPin;
    jobject["leds"] = setting_leds;
    fileSystem.saveToFile(localConfigFile,jobject);
    myJsonDocument.clear();
    jobject.clear();
}

