//create PinballSwitch class instances - one for each switch in the switch matrix
//we know the cols and the rows so can iterate through
//for any undefined switches, we create a switch that has 9999 debounce
#include <Arduino.h>
#include <ArduinoJson.h> 
#include <Effortless_SPIFFS.h>
#include "PinballSwitch.h"

void createSwitchObjects()
{
  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {    
      int SwitchIDInteger = (col * 8)+row;
      String SwitchID = (String)SwitchIDInteger;

      //get the json file for this switchID
      String jsonConfig;
      String dataFile = "/switchConfig." + SwitchID + ".json";
      Serial.println("Opening " + dataFile);
      File file = SPIFFS.open(dataFile);
      while (file.available()) {
          // Extract each characters by one by one
          jsonConfig = file.readString();
      }
      Serial.print("JSON Document is: ");
      Serial.println(jsonConfig);
      if(jsonConfig == "")
      {
        //we need to send a dummy set of values
        String jsonString = "{\"switchId\" : " + SwitchID + ",\"switchName\":\"undefined\",\"switchDebounce\":\"1000\",\"switchIsFlipper\":\"false\",\"switchDebug\":\"false\"}";

      }

      //use the values in the json

      //we need to go through each switch and set up.  For this we probably need global objects already created and tehn update them with the JSON values.






    }//end row processing
  }//end col processing
}


PinballSwitch sw_outhole("sw_outhole",2000,false,switchDebug);
PinballSwitch sw_rebounds("sw_rebounds",200,false,switchDebug);
PinballSwitch sw_credit("sw_credit",200,false,switchDebug);
PinballSwitch sw_saucer("sw_saucer",2000,false,switchDebug);
PinballSwitch sw_sling_left("sw_sling_left",200,false,switchDebug);
PinballSwitch sw_sling_right("sw_sling_right",200,false,switchDebug);
PinballSwitch sw_pop_left("sw_pop_left",200,false,switchDebug);
PinballSwitch sw_pop_right("sw_pop_right",200,false,switchDebug);
PinballSwitch sw_notused("sw_notused",200,false,switchDebug);
PinballSwitch sw_tilt_bob("sw_tilt_bob",200,false,switchDebug);
PinballSwitch sw_tilt_slam("sw_tilt_slam",200,false,switchDebug);
PinballSwitch sw_rollover_right("sw_rollover_right",1000,false,switchDebug);
PinballSwitch sw_rollover_left("sw_rollover_left",1000,false,switchDebug);
PinballSwitch sw_start("sw_start",2000,false,switchDebug);
//PinballSwitch sw_flipper_right("sw_flipper_right",20,true,switchDebug);
//PinballSwitch sw_flipper_left("sw_flipper_left",20,true,switchDebug);
PinballSwitch sw_outlane_right("sw_outlane_right",1000,false,switchDebug);
PinballSwitch sw_outlane_left("sw_outlane_left",1000,false,switchDebug);
PinballSwitch sw_lane_p("sw_lane_p",1000,false,switchDebug);
PinballSwitch sw_lane_m("sw_lane_m",1000,false,switchDebug);
PinballSwitch sw_lane_a("sw_lane_a",1000,false,switchDebug);
PinballSwitch sw_lane_h("sw_lane_h",1000,false,switchDebug);
PinballSwitch sw_lane_c("sw_lane_c",1000,false,switchDebug);
PinballSwitch sw_spinner("sw_spinner",100,false,switchDebug);
PinballSwitch sw_drop_7("sw_drop_7",1000,false,switchDebug);
PinballSwitch sw_drop_6("sw_drop_6",1000,false,switchDebug);
PinballSwitch sw_rollover_center("sw_rollover_center",1000,false,switchDebug);
PinballSwitch sw_drop_4_5("sw_drop_4_5",1000,false,switchDebug);
PinballSwitch sw_drop_3("sw_drop_3",1000,false,switchDebug);
PinballSwitch sw_lane_change("sw_lane_change",200,false,switchDebug);
PinballSwitch sw_drop_1_2("sw_drop_1_2",1000,false,switchDebug);
PinballSwitch sw_standup_t("sw_standup_t",1000,false,switchDebug);
PinballSwitch sw_standup_h("sw_standup_h",1000,false,switchDebug);
PinballSwitch sw_standup_g("sw_standup_g",1000,false,switchDebug);
PinballSwitch sw_standup_i("sw_standup_i",1000,false,switchDebug);
PinballSwitch sw_standup_e("sw_standup_e",1000,false,switchDebug);


typedef struct {
  byte swNum; // col * 8 + row
  PinballSwitch *switchObject;
  int baseScore;
} SwitchAttributes;
typedef SwitchAttributes SwitchList[];
// List of Swithches and their object

SwitchList switches = {
  //no, PinballSwitch
  {0,&sw_outhole,0},
  {1,&sw_rebounds,100},
  {2,&sw_credit,0},
  {3,&sw_saucer,100000},
  {4,&sw_sling_left,15},
  {5,&sw_sling_right,15},
  {6,&sw_pop_left,333},
  {7,&sw_pop_right,333},
  {8,&sw_notused,0},
  {9,&sw_tilt_bob,3},
  {10,&sw_tilt_slam,3},
  {11,&sw_rollover_right,10000},
  {12,&sw_rollover_left,10000},
  {13,&sw_start,0},
  {14,&sw_notused,0},
  {15,&sw_notused,0},
  {16,&sw_outlane_right,1000},
  {17,&sw_outlane_left,1000},
  {18,&sw_notused,0},
  {19,&sw_lane_p,3000},
  {20,&sw_lane_m,3000},
  {21,&sw_lane_a,3000},
  {22,&sw_lane_h,3000},
  {23,&sw_lane_c,3000},
  {24,&sw_spinner,5},
  {25,&sw_drop_7,500},
  {26,&sw_drop_6,500},
  {27,&sw_rollover_center,500},
  {28,&sw_drop_4_5,500},
  {29,&sw_drop_3,500},
  {30,&sw_lane_change,0},
  {31,&sw_drop_1_2,500},
  {32,&sw_notused,0},
  {33,&sw_notused,0},
  {34,&sw_notused,0},
  {35,&sw_standup_t,1000},
  {36,&sw_standup_h,1000},
  {37,&sw_standup_g,1000},
  {38,&sw_standup_i,1000},
  {39,&sw_standup_e,1000},
};
