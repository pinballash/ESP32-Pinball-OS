#include <Arduino.h>
//define LED named objects
//CHAMP
PinballLED* c_champ = LEDs[82].ledObject;
PinballLED* h_champ = LEDs[19].ledObject;
PinballLED* a_champ = LEDs[20].ledObject;
PinballLED* m_champ = LEDs[21].ledObject;
PinballLED* p_champ = LEDs[78].ledObject;

//Table Balls
PinballLED* oneball_table = LEDs[39].ledObject;
PinballLED* twoball_table = LEDs[37].ledObject;
PinballLED* threeball_table = LEDs[34].ledObject;
PinballLED* fourball_table = LEDs[32].ledObject;
PinballLED* fiveeball_table = LEDs[30].ledObject;
PinballLED* sixball_table = LEDs[42].ledObject;
PinballLED* sevenball_table = LEDs[54].ledObject;
PinballLED* eightball_table = LEDs[2].ledObject;
PinballLED* nineball_table = LEDs[40].ledObject;
PinballLED* tenball_table = LEDs[14].ledObject;
PinballLED* elevenball_table = LEDs[33].ledObject;
PinballLED* twelveball_table = LEDs[31].ledObject;
PinballLED* thirteenball_table = LEDs[29].ledObject;
PinballLED* fourteenball_table = LEDs[43].ledObject;
PinballLED* fifteenball_table = LEDs[51].ledObject;

//Pocket Balls
PinballLED* oneball_pocket = LEDs[62].ledObject;
PinballLED* twoball_pocket = LEDs[64].ledObject;
PinballLED* threeball_pocket = LEDs[67].ledObject;
PinballLED* fourball_pocket = LEDs[70].ledObject;
PinballLED* fiveeball_pocket = LEDs[72].ledObject;
PinballLED* sixball_pocket = LEDs[73].ledObject;
PinballLED* sevenball_pocket = LEDs[75].ledObject;
PinballLED* eightball_pocket = LEDs[68].ledObject;
PinballLED* nineball_pocket = LEDs[63].ledObject;
PinballLED* tenball_pocket = LEDs[65].ledObject;
PinballLED* elevenball_pocket = LEDs[66].ledObject;
PinballLED* twelveball_pocket = LEDs[69].ledObject;
PinballLED* thirteenball_pocket = LEDs[71].ledObject;
PinballLED* fourteenball_pocket = LEDs[74].ledObject;
PinballLED* fifteenball_pocket = LEDs[76].ledObject;

//Table indicators
PinballLED* shootagain = LEDs[92].ledObject;
PinballLED* twox_bonus = LEDs[89].ledObject;
PinballLED* threex_bonus = LEDs[88].ledObject;
PinballLED* fivex_bonus = LEDs[87].ledObject;
PinballLED* onehundredtwentythousand_bonus = LEDs[90].ledObject;
PinballLED* twohundredfortythousand_bonus = LEDs[86].ledObject;
PinballLED* double_playfield = LEDs[81].ledObject;
PinballLED* triple_playfield = LEDs[79].ledObject;

PinballLED* special_big = LEDs[80].ledObject;
PinballLED* special_left_outlane = LEDs[83].ledObject;
PinballLED* special_right_outlane = LEDs[77].ledObject;
PinballLED* special_centre = LEDs[49].ledObject;
PinballLED* special_left_rollover = LEDs[9].ledObject;
PinballLED* special_right_rollover = LEDs[23].ledObject;



PinballLED* onethousand_spinner = LEDs[15].ledObject;
PinballLED* threethousand_spinner = LEDs[16].ledObject;
PinballLED* fivethousand_spinner = LEDs[17].ledObject;