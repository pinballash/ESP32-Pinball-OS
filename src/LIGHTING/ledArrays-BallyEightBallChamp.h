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

int pfRow41[] = {-1,-1,-1,-1,-1,-1,6,5,4,3,2,-1,-1,-1,-1};
int pfRow40[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow39[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow38[] = {-1,8,-1,-1,-1,-1,19,-1,20,-1,-1,-1,-1,-1,-1};
int pfRow37[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,-1,-1,-1};
int pfRow36[] = {-1,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1};
int pfRow35[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow34[] = {-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1};
int pfRow33[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow32[] = {-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,-1};
int pfRow31[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow30[] = {-1,-1,12,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,25,-1};
int pfRow29[] = {-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,26,-1,-1};
int pfRow28[] = {-1,-1,13,-1,-1,15,-1,-1,-1,-1,-1,-1,27,-1,-1};
int pfRow27[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow26[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow25[] = {-1,-1,38,-1,-1,-1,-1,35,-1,-1,-1,-1,-1,28,-1};
int pfRow24[] = {-1,-1,-1,37,14,-1,-1,-1,33,-1,-1,-1,29,-1,-1};
int pfRow23[] = {-1,-1,39,40,-1,-1,-1,34,-1,-1,32,31,30,-1,-1};
int pfRow22[] = {-1,-1,-1,-1,-1,36,44,45,46,47,-1,-1,-1,-1,-1};
int pfRow21[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow20[] = {-1,-1,-1,-1,43,-1,58,57,56,48,-1,-1,51,-1,-1};
int pfRow19[] = {-1,-1,-1,42,-1,59,-1,-1,-1,49,-1,54,-1,-1,-1};
int pfRow18[] = {-1,-1,41,-1,-1,-1,-1,60,-1,-1,-1,-1,-1,52,-1};
int pfRow17[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow16[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow15[] = {-1,-1,-1,62,64,-1,67,70,72,-1,-1,75,-1,-1,-1};
int pfRow14[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,73,-1,-1,-1,-1};
int pfRow13[] = {-1,-1,-1,-1,63,65,66,69,71,-1,74,76,-1,-1,-1};
int pfRow12[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow11[] = {-1,83,82,-1,-1,-1,-1,68,-1,-1,-1,-1,78,77,-1};
int pfRow10[] = {-1,-1,-1,-1,-1,81,-1,-1,-1,79,-1,-1,-1,-1,-1};
int pfRow9[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow8[] = {-1,-1,-1,-1,-1,-1,-1,80,-1,-1,-1,-1,-1,-1,-1};
int pfRow7[] = {-1,-1,-1,-1,-1,90,-1,-1,-1,86,-1,-1,-1,-1,-1};
int pfRow6[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow5[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow4[] = {-1,-1,-1,-1,-1,89,-1,-1,-1,87,-1,-1,-1,-1,-1};
int pfRow3[] = {-1,-1,-1,-1,-1,-1,-1,88,-1,-1,-1,-1,-1,-1,-1};
int pfRow2[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow1[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int pfRow0[] = {-1,-1,-1,-1,-1,-1,-1,92,-1,-1,-1,-1,-1,-1,-1};

int pfCol0[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
int pfCol1[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,83,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,10,-1,9,-1,-1,-1,-1};	
int pfCol2[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,82,-1,-1,-1,-1,-1,-1,41,-1,-1,-1,-1,39,-1,38,-1,-1,13,-1,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
int pfCol3[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,42,-1,-1,-1,40,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
int pfCol4[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,63,-1,64,-1,-1,-1,-1,43,-1,-1,-1,14,-1,-1,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
int pfCol5[] = {-1,-1,-1,-1,89,-1,-1,90,-1,-1,81,-1,-1,65,-1,-1,-1,-1,-1,59,-1,-1,36,-1,-1,-1,-1,-1,15,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
int pfCol6[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,66,-1,67,-1,-1,-1,-1,58,-1,44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6};	
int pfCol7[] = {92,-1,-1,88,-1,-1,-1,-1,80,-1,-1,68,-1,69,-1,70,-1,-1,60,-1,57,-1,45,34,-1,35,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,5};	
int pfCol8[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,71,-1,72,-1,-1,-1,-1,56,-1,46,-1,33,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4};	
int pfCol9[] = {-1,-1,-1,-1,87,-1,-1,86,-1,-1,79,-1,-1,-1,-1,-1,-1,-1,-1,49,48,-1,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3};	
int pfCol10[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,74,73,-1,-1,-1,-1,-1,-1,-1,-1,32,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,-1,2};	
int pfCol11[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,76,-1,75,-1,-1,-1,54,-1,-1,-1,31,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
int pfCol12[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,78,-1,-1,-1,-1,-1,-1,-1,-1,51,-1,-1,30,29,-1,-1,-1,27,26,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,-1};	
int pfCol13[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,77,-1,-1,-1,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,25,-1,24,-1,23,-1,-1,-1,-1,-1,-1};	
int pfCol14[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

const int pfRowCount = 42;
const int pfColCount = 15;

int* pfMatrix[pfColCount][pfRowCount] = {
  pfCol0,
  pfCol1,
  pfCol2,
  pfCol3,
  pfCol4,
  pfCol5,
  pfCol6,
  pfCol7,
  pfCol8,
  pfCol9,
  pfCol10,
  pfCol11,
  pfCol12,
  pfCol13,
  pfCol14
};

int* playfieldRows[pfRowCount] = {pfRow0,pfRow1,pfRow2,pfRow3,pfRow4,pfRow5,pfRow6,pfRow7,pfRow8,pfRow9,pfRow10,pfRow11,pfRow12,pfRow13,pfRow14,pfRow15,pfRow16,pfRow17,pfRow18,pfRow19,pfRow20,pfRow21,pfRow22,pfRow23,pfRow24,pfRow25,pfRow26,pfRow27,pfRow28,pfRow29,pfRow30,pfRow31,pfRow32,pfRow33,pfRow34,pfRow35,pfRow36,pfRow37,pfRow38,pfRow39,pfRow40,pfRow41};
int* playfieldCols[pfColCount] = {pfCol0,pfCol1,pfCol2,pfCol3,pfCol4,pfCol5,pfCol6,pfCol7,pfCol8,pfCol9,pfCol10,pfCol11,pfCol12,pfCol13,pfCol14};
int pfRowCounter = 0;
int pfColCounter = 0;
bool chase_pf_up = false;

