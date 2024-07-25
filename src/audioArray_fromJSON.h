#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
#include "PinballAudio.h"

//st up global coilObjects so they can be accessed later
PinballAudio a_0(0);
PinballAudio a_1(1);
PinballAudio a_2(2);
PinballAudio a_3(3);
PinballAudio a_4(4);
PinballAudio a_5(5);
PinballAudio a_6(6);
PinballAudio a_7(7);
PinballAudio a_8(8);
PinballAudio a_9(9);
PinballAudio a_10(10);
PinballAudio a_11(11);
PinballAudio a_12(12);
PinballAudio a_13(13);
PinballAudio a_14(14);
PinballAudio a_15(15);
PinballAudio a_16(16);
PinballAudio a_17(17);
PinballAudio a_18(18);
PinballAudio a_19(19);
PinballAudio a_20(20);
PinballAudio a_21(21);
PinballAudio a_22(22);
PinballAudio a_23(23);
PinballAudio a_24(24);
PinballAudio a_25(25);
PinballAudio a_26(26);
PinballAudio a_27(27);
PinballAudio a_28(28);
PinballAudio a_29(29);
PinballAudio a_30(30);
PinballAudio a_31(31);
PinballAudio a_32(32);
PinballAudio a_33(33);
PinballAudio a_34(34);
PinballAudio a_35(35);
PinballAudio a_36(36);
PinballAudio a_37(37);
PinballAudio a_38(38);
PinballAudio a_39(39);
PinballAudio a_40(40);


typedef struct {
  byte audioNum; 
  PinballAudio *AudioObject;
} AudioAttributes;
typedef AudioAttributes AudioList[];
// List of Swithches and their object

AudioList audios = {
  {0,&a_0},
{1,&a_1},
{2,&a_2},
{3,&a_3},
{4,&a_4},
{5,&a_5},
{6,&a_6},
{7,&a_7},
{8,&a_8},
{9,&a_9},
{10,&a_10},
{11,&a_11},
{12,&a_12},
{13,&a_13},
{14,&a_14},
{15,&a_15},
{16,&a_16},
{17,&a_17},
{18,&a_18},
{19,&a_19},
{20,&a_20},
{21,&a_21},
{22,&a_22},
{23,&a_23},
{24,&a_24},
{25,&a_25},
{26,&a_26},
{27,&a_27},
{28,&a_28},
{29,&a_29},
{30,&a_30},
{31,&a_31},
{32,&a_32},
{33,&a_33},
{34,&a_34},
{35,&a_35},
{36,&a_36},
{37,&a_37},
{38,&a_38},
{39,&a_39}

};




void createAudioObjects()
{
  for ( byte col = 0; col < 40 ; col++) {
    
      int AudioIDInteger = col;

      
      String AudioID = (String)AudioIDInteger;
      byte AudioByte = col;
      byte soundClipIDbyte = AudioIDInteger;

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
      //tso_PinballAudio = tso_PinballAudio + "[CreateAudioObjects] [setValues] Name = SoundClip"+AudioID;
      //String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff
      thisAudio->setValues("SoundClip"+AudioID,0,soundClipIDbyte,200,100);
      //Serial.println("JSON Loaded, this coil object is now called " + thisCoil->getName());
      //coilJSON.clear();

  }//end col processing
}