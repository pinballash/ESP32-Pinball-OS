//create PinballSwitch class instances - one for each switch in the switch matrix
//we know the cols and the rows so can iterate through
//for any undefined switches, we create a switch that has 9999 debounce
#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
#include "PinballSwitch.h"

//st up global switchObjects so they can be accessed later
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
  {0,&sw_0,0},
  {1,&sw_1,0},
  {2,&sw_2,0},
  {3,&sw_3,0},
  {4,&sw_4,0},
  {5,&sw_5,0},
  {6,&sw_6,0},
  {7,&sw_7,0},
  {8,&sw_8,0},
  {9,&sw_9,0},
  {10,&sw_10,0},
  {11,&sw_11,0},
  {12,&sw_12,0},
  {13,&sw_13,0},
  {14,&sw_14,0},
  {15,&sw_15,0},
  {16,&sw_16,0},
  {17,&sw_17,0},
  {18,&sw_18,0},
  {19,&sw_19,0},
  {20,&sw_20,0},
  {21,&sw_21,0},
  {22,&sw_22,0},
  {23,&sw_23,0},
  {24,&sw_24,0},
  {25,&sw_25,0},
  {26,&sw_26,0},
  {27,&sw_27,0},
  {28,&sw_28,0},
  {29,&sw_29,0},
  {30,&sw_30,0},
  {31,&sw_31,0},
  {32,&sw_32,0},
  {33,&sw_33,0},
  {34,&sw_34,0},
  {35,&sw_35,0},
  {36,&sw_36,0},
  {37,&sw_37,0},
  {38,&sw_38,0},
  {39,&sw_39,0},
  {40,&sw_40,0},
  {41,&sw_41,0},
  {42,&sw_42,0},
  {43,&sw_43,0},
  {44,&sw_44,0},
  {45,&sw_45,0},
  {46,&sw_46,0},
  {47,&sw_47,0},
  {48,&sw_48,0},
  {49,&sw_49,0},
  {50,&sw_50,0},
  {51,&sw_51,0},
  {52,&sw_52,0},
  {53,&sw_53,0},
  {54,&sw_54,0},
  {55,&sw_55,0},
  {56,&sw_56,0},
  {57,&sw_57,0},
  {58,&sw_58,0},
  {59,&sw_59,0},
  {60,&sw_60,0},
  {61,&sw_61,0},
  {62,&sw_62,0},
  {63,&sw_63,0}
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
      thisSwitch->setValues(switchJSON["switchName"],switchJSON["switchDebounce"],switchJSON["switchIsFlipper"],switchJSON["switchDebug"]);
      //Serial.println("JSON Loaded, this switch object is now called " + thisSwitch->getName());
    }//end row processing
  }//end col processing
}