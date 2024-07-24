#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
#include "PinballAudio.h"

//st up global coilObjects so they can be accessed later
PinballAudio a_0(0);
PinballAudio a_1(1);

typedef struct {
  byte audioNum; 
  PinballAudio *AudioObject;
} AudioAttributes;
typedef AudioAttributes AudioList[];
// List of Swithches and their object

AudioList audios = {
  {0,&a_0},
  {1,&a_1}
};




void createAudioObjects()
{
  for ( byte col = 0; col < 2 ; col++) {
    
      int AudioIDInteger = col;
      int soundClipID = col;
      String AudioID = (String)AudioIDInteger;
      byte AudioByte = col;
      byte soundClipIDbyte = soundClipID;

      //get the json file for this CoilID
      /*String jsonConfig;
      String dataFile = "/coilConfig." + CoilID + ".json";
      //Serial.println("Opening " + dataFile);
      File file = SPIFFS.open(dataFile);
      while (file.available()) {
          // Extract each characters by one by one
          jsonConfig = file.readString();
      }
      //Serial.print("JSON Document is: ");
      //Serial.println(jsonConfig);
      if(jsonConfig == "")
      {
        //we need to send a dummy set of values
        jsonConfig = "{\"coilId\" : " + CoilID + ",\"coilName\":\"undefined\",\"shiftRegister\":\"\",\"shiftRegisterBit\":\"\",\"pulseTime\":\"50\",\"pulseBackOff\":\"500\"}";

      }

      //use the values in the json
      DynamicJsonDocument coilJSON(2048);
      deserializeJson(coilJSON,jsonConfig);*/
      PinballAudio* thisAudio = audios[AudioByte].AudioObject;
      tso_PinballAudio = tso_PinballAudio + "[CreateAudioObjects] [setValues] Name = SoundClip"+AudioID;
      //String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff
      thisAudio->setValues("SoundClip"+AudioID,0,soundClipIDbyte,100,100);
      //Serial.println("JSON Loaded, this coil object is now called " + thisCoil->getName());
      //coilJSON.clear();

  }//end col processing
}