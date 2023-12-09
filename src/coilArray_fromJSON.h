#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
#include "PinballCoil.h"

//st up global coilObjects so they can be accessed later
PinballCoil c_0(0);
PinballCoil c_1(1);
PinballCoil c_2(2);
PinballCoil c_3(3);
PinballCoil c_4(4);
PinballCoil c_5(5);
PinballCoil c_6(6);
PinballCoil c_7(7);
PinballCoil c_8(8);
PinballCoil c_9(9);
PinballCoil c_10(10);
PinballCoil c_11(11);
PinballCoil c_12(12);
PinballCoil c_13(13);
PinballCoil c_14(14);
PinballCoil c_15(15);

typedef struct {
  byte coilNum; // col * 8 + row
  PinballCoil *coilObject;
} CoilAttributes;
typedef CoilAttributes CoilList[];
// List of Swithches and their object

CoilList coils = {
  {0,&c_0},
  {1,&c_1},
  {2,&c_2},
  {3,&c_3},
  {4,&c_4},
  {5,&c_5},
  {6,&c_6},
  {7,&c_7},
  {8,&c_8},
  {9,&c_9},
  {10,&c_10},
  {11,&c_11},
  {12,&c_12},
  {13,&c_13},
  {14,&c_14},
  {15,&c_15}
};




void createCoilObjects()
{
  for ( byte col = 0; col < 2 ; col++) {
    for (byte row = 0; row < 8; row++) 
    {    
      int CoilIDInteger = (col * 8)+row;
      String CoilID = (String)CoilIDInteger;
      byte CoilByte = CoilIDInteger;

      //get the json file for this CoilID
      String jsonConfig;
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
      deserializeJson(coilJSON,jsonConfig);
      PinballCoil* thisCoil = coils[CoilByte].coilObject;

      //String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff
      thisCoil->setValues(coilJSON["coilName"],coilJSON["shiftRegister"],coilJSON["shiftRegisterBit"],coilJSON["pulseTime"],coilJSON["pulseBackOff"]);
      //Serial.println("JSON Loaded, this coil object is now called " + thisCoil->getName());
    }//end row processing
  }//end col processing
}