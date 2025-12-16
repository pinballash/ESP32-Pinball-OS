#include <Arduino.h>

int WEBHz = 0;
int CMOHz = 0;
int DisplayControllerHz = 0;
bool webOn = true;//set to false to ensure the machine works well - ie: leds arent disrupted by the web
bool chimesOn = true;

unsigned long lastMillisSwINT = 0;
unsigned long lastMillisFlip1 = 0;
int INTHz = 0;
int reportedSwitchMatrixHz = 0;
bool scanInProgress = false;
bool flip1Enabled = false;
bool flip2Enabled= false;
bool flip1Released = true;
bool flip2Released= true;

int LED_CPU_Core_Selection = 0;
int LED_CPU_Task_Priority = 24;
int LED_Task_Mem_Alloc = 5000;

int DISPLAY_CPU_Core_Selection = 0;
int DISPLAY_CPU_Task_Priority = 32;
int DISPLAY_Task_Mem_Alloc = 5000;

int RULES_CPU_Core_Selection = 0;
int RULES_CPU_Task_Priority = 25;
int RULES_Task_Mem_Alloc = 5000;

int WEB_CPU_Core_Selection = 1;
int WEB_CPU_Task_Priority = 50;
int WEB_Task_Mem_Alloc = 20000;

int WiFi_CPU_Core_Selection = 0;
int WiFi_CPU_Task_Priority = 49;
int WiFi_Task_Mem_Alloc = 5000;

int MachineState = 0; //this can be Bootup-0, Atract-1, Game-2, End Game-3, End Ball-4
int lastMachineState = 0;
bool forceDisplayUpdate = false;
bool WifiConnected = false;
bool wifiSoftAPInUse = false;
IPAddress localIP;
String localIPURL;	 // a string version of the local IP with http, used for redirecting clients to your webpage

String ScoreboardTText = "";
String ScoreboardTRText = "";
String ScoreboardTLText = "";
String ScoreboardBText = "";

String tso_PinballGame = "";
String tso_PinballSwitch = "";
String tso_PinballCoil = "";
String tso_PinballDisplay = "";
String tso_SwitchesAndRules = "";
String tso_PinballAudio = "";
String tso_Webserver = "";

unsigned long mainLoopMillis = 0;
unsigned long ledUpdateMicros = 0;

int attractStage = 3;
int attractCount = 0;

int attractUpdatesPerSecond = 30;
int attactSecondsPerScene = 1;
int attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond; //10 seconds

bool WifiOnline = false;