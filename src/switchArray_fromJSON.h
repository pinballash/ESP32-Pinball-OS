//create PinballSwitch class instances - one for each switch in the switch matrix
//we know the cols and the rows so can iterate through
//for any undefined switches, we create a switch that has 9999 debounce
#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
#include "PinballSwitch.h"

//set up global switchObjects so they can be accessed later
PinballSwitch sw_0(0);
PinballSwitch sw_1(1);
PinballSwitch sw_2(2);
PinballSwitch sw_3(3);
PinballSwitch sw_4(4);
PinballSwitch sw_5(5);
PinballSwitch sw_6(6);
PinballSwitch sw_7(7);
PinballSwitch sw_8(8);
PinballSwitch sw_9(9);

PinballSwitch sw_10(10);
PinballSwitch sw_11(11);
PinballSwitch sw_12(12);
PinballSwitch sw_13(13);
PinballSwitch sw_14(14);
PinballSwitch sw_15(15);
PinballSwitch sw_16(16);
PinballSwitch sw_17(17);
PinballSwitch sw_18(18);
PinballSwitch sw_19(19);

PinballSwitch sw_20(20);
PinballSwitch sw_21(21);
PinballSwitch sw_22(22);
PinballSwitch sw_23(23);
PinballSwitch sw_24(24);
PinballSwitch sw_25(25);
PinballSwitch sw_26(26);
PinballSwitch sw_27(27);
PinballSwitch sw_28(28);
PinballSwitch sw_29(29);

PinballSwitch sw_30(30);
PinballSwitch sw_31(31);
PinballSwitch sw_32(32);
PinballSwitch sw_33(33);
PinballSwitch sw_34(34);
PinballSwitch sw_35(35);
PinballSwitch sw_36(36);
PinballSwitch sw_37(37);
PinballSwitch sw_38(38);
PinballSwitch sw_39(39);

PinballSwitch sw_40(40);
PinballSwitch sw_41(41);
PinballSwitch sw_42(42);
PinballSwitch sw_43(43);
PinballSwitch sw_44(44);
PinballSwitch sw_45(45);
PinballSwitch sw_46(46);
PinballSwitch sw_47(47);
PinballSwitch sw_48(48);
PinballSwitch sw_49(49);

PinballSwitch sw_50(50);
PinballSwitch sw_51(51);
PinballSwitch sw_52(52);
PinballSwitch sw_53(53);
PinballSwitch sw_54(54);
PinballSwitch sw_55(55);
PinballSwitch sw_56(56);
PinballSwitch sw_57(57);
PinballSwitch sw_58(58);
PinballSwitch sw_59(59);

PinballSwitch sw_60(60);
PinballSwitch sw_61(61);
PinballSwitch sw_62(62);
PinballSwitch sw_63(63);

typedef struct {
  byte swNum; // col * 8 + row
  PinballSwitch *switchObject;
  int baseScore;
} SwitchAttributes;
typedef SwitchAttributes SwitchList[];

// List of Swithches and their object
SwitchList switches = {
  //no, PinballSwitch
  {0,&sw_0,3},
  {1,&sw_1,3},
  {2,&sw_2,3},
  {3,&sw_3,3},
  {4,&sw_4,3},
  {5,&sw_5,3},
  {6,&sw_6,3},
  {7,&sw_7,3},
  {8,&sw_8,3},
  {9,&sw_9,3},
  {10,&sw_10,3},
  {11,&sw_11,3},
  {12,&sw_12,3},
  {13,&sw_13,3},
  {14,&sw_14,3},
  {15,&sw_15,3},
  {16,&sw_16,3},
  {17,&sw_17,3},
  {18,&sw_18,3},
  {19,&sw_19,3},
  {20,&sw_20,3},
  {21,&sw_21,3},
  {22,&sw_22,3},
  {23,&sw_23,3},
  {24,&sw_24,3},
  {25,&sw_25,3},
  {26,&sw_26,3},
  {27,&sw_27,3},
  {28,&sw_28,3},
  {29,&sw_29,3},
  {30,&sw_30,3},
  {31,&sw_31,3},
  {32,&sw_32,3},
  {33,&sw_33,3},
  {34,&sw_34,3},
  {35,&sw_35,3},
  {36,&sw_36,3},
  {37,&sw_37,3},
  {38,&sw_38,3},
  {39,&sw_39,3},
  {40,&sw_40,3},
  {41,&sw_41,3},
  {42,&sw_42,3},
  {43,&sw_43,3},
  {44,&sw_44,3},
  {45,&sw_45,3},
  {46,&sw_46,3},
  {47,&sw_47,3},
  {48,&sw_48,3},
  {49,&sw_49,3},
  {50,&sw_50,3},
  {51,&sw_51,3},
  {52,&sw_52,3},
  {53,&sw_53,3},
  {54,&sw_54,3},
  {55,&sw_55,3},
  {56,&sw_56,3},
  {57,&sw_57,3},
  {58,&sw_58,3},
  {59,&sw_59,3},
  {60,&sw_60,3},
  {61,&sw_61,3},
  {62,&sw_62,3},
  {63,&sw_63,3}
};




void createSwitchObjects()
{
  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {    
      int SwitchIDInteger = (col * 8)+row;
      String SwitchID = (String)SwitchIDInteger;
      byte SwitchByte = SwitchIDInteger;

      //get the json file for this switchID
      String jsonConfig;
      String dataFile = "/switchConfig." + SwitchID + ".json";
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
        jsonConfig = "{\"switchId\" : " + SwitchID + ",\"switchName\":\"Unconfigured\",\"switchDebounce\":\"1000\",\"switchIsFlipper\":\"false\",\"switchDebug\":\"false\"}";

      }

      //use the values in the json
      DynamicJsonDocument switchJSON(2048);
      deserializeJson(switchJSON,jsonConfig);
      PinballSwitch* thisSwitch = switches[SwitchByte].switchObject;
      //sanitiseJSON
      bool isFlipper = false;
      bool isStart = false;
      bool isCredit = false;
      bool isOuthole = false;
      bool isDebug = false;
      bool autoOn = true;

      if(switchJSON["switchIsFlipper"] == "true")
      {
        isFlipper = true;
      }
      if(switchJSON["switchIsStart"] == "true")
      {
        isStart = true;
      }
      if(switchJSON["switchIsCredit"] == "true")
      {
        isCredit = true;
      }
      if(switchJSON["switchIsOuthole"] == "true")
      {
        isOuthole = true;
      }
      if(switchJSON["switchIsDebug"] == "true")
      {
        isDebug = true;
      }
      if(switchJSON["switchAutoOn"] == "false")
      {
        autoOn = false;
      }



      thisSwitch->setValues(switchJSON["switchName"],switchJSON["switchDebounce"],isFlipper,isStart,isCredit,isOuthole,isDebug,autoOn);
      //Serial.println("JSON Loaded, this switch object is now called " + thisSwitch->getName());
    }//end row processing
  }//end col processing
}