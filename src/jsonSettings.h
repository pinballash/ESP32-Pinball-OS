#include <Arduino.h>
#include <ArduinoJson.h> // JSON soft config file
//adding comment to test GIT on new laptop

#include <Effortless_SPIFFS.h>
// Create fileSystem
eSPIFFS fileSystem;
DynamicJsonDocument configJsonDocument(1024);
bool writeToFlash = false;   

void createConfigFiles();
void openConfigFiles();

const char * localConfigFile = "/ESPPinballOSConfig.json";

void createConfigFiles()
{

    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["Name"] = "Pinball Name";
    jobject["Version"] = "1.1";
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

}

