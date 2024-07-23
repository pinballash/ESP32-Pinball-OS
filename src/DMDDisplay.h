#include <Arduino.h>
//include dependancies
#include <MD_Parola.h> 
#include <MD_MAX72xx.h> 
#include <SPI.h> 

void oneTopOneBottomDisplay(String DMDTopLine, String DMDBottomLine);
void resetDisplay();
void DisplayBootModeFunction(void * pvParameters);
void DisplayControllerFunction(void * pvParameters);

//setup a task handler;
TaskHandle_t DisplayController;
TaskHandle_t DisplayBootMode;
TaskHandle_t DisplayAttractMode;
TaskHandle_t DisplayGameMode;
TaskHandle_t DisplayEndOfBallMode;
TaskHandle_t DisplayEndOfGameMode;
TaskHandle_t DisplayDiagnosticsMode;


// Definitions for the dot matrix score displays
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 24 // to 24 from 16
#define MAX_ZONES   4
#define ZONE_SIZE (MAX_DEVICES/MAX_ZONES)   // integer multiple works best

#define DMCLK_PIN   4
#define DMDATA_PIN  13
#define DMCS_PIN    12

// Hardware SPI connection
MD_Parola DMDDisplay = MD_Parola(HARDWARE_TYPE, DMDATA_PIN, DMCLK_PIN, DMCS_PIN, MAX_DEVICES);


#define SPEED_TIME  10
#define PAUSE_TIME  100

uint8_t curFX = 0;
textEffect_t  effect[] =
{ PA_PRINT,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_WIPE,
  PA_RANDOM,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  PA_FADE,
  PA_OPENING_CURSOR,
  PA_GROW_UP,
  PA_SCROLL_UP_RIGHT,
  PA_BLINDS,
  PA_MESH,
  PA_CLOSING,
  PA_GROW_DOWN,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT,
  PA_WIPE_CURSOR,
  PA_DISSOLVE,
  PA_OPENING,
  PA_CLOSING_CURSOR,
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_RIGHT,
  PA_SLICE,
  PA_SCROLL_DOWN,
  PA_NO_EFFECT // adj added #25
};

void DisplayControllerFunction(void * pvParameters)
{
  resetDisplay();  
  for(;;){
    String DMDTopText = g_myPinballGame.getDMDTopLine();
    String DMDBottomText = g_myPinballGame.getDMDBottomLine();
    ScoreboardTText = DMDTopText;
    ScoreboardBText = DMDBottomText; 
    oneTopOneBottomDisplay(DMDTopText, DMDBottomText);
    vTaskDelay(50);       
  }
}

void resetDisplay() //to be done when changing layout on the display
{
  DMDDisplay.begin(MAX_ZONES);
  DMDDisplay.setInvert(false);
  for (uint8_t i=0; i<MAX_ZONES; i++)
  {
    DMDDisplay.setZone(i, ZONE_SIZE*i, (ZONE_SIZE*(i+1))-1);
  }
}
void oneTopOneBottomDisplay(String DMDTopLine, String DMDBottomLine) // Simple layout with a top line and a bottom line.
{
  DMDDisplay.setZone(0,12,23); // Make zone 0 the whole top display
  char scoreboardTChar[40];
  DMDTopLine.toCharArray(scoreboardTChar, sizeof(scoreboardTChar));
  DMDDisplay.displayZoneText(0,scoreboardTChar,PA_CENTER,0,0,PA_NO_EFFECT,PA_NO_EFFECT);
  
  DMDDisplay.setZone(1,0,11); // Make zone 1 the whole bottom display
  char scoreboardBChar[40];
  DMDBottomLine.toCharArray(scoreboardBChar, sizeof(scoreboardBChar));
  DMDDisplay.displayZoneText(1,scoreboardBChar,PA_CENTER,0,0,PA_NO_EFFECT,PA_NO_EFFECT);

  DMDDisplay.displayAnimate();
}

