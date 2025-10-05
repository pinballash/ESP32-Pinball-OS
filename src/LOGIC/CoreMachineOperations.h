#include <Arduino.h>

#include "CLASSES/PinballCoil.h"
#include "CLASSES/PinballCoil.h"
#include "CLASSES/PinballLED.h"
#include "CLASSES/PinballGame.h"
//not using audio in this pinball table - commented out
//#include "CLASSES\PinballAudio.h"

PinballGame g_myPinballGame(setting_MachineName);

/* Global Variables Start*/
bool switchDebug = false;
bool coilDebug = false;
bool loopDebug = false;
bool threadDebug = false;
bool srDebug = false;
bool osrDebug = false;
bool generalMODebug = false;
bool memoryStats = false;
unsigned long processSwitchArrayEveryMicroSeconds = (1000000/1000); //1000 times per second
int ledUpdateFrequency = 60;
unsigned long UpdateLedsEveryMicroSeconds = (1000000/ledUpdateFrequency); 
bool runningLeds = false;

//setup array for storing switch active
const int tableRows = 8;//(int8_t)setting_switchMatrixRows; // 0 to 7
const int tableCols = 8;//(int8_t)setting_switchMatrixColumns; // 0 to 4
const int switchCount = tableRows * tableCols;
const int flipperButtons = 2;
bool switchActive[tableCols][tableRows];
bool secondarySwitchActive[8];
bool switchScored[tableCols][tableRows];
char colflipper[flipperButtons]; // flipper button cols
char rowflipper[flipperButtons]; // flipper button rows
unsigned long player1score = 0;
unsigned long player2score = 0;
unsigned long player3score = 0;
unsigned long player4score = 0;
int playfieldMultiplier = 1;

//setup array fo maintaining the state of coils
const int coilCount = 16;
bool coilActive[coilCount];
//bool audioActive[39];

// Define Connections to 74HC595 - Matrix Output Shift Register
const int osr1latchPin = setting_osr1latchPin;
const int osr1clockPin = setting_osr1clockPin;
const int osr1dataPin = setting_osr1dataPin;

// Define Connections to 74HC595 - Audio Output Shift Register
const int osr2latchPin = setting_osr2latchPin;
const int osr2clockPin = setting_osr2clockPin;
const int osr2dataPin = setting_osr2dataPin;

// Define Connections to 74HC595 - Coil Output Shift Registers
const int osr3latchPin = setting_osr3latchPin;
const int osr3clockPin = setting_osr3clockPin;
const int osr3dataPin = setting_osr3dataPin; 

//Comms to 74HC165 - Input Shift Registers
int isrload = setting_isrload;
int isrclockEnablePin = setting_isrclockEnablePin; //latch
int isrdataIn = setting_isrdataIn;
int isrclockIn = setting_isrclockIn;

// input and output bytes for the shift registers
byte incoming;
byte incoming2;
byte outgoing=0; // used for switch matrix - only 5 cols implemented - can expand to 8
byte outgoing2=255; // used for sound, so needs to be all kept high
byte outgoing3=0; // used for solenoids
byte outgoing4=0; //used for solenoids

bool needsRegisterUpdate = false;

//High Voltage Relay pin
//const int hvrPin = 27;
const int hvrPin = setting_hvrPin;

//Flipper 1 pin
//const int flipper1Pin = 34;
const int flipper1Pin = setting_flipper1Pin;

//Flipper 2 pin
//const int flipper2Pin = 35;
const int flipper2Pin = setting_flipper2Pin;

//const int flipper2Pin = 35;
const int ledPin = setting_ledPin;

int counter;
unsigned long lastMillis;

int timerSw;
unsigned long lastMillisTimerSw;

int counterCoil;
unsigned long lastMillisCoil;

/* Global Variables End*/

/* Global Variables From JSON Start*/
#include "SETTINGS/JSON_switchArray.h"
#include "SETTINGS/JSON_coilArray.h"
#include "SETTINGS/flipperBindings_def.h"
#include "SETTINGS/JSON_coilBindings.h"
#include "SETTINGS/JSON_ledArray.h"
//not using audio in this pinball table - commented out
//#include "SETTINGS\JSON_audioArray.h"
/* Global Variables From JSON End*/

//START delcaration of functions within LOGIC\switchHandlingFunctions.h
void ProcessSwitchesAndRulesFunction( void * pvParameters);
void scanSwitchMatrix(); 
void triggerSwitches();
void processAllSwitches();
//END delcaration of functions within LOGIC\switchHandlingFunctions.h

//START delcaration of functions within SHIFT-REGISTERS\shiftRegisterFunctions.h
void ProcessShifts(PinballCoil* CoilObject); 
void read_sr(); 
void write_sr_matrix(); 
void write_sr_coils(); 
void manageCoils(); 
//not using audio in this pinball table - commented out
//void ProcessAudioShifts(PinballAudio* AudioObject); 
//void ResetAudioShifts(); 
//void manageAudio(); 
//void write_sr_audio(); 
//END delcaration of functions within SHIFT-REGISTERS\shiftRegisterFunctions.h

//START delcaration of functions within LOGIC\gameRules-BallyEightBallChamp.h
void switch_event_startbutton(); 
void switch_event_outhole(int switchId); 
void addScore(int switchID);
bool checkChamp(); 
void increaseBonusMultiplier(); 
void increaseSpinnerValue(); 
void resetDrops(); 
void processAllLeds();
void turnOffAllLeds(); 
void setNewBallLEDs(bool dots, bool resetChamp); //sets up playfield lights - dots true, 1-7, false 9-15 
void resetChampLeds(); 
void resetBonusLeds(); 
void resetSpinnerLeds(); 
//END delcaration of functions within LOGIC\gameRules-BallyEightBallChamp.h

//START delcaration of functions within LIGHTING\ledHandlingFunctions.h
void ProcessLedsFunction( void * pvParameters);
//END delcaration of functions within LIGHTING\ledHandlingFunctions.h

void changeState(int newState); //from LOGIC\machineState.h

bool ChimeRing(char coilNum); //from CHIMES\chimeEffects.h
void DoubleTrigger(); //from CHIMES\chimeEffects.h
void Tune1Trigger(); //from CHIMES\chimeEffects.h
void Tune2Trigger(); //from CHIMES\chimeEffects.h
void Tune3Trigger(); //from CHIMES\chimeEffects.h

#include "LOGIC/interupts.h" //here we regualarly (1000 times per second) scan the switch matrix, process the results and then manage the coils

//setup a task handlers
TaskHandle_t ScanSwitchMatrix;
TaskHandle_t ProcessSwitchesAndRules;
TaskHandle_t ProcessLeds;

#include "LOGIC/gameRules-BallyEightBallChamp.h"

#include "SHIFT-REGISTERS/shiftRegisterFunctions.h"

#include "LIGHTING/ledHandlingFunctions.h"

#include "LOGIC/switchHandlingFunctions.h"