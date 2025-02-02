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
PinballLED* fiveball_table = LEDs[30].ledObject;
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
PinballLED* fiveball_pocket = LEDs[72].ledObject;
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


PinballLED* E_led = LEDs[36].ledObject;
PinballLED* I_led = LEDs[44].ledObject;
PinballLED* G_led = LEDs[45].ledObject;
PinballLED* H_led = LEDs[46].ledObject;
PinballLED* T_led = LEDs[47].ledObject;

PinballLED* Ball_led = LEDs[58].ledObject;
PinballLED* bAll_led = LEDs[57].ledObject;
PinballLED* baLl_led = LEDs[56].ledObject;
PinballLED* balL_led = LEDs[48].ledObject;

//define LED Groups 
char ledArray_lowerrRing[] = {
  80,90,89,88,87,86
};
char ledArrayLowerRingCount = 6;
char ledArrayLowerRingCounter = 0;
bool cycleledLowerRing = true;

char ledArray_special[] = {
  9,23,49,77,80,83
};
char ledSecialCount = 6;

char ledArray_CHAMP[] = {
  82,19,20,21,78
};
char ledArrayCHAMPCount = 5;
bool cycleLedCHAMP = true;

char ledArray_EIGHTBALL[] = {
  36,44,45,46,47,48,56,57,58
};
char ledArrayEIGHTBALLCount = 9;
char ledArrayEIGHTBALLCounter = 0;
bool cycleLedEIGHTBALL = true;

char ledArray_LeftSide[] = {
  13,12,11,10,9,8
};
char ledArrayLeftSideCount = 6;
char ledArrayLeftSideCounter = 0;
bool cycleLedLeftSide = true;

char ledArray_RightSide[] = {
  27,26,25,24,23,22
};
char ledArrayRightSideCount = 6;
char ledArrayRightSideCounter = 0;
bool cycleLedRightSide = true;

char ledArray_TableBalls[] = {
  39,37,34,32,30,42,54,40,14,33,31,29,43,51
};
char ledArrayTableBallsCount = 14;
char ledArrayTableBallsCounter = 0;
bool cycleLedTableBalls = true;

char ledArray_PottedBalls[] = {
  62,64,67,70,72,73,75,63,65,66,69,71,74,76//,68
};
char ledArrayPottedBallsCount = 15;
char ledArrayPottedBallsCounter = 0;
bool cycleLedPottedBalls = true;
bool ledArrayPottedBallsEven = true;


char ledArray_TestBalls[] = {
  62,64//,68
};
char ledArrayTestBallsCount = 2;
char ledArrayTestBallsCounter = 0;
bool cycleLedTestBalls = true;
bool ledArrayTestBallsEven = true;

char ledArray_Spinner[] = {
  15,16,17,17,16,15
};
char ledArraySpinnerCount = 6;
char ledArraySpinnerCounter = 0;
bool cycleLedSpinner = true;
bool ledArraySpinnerEven = true;

char ledArray_FiveThou[] = {
  28,35,38,41,52
};
char ledArrayFiveThouCount = 5;
char ledArrayFiveThouCounter = 0;
bool cycleLedFiveThou = true;
bool ledArrayFiveThouEven = true;

char ledArray_TopLane[] = {
  6,5,4,3,2,2,3,4,5,6
};
char ledArrayTopLaneCount = 10;
char ledArrayTopLaneCounter = 0;
bool cycleLedTopLane = true;
bool ledArrayTopLaneEven = true;

int row0[] = {92};
int row1[] = {88};
int row3[] = {89,87};
int row4[] = {90,86};
int row5[] = {80};
int row6[] = {81,79};
int row7[] = {83,82,68,78,77};
int row8[] = {63,65,66,69,71,74,76};
int row9[] = {62,64,67,70,72,73,75};
int row10[] = {};
int row11[] = {41,60,52};
int row12[] = {42,59,49,54};
int row13[] = {43,58,57,56,48,51};
int row14[] = {39,40,44,45,46,47,36,31,30};
int row15[] = {37,14,34,33,32,29};
int row16[] = {38,35,28};
int row17[] = {13,15,27};
int row18[] = {16,26};
int row19[] = {12,17};
int row20[] = {25};
int row21[] = {11,24};
int row22[] = {10,23};
int row23[] = {9,22};
int row24[] = {8,21,20,19};
int row25[] = {};
int row26[] = {6,5,4,3,2};


const int pfRowCount = 27;
int* playfieldRows[pfRowCount] = {row0, row1, row3, row4, row5, row6, row7, row8, row9, row10, row11, row12, row13, row14, row15, row16, row17, row18, row19, row20, row21, row22, row23, row24, row25, row26};
// Array to hold the size of each row 
int pfArraySize[pfRowCount] = {1,1,2,2,1,
                               2,5,7,7,0,
                               3,4,6,9,6,
                               3,3,2,2,1,
                               2,2,2,4,0,
                               5};
int pfRowCounter = 0;
bool chase_pf_up = false;


