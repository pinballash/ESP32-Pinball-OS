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
  boolean instantFire;
} CoilBinding;
typedef CoilBinding CoilBindingList[];
// List of Swithches and their object

CoilBindingList switchCoilBindings = {
  //switch, coil
{0,&s_c_binding_0,false},
{1,&s_c_binding_1,false},
{2,&s_c_binding_2,false},
{3,&s_c_binding_3,false},
{4,&s_c_binding_4,false},
{5,&s_c_binding_5,false},
{6,&s_c_binding_6,false},
{7,&s_c_binding_7,false},
{8,&s_c_binding_8,false},
{9,&s_c_binding_9,false},
{10,&s_c_binding_10,false},
{11,&s_c_binding_11,false},
{12,&s_c_binding_12,false},
{13,&s_c_binding_13,false},
{14,&s_c_binding_14,false},
{15,&s_c_binding_15,false},
{16,&s_c_binding_16,false},
{17,&s_c_binding_17,false},
{18,&s_c_binding_18,false},
{19,&s_c_binding_19,false},
{20,&s_c_binding_20,false},
{21,&s_c_binding_21,false},
{22,&s_c_binding_22,false},
{23,&s_c_binding_23,false},
{24,&s_c_binding_24,false},
{25,&s_c_binding_25,false},
{26,&s_c_binding_26,false},
{27,&s_c_binding_27,false},
{28,&s_c_binding_28,false},
{29,&s_c_binding_29,false},
{30,&s_c_binding_30,false},
{31,&s_c_binding_31,false},
{32,&s_c_binding_32,false},
{33,&s_c_binding_33,false},
{34,&s_c_binding_34,false},
{35,&s_c_binding_35,false},
{36,&s_c_binding_36,false},
{37,&s_c_binding_37,false},
{38,&s_c_binding_38,false},
{39,&s_c_binding_39,false},
{40,&s_c_binding_40,false},
{41,&s_c_binding_41,false},
{42,&s_c_binding_42,false},
{43,&s_c_binding_43,false},
{44,&s_c_binding_44,false},
{45,&s_c_binding_45,false},
{46,&s_c_binding_46,false},
{47,&s_c_binding_47,false},
{48,&s_c_binding_48,false},
{49,&s_c_binding_49,false},
{50,&s_c_binding_50,false},
{51,&s_c_binding_51,false},
{52,&s_c_binding_52,false},
{53,&s_c_binding_53,false},
{54,&s_c_binding_54,false},
{55,&s_c_binding_55,false},
{56,&s_c_binding_56,false},
{57,&s_c_binding_57,false},
{58,&s_c_binding_58,false},
{59,&s_c_binding_59,false},
{60,&s_c_binding_60,false},
{61,&s_c_binding_61,false},
{62,&s_c_binding_62,false},
{63,&s_c_binding_63,false},
 
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
        if(switchJSON["instantCoilFire"]=="true")
        {
          switchCoilBindings[SwitchByte].instantFire  = true;
        }else{
          switchCoilBindings[SwitchByte].instantFire  = false;
        }
        switchJSON.clear();
        //Serial.print("[SWITCH TO COIL BINDING] - JSON Loaded :: ");
        //Serial.println(jsonConfig);
      }

      
    }//end row processing
  }//end col processing
}
