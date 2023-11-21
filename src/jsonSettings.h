#include <Arduino.h>

#include <ArduinoJson.h> // JSON soft config file
//adding comment to test GIT on new laptop

#include <Effortless_SPIFFS.h>
// Create fileSystem
eSPIFFS fileSystem;
DynamicJsonDocument configJsonDocument(1024);
bool writeToFlash = false; 

String setting_MachineName;
String setting_MachineVersion;

void createConfigFiles();
void openConfigFiles();
void updateConfigFiles();

const char * localConfigFile = "/ESPPinballOSConfig.json";

void createConfigFiles()
{

    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["Name"] = (String)"Pinball Name";
    jobject["Version"] = (String)"1.0";
    fileSystem.saveToFile(localConfigFile,jobject);
    Serial.print("JSON Document Created is: ");
    serializeJson(myJsonDocument, Serial);
    Serial.println();
}

void openConfigFiles()
{
    DynamicJsonDocument jsonDocument(1024);
    fileSystem.openFromFile(localConfigFile, jsonDocument);
    Serial.print("JSON Document Opened is: ");
    serializeJson(jsonDocument, Serial);
    Serial.println();
    //we need to set variables in the software from this json
    setting_MachineName = (const char*)jsonDocument["Name"];
    setting_MachineVersion = (const char*)jsonDocument["Version"];


}

void updateConfigFiles()
{

    
    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["Name"] = setting_MachineName;
    jobject["Version"] = setting_MachineVersion;
    fileSystem.saveToFile(localConfigFile,jobject);
    Serial.print("JSON Document Updates is: ");
    serializeJson(myJsonDocument, Serial);
    Serial.println();
}

