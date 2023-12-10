#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>

byte s_c_binding_0 = -1;
byte s_c_binding_1 = -1;
byte s_c_binding_2 = -1;
byte s_c_binding_3 = -1;
byte s_c_binding_4 = -1;
byte s_c_binding_5 = -1;
byte s_c_binding_6 = -1;
byte s_c_binding_7 = -1;
byte s_c_binding_8 = -1;
byte s_c_binding_9 = -1;
byte s_c_binding_10 = -1;
byte s_c_binding_11 = -1;
byte s_c_binding_12 = -1;
byte s_c_binding_13 = -1;
byte s_c_binding_14 = -1;
byte s_c_binding_15 = -1;
byte s_c_binding_16 = -1;
byte s_c_binding_17 = -1;
byte s_c_binding_18 = -1;
byte s_c_binding_19 = -1;
byte s_c_binding_20 = -1;
byte s_c_binding_21 = -1;
byte s_c_binding_22 = -1;
byte s_c_binding_23 = -1;
byte s_c_binding_24 = -1;
byte s_c_binding_25 = -1;
byte s_c_binding_26 = -1;
byte s_c_binding_27 = -1;
byte s_c_binding_28 = -1;
byte s_c_binding_29 = -1;
byte s_c_binding_30 = -1;
byte s_c_binding_31 = -1;
byte s_c_binding_32 = -1;
byte s_c_binding_33 = -1;
byte s_c_binding_34 = -1;
byte s_c_binding_35 = -1;
byte s_c_binding_36 = -1;
byte s_c_binding_37 = -1;
byte s_c_binding_38 = -1;
byte s_c_binding_39 = -1;
byte s_c_binding_40 = -1;
byte s_c_binding_41 = -1;
byte s_c_binding_42 = -1;
byte s_c_binding_43 = -1;
byte s_c_binding_44 = -1;
byte s_c_binding_45 = -1;
byte s_c_binding_46 = -1;
byte s_c_binding_47 = -1;
byte s_c_binding_48 = -1;
byte s_c_binding_49 = -1;
byte s_c_binding_50 = -1;
byte s_c_binding_51 = -1;
byte s_c_binding_52 = -1;
byte s_c_binding_53 = -1;
byte s_c_binding_54 = -1;
byte s_c_binding_55 = -1;
byte s_c_binding_56 = -1;
byte s_c_binding_57 = -1;
byte s_c_binding_58 = -1;
byte s_c_binding_59 = -1;
byte s_c_binding_60 = -1;
byte s_c_binding_61 = -1;
byte s_c_binding_62 = -1;
byte s_c_binding_63 = -1;

typedef struct {
  byte swNumber; // col * 8 + row
  byte *coilNumber;
} CoilBinding;
typedef CoilBinding CoilBindingList[];
// List of Swithches and their object

CoilBindingList switchCoilBindings = {
  //switch, coil
{0,&s_c_binding_0},
{1,&s_c_binding_1},
{2,&s_c_binding_2},
{3,&s_c_binding_3},
{4,&s_c_binding_4},
{5,&s_c_binding_5},
{6,&s_c_binding_6},
{7,&s_c_binding_7},
{8,&s_c_binding_8},
{9,&s_c_binding_9},
{10,&s_c_binding_10},
{11,&s_c_binding_11},
{12,&s_c_binding_12},
{13,&s_c_binding_13},
{14,&s_c_binding_14},
{15,&s_c_binding_15},
{16,&s_c_binding_16},
{17,&s_c_binding_17},
{18,&s_c_binding_18},
{19,&s_c_binding_19},
{20,&s_c_binding_20},
{21,&s_c_binding_21},
{22,&s_c_binding_22},
{23,&s_c_binding_23},
{24,&s_c_binding_24},
{25,&s_c_binding_25},
{26,&s_c_binding_26},
{27,&s_c_binding_27},
{28,&s_c_binding_28},
{29,&s_c_binding_29},
{30,&s_c_binding_30},
{31,&s_c_binding_31},
{32,&s_c_binding_32},
{33,&s_c_binding_33},
{34,&s_c_binding_34},
{35,&s_c_binding_35},
{36,&s_c_binding_36},
{37,&s_c_binding_37},
{38,&s_c_binding_38},
{39,&s_c_binding_39},
{40,&s_c_binding_40},
{41,&s_c_binding_41},
{42,&s_c_binding_42},
{43,&s_c_binding_43},
{44,&s_c_binding_44},
{45,&s_c_binding_45},
{46,&s_c_binding_46},
{47,&s_c_binding_47},
{48,&s_c_binding_48},
{49,&s_c_binding_49},
{50,&s_c_binding_50},
{51,&s_c_binding_51},
{52,&s_c_binding_52},
{53,&s_c_binding_53},
{54,&s_c_binding_54},
{55,&s_c_binding_55},
{56,&s_c_binding_56},
{57,&s_c_binding_57},
{58,&s_c_binding_58},
{59,&s_c_binding_59},
{60,&s_c_binding_60},
{61,&s_c_binding_61},
{62,&s_c_binding_62},
{63,&s_c_binding_63},
 
};

void createSwitchCoilBindings()
{
  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {    
      int SwitchIDInteger = (col * 8)+row;
      String SwitchID = (String)SwitchIDInteger;
      byte SwitchByte = SwitchIDInteger;

      //get the json file for this switchID
      String jsonConfig;
      String dataFile = "/switchCoilBindingConfig." + SwitchID + ".json";
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
        jsonConfig = "{\"switchId\" : " + SwitchID + ",\"coilBinding\":\"-1\"}";

      }else{
        //use the values in the json
        DynamicJsonDocument switchJSON(2048);
        deserializeJson(switchJSON,jsonConfig);
        byte* thisSwitchCoilBinding = switchCoilBindings[SwitchByte].coilNumber;
        *thisSwitchCoilBinding = switchJSON["coilBinding"];
        Serial.print("[SWITCH TO COIL BINDING] - JSON Loaded");
        Serial.println(jsonConfig);
      }

      
    }//end row processing
  }//end col processing
}
