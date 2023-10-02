#include <Arduino.h>
//include dependancies
#include <MD_Parola.h> 
#include <MD_MAX72xx.h> 
#include <SPI.h> 

void oneTopOneBottomDisplay();
void twoTopOneBottomDisplay();
void resetDisplay();
void DisplayControllerFunction(void * pvParameters);
void DisplayBootModeFunction(void * pvParameters);
void DisplayAttractModeFunction(void * pvParameters);
void DisplayGameModeFunction(void * pvParameters);
void DisplayEndOfBallModeFunction(void * pvParameters);
void DisplayEndOfGameModeFunction(void * pvParameters);

//setup a task to run on core 0;
TaskHandle_t DisplayAttractMode;
TaskHandle_t DisplayBootMode;
TaskHandle_t DisplayGameMode;
TaskHandle_t DisplayEndOfGameMode;
TaskHandle_t DisplayController;

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
  static unsigned long displayControllerCounter = 0;
  static unsigned long displayCounterLastMillis = 0;
   for(;;)
   {
    displayControllerCounter++;
    if (millis() - displayCounterLastMillis > 2000 ){
      
        /*Serial.print("DisplayController : CORE ");
        Serial.print(xPortGetCoreID());
        Serial.print(" : is currently running at approimatly ");
        Serial.print(counter/2);
        Serial.println("Hz (full program cycles per second)");*/
    
      core1Hz = counter/2;  
      displayControllerCounter = 0;
      displayCounterLastMillis = millis();
    }
    if((MachineState == 1) && (forceDisplayUpdate == true) && (lastMachineState == 0)) //change from Boot to Atract
    {
      //Serial.println("Deleting DisplayGameMode Task");
      //vTaskDelete(DisplayGameMode);
      Serial.println("Deleting DisplayBootMode Task");
      vTaskDelete(DisplayBootMode);
      resetDisplay();
      xTaskCreatePinnedToCore(DisplayAttractModeFunction, "DisplayAttractMode",10000,NULL,99,&DisplayAttractMode,1);
      forceDisplayUpdate = false;
      Serial.println("Display Changing to Attract Mode");

    }else if((MachineState == 2) && (forceDisplayUpdate == true) && (lastMachineState == 1)) //change from Atract to Game
    {
      //Serial.println("Deleting DisplayGameMode Task");
      //vTaskDelete(DisplayGameMode);
      Serial.println("Deleting AtractMode Task");
      vTaskSuspend(DisplayAttractMode);
      vTaskDelete(DisplayAttractMode);
      resetDisplay();
      xTaskCreatePinnedToCore(DisplayGameModeFunction, "DisplayGameMode", 10000, NULL, 99, &DisplayGameMode,1);
      forceDisplayUpdate = false;
      Serial.println("Display Changing to Attract Mode");

    }else if((MachineState == 1) && (forceDisplayUpdate == true) && (lastMachineState == 3)) //change grom End Game to Attract
    {
      Serial.println("Deleting DisplayGameMode Task");
      vTaskDelete(DisplayEndOfGameMode);
      resetDisplay();
      xTaskCreatePinnedToCore(DisplayAttractModeFunction, "DisplayAttractMode",10000,NULL,99,&DisplayAttractMode,1);
      forceDisplayUpdate = false;
      Serial.println("Display Changing to Attract Mode");

    }else if((MachineState == 2) && (forceDisplayUpdate == true) && (lastMachineState == 3)) //Chamnge from End Game to Game
    {
      Serial.println("Deleting DisplayEOGMode Task");
      vTaskDelete(DisplayEndOfGameMode);
      resetDisplay();
      Serial.println("Creating DisplayGameMode Task");
      xTaskCreatePinnedToCore(DisplayGameModeFunction, "DisplayGameMode", 10000, NULL, 99, &DisplayGameMode,1);
      forceDisplayUpdate = false;
      Serial.println("Display Changing to Game Mode");
    }else if((MachineState == 3) && (forceDisplayUpdate == true) && (lastMachineState == 2)) //Chamnge from Game to End Game
    {
      Serial.println("Deleting DisplayGameMode Task");
      vTaskDelete(DisplayGameMode);
      resetDisplay();
      Serial.println("Creating DisplayEndOfGameMode Task");
      xTaskCreatePinnedToCore(DisplayEndOfGameModeFunction, "DisplayEndOfGameMode", 10000, NULL, 99, &DisplayEndOfGameMode,1);
      forceDisplayUpdate = false;
      Serial.println("Display Changing to End of Game Mode");
    }
    vTaskDelay(10);

     
  }
}
void DisplayBootModeFunction(void * pvParameters)
{
  Serial.println("DisplayBootModeFunction.....");
  resetDisplay();  
  for(;;){
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay();        
  }
}
void DisplayAttractModeFunction(void * pvParameters)
{
  Serial.println("DisplayAttractModeFunction.....");
  int arrayLen = 12;
  static unsigned long atractModeMillis = 0;
  String topTextArray[arrayLen];
  String bottomTextArray[arrayLen];
  topTextArray[0] = "T1";
  bottomTextArray[0] = "B1";

  topTextArray[1] = "T2";
  bottomTextArray[1] = "B2";

  topTextArray[2] = "T3";
  bottomTextArray[2] = "B3";

  topTextArray[3] = "T4";
  bottomTextArray[3] = "B4";

  topTextArray[4] = "T5";
  bottomTextArray[4] = "B5";

  topTextArray[5] = "T6";
  bottomTextArray[5] = "B6";

  topTextArray[6] = "T7";
  bottomTextArray[6] = "B7";

  topTextArray[7] = "T8";
  bottomTextArray[7] = "B8";

  topTextArray[8] = "T9";
  bottomTextArray[8] = "B9";

  topTextArray[9] = "T10";
  bottomTextArray[9] = "B10";

  topTextArray[10] = "T11";
  bottomTextArray[10] = "B11";

  topTextArray[11] = "T12";
  bottomTextArray[11] = "B12";

  int atractCounter = 0;
  resetDisplay();  
  for(;;){

    if (millis() - atractModeMillis > 5000 ){
        
        //every five seconds change display
        Serial.println("Attract mode - next display");
        atractModeMillis = millis();
        if(atractCounter < arrayLen)
        {
          ScoreboardTText = topTextArray[atractCounter];
          ScoreboardBText = bottomTextArray[atractCounter];
          oneTopOneBottomDisplay();
          atractCounter +=1;
        }else{
          atractCounter = 0;
        }
    }
    vTaskDelay(1);

    /*ScoreboardBText = "http://"+ (String)host + ".local";
    ScoreboardTText = "Browser Access";
    oneTopOneBottomDisplay();
    vTaskDelay(5000);
    //resetDisplay(); 
    
    ScoreboardTText = "The Early Gamers";
    ScoreboardBText = "Present";
    oneTopOneBottomDisplay();
    vTaskDelay(5000);
    //resetDisplay(); 
       
    ScoreboardTText = "--The Little Shop";
    ScoreboardBText = "Of Rock--";
    oneTopOneBottomDisplay();
    vTaskDelay(5000);
    //resetDisplay(); 

    ScoreboardTText = "Inspired By";
    ScoreboardBText = "The Arctic Monkeys";
    oneTopOneBottomDisplay();
    vTaskDelay(5000);
    //resetDisplay(); 

    ScoreboardTText = "Theme Design";
    ScoreboardBText = "Lottie";
    oneTopOneBottomDisplay();
    vTaskDelay(5000);
    //resetDisplay(); 

    ScoreboardTText = "Code and Dev";
    ScoreboardBText = "Ash";
    oneTopOneBottomDisplay();
    vTaskDelay(5000);
    //resetDisplay(); 

    ScoreboardTText = "Original Build";
    ScoreboardBText = "AlanJ";
    oneTopOneBottomDisplay();
    vTaskDelay(5000);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "-->Free Play<--";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "Free Play";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "-->Free Play<--";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "Free Play";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "-->Free Play<--";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "Free Play";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "-->Free Play<--";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "Free Play";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "-->Free Play<--";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); 

    ScoreboardTText = "Press Start";
    ScoreboardBText = "Free Play";
    oneTopOneBottomDisplay();
    vTaskDelay(500);
    //resetDisplay(); */
       
  }
}
void DisplayGameModeFunction(void * pvParameters) //more regular updates to cope with changes
{
  Serial.println("DisplayGameModeFunction.....");
  static unsigned long gameModeMillis = 0;
  for(;;){
    if (millis() - gameModeMillis > 500 ){
        //every half second change display
        oneTopOneBottomDisplay();
        gameModeMillis = millis();
    }
    vTaskDelay(50);
  }
  
}
void DisplayEndOfBallModeFunction(void * pvParameters)
{
  for(;;){
    oneTopOneBottomDisplay();
    //vTaskDelay(16); //60Hz display updates
    vTaskDelay(500); //2Hz display updates
    //resetDisplay();
  }
}
void DisplayEndOfGameModeFunction(void * pvParameters)
{
  Serial.println("DisplayEndOfGameModeFunction.....");
  static unsigned long gameModeMillis = 0;
  int arrayLen = 3;
  static unsigned long atractModeMillis = 0;
  String topTextArray[arrayLen];
  String bottomTextArray[arrayLen];
  topTextArray[0] = "Who you gonna call?";
  bottomTextArray[0] = "The Martini police?";

  topTextArray[1] = "I bet that you";
  bottomTextArray[1] = "look good on the";

  topTextArray[2] = "Pinball???";
  bottomTextArray[2] = "Nah!! :)";
  int EOGCounter = 0;
  for(;;){
    if (millis() - gameModeMillis > 1000 ){
        //every second change display
        if(EOGCounter < arrayLen)
        {
          ScoreboardTText = topTextArray[EOGCounter];
          ScoreboardBText = bottomTextArray[EOGCounter];
          oneTopOneBottomDisplay();
          EOGCounter +=1;
        }else{
          changeState(1);
        }
        gameModeMillis = millis();
    }
    vTaskDelay(50);
  }
  
}
void resetDisplay()
{
  //Serial.println("Ressetting display");
  DMDDisplay.begin(MAX_ZONES);
  DMDDisplay.setInvert(false);
  for (uint8_t i=0; i<MAX_ZONES; i++)
  {
    DMDDisplay.setZone(i, ZONE_SIZE*i, (ZONE_SIZE*(i+1))-1);
  }
}

void oneTopOneBottomDisplay()
{
  DMDDisplay.setZone(0,12,23); // Make zone 0 the whole top display
  char scoreboardTChar[40];
  ScoreboardTText.toCharArray(scoreboardTChar, sizeof(scoreboardTChar));
  DMDDisplay.displayZoneText(0,scoreboardTChar,PA_CENTER,0,0,PA_NO_EFFECT,PA_NO_EFFECT);
  
  DMDDisplay.setZone(1,0,11); // Make zone 1 the whole bottom display
  char scoreboardBChar[40];
  ScoreboardBText.toCharArray(scoreboardBChar, sizeof(scoreboardBChar));
  DMDDisplay.displayZoneText(1,scoreboardBChar,PA_CENTER,0,0,PA_NO_EFFECT,PA_NO_EFFECT);

  DMDDisplay.displayAnimate();
}

