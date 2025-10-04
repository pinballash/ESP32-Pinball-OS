#include <Arduino.h>
int LED_display_chase_pf_up(int rowCounter, int maxRows);
int LED_display_chase_flash_pf_up(int rowCounter, int maxRows, int flashesPerSecond);
int LED_display_chase_flash_pf_left(int colCounter, int maxCols, int flashesPerSecond);
int LED_display_chase_pf_down(int rowCounter, int maxRows);
int LED_display_chase_flash_pf_down(int rowCounter, int maxRows, int flashesPerSecond);
int LED_display_chase_flash_pf_right(int colCounter, int maxCols, int flashesPerSecond);
bool LED_display_oddsAndEvens(char LED_ID_array[], char LED_array_length, bool isEven, int flashesPerSecond);
char LED_display_chase(char LED_ID_array[], char LED_array_length, int flashesPerSecond, char counter);
void LED_display_flashBlock(char LED_ID_array[], char LED_array_length, int flashesPerSecond);
void LED_display_chase_snake();

/*
* Function processAllLeds
* 
*/
void processAllLeds()
{
  //this runs at ledUpdateFrequency

  //led patterns that will fire less frequently than this function does
  
  if((micros() - ledUpdateMicros >= (1000000/attractUpdatesPerSecond))) 
  {
    /*
    MachineState of 1 means we are in attract
    If we are in any other machine state, changes to led stus is are handled directly from other logic, however the actual physical execution of led updates happens here
    */
    if(MachineState == 1)
    {
      attractCount++;
      if(attractCount > attractSwitchCount)
      {
        /*
        We are done with the last attact, so we will move to the next
        */
        for (byte id = 0; id < NUM_LEDS ; id++) 
        {
          //get the led object and read its state
          PinballLED* thisLed = LEDs[id].ledObject; //get the PinballCoil instance associated
          thisLed->disable();
          thisLed->resetCalculatedRGB();
          thisLed->setFlashSpeed(0);
          thisLed->updateLed();

          ledArray[id] = CRGB::Black;    

        }
        FastLED.show();
        attractCount = 0;
        /*
        Attract Timing
        move between the attact scenes
        */
        if(attactStage == 0)
        {
          attactStage = 1;
          pfRowCounter = 0;
          attractUpdatesPerSecond = 50;
          attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond;
        }else if(attactStage == 1){
          attactStage = 2;
          attractUpdatesPerSecond = 50;
          pfRowCounter = pfRowCount-1;
          attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond;
        }else if(attactStage == 2){
          attactStage = 3;
          attractUpdatesPerSecond = 24;
          attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond;
        }else if(attactStage == 3){
          attactStage = 4;
          attractUpdatesPerSecond = 24;
          attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond;
        }else if(attactStage == 4){
          attactStage = 5;
          attractUpdatesPerSecond = 24;
          attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond;
        }else if(attactStage == 5){
          attactStage = 6;
          attractUpdatesPerSecond = 24;
          attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond;
        }else if(attactStage == 6){
          attactStage = 0;
          attractUpdatesPerSecond = 12;
          attractSwitchCount = attactSecondsPerScene*attractUpdatesPerSecond;
        }
        /*
        End Attract Timing
        */
      }
      /*
      Process Attract effects
      */
      if(attactStage == 0)
      {
        
        /*
        Update smaller localised effects, based on small LED arrays
        */
        ledArrayPottedBallsCounter = LED_display_chase(ledArray_PottedBalls, ledArrayPottedBallsCount, 3, ledArrayPottedBallsCounter);
        ledArrayTableBallsCounter = LED_display_chase(ledArray_TableBalls, ledArrayTableBallsCount, 1, ledArrayTableBallsCounter);
        ledArrayEIGHTBALLCounter = LED_display_chase(ledArray_EIGHTBALL, ledArrayEIGHTBALLCount, 4, ledArrayEIGHTBALLCounter);
        ledArrayLowerRingCounter = LED_display_chase(ledArray_lowerrRing, ledArrayLowerRingCount, 4, ledArrayLowerRingCounter);
        ledArrayLeftSideCounter = LED_display_chase(ledArray_LeftSide, ledArrayLeftSideCount, 4, ledArrayLeftSideCounter);
        ledArrayRightSideCounter = LED_display_chase(ledArray_RightSide, ledArrayRightSideCount, 4, ledArrayRightSideCounter);
        ledArraySpinnerCounter = LED_display_chase(ledArray_Spinner, ledArraySpinnerCount, 6, ledArraySpinnerCounter);
        ledArrayTopLaneCounter = LED_display_chase(ledArray_TopLane, ledArrayTopLaneCount, 6, ledArrayTopLaneCounter);
        LED_display_flashBlock(ledArray_CHAMP, ledArrayCHAMPCount, 2);
        LED_display_flashBlock(ledArray_FiveThou, ledArrayFiveThouCount, 4);
      }else if(attactStage == 1)
      {
        /*
        Update a sweep of LEDs moving up the playfield
        */
       //do we need to set starting values?  Then do this when the attact mode changes
        pfRowCounter = LED_display_chase_pf_up(pfRowCounter, pfRowCount);
      }else if(attactStage == 2)
      {
        /*
        Update a sweep of LEDs moving down the playfield
        */
        pfRowCounter = LED_display_chase_pf_down(pfRowCounter, pfRowCount);
      }else if(attactStage == 3)
      {
        //LED_display_chase_snake();
        pfColCounter = LED_display_chase_flash_pf_left(pfColCounter, pfColCount, 10);
      }else if(attactStage == 4)
      {
        //LED_display_chase_snake();
        pfColCounter = LED_display_chase_flash_pf_right(pfColCounter, pfColCount, 10);
      }else if(attactStage == 5)
      {
        //LED_display_chase_snake();
        pfColCounter = LED_display_chase_flash_pf_left(pfColCounter, pfColCount, 10);
        pfRowCounter = LED_display_chase_flash_pf_down(pfRowCounter, pfRowCount, 10);
      }else if(attactStage == 6)
      {
        //LED_display_chase_snake();
        pfColCounter = LED_display_chase_flash_pf_right(pfColCounter, pfColCount, 10);
        pfRowCounter = LED_display_chase_flash_pf_up(pfRowCounter, pfRowCount, 10);
      }
      
      ledUpdateMicros = micros();
      /*
      End process atract effects
      */
    } 
  } 
  //ledArrayTestBallsCounter = LED_display_chase(ledArray_TestBalls, ledArrayTestBallsCount, 1, ledArrayTestBallsCounter);
  
  bool needsReload = false;
/*
Actual LED updates now happen here
*/

  for (byte id = 0; id < NUM_LEDS ; id++) 
  {
    //get the led object, process a tick and then and read its state.  If it needs changes, then execute them.
    PinballLED* thisLed = LEDs[id].ledObject; 
    thisLed->tick();
    if((thisLed->getUpdate() == true));
    { 
      needsReload = true;
      if(thisLed->isOn())
      {
        ledArray[id].setRGB(thisLed->getRed(),thisLed->getGreen(), thisLed->getBlue()); 
        thisLed->setUpdate();
      }else{
        //this led is off
        ledArray[id] = CRGB::Black;
        thisLed->setUpdate();
      }
    }
  }

  if(needsReload == true)
  {
    FastLED.show();  // update to the WS2812B Led Strip
  }
  runningLeds = false;
}

int LED_display_chase_pf_up(int rowCounter, int maxRows) //return pfRowCounter
{
  //int* pfLEDArray = playfieldRows[rowCounter];
  for(int i = 0; i < pfColCount; i++)
  {
    
    int ledId = pfMatrix[i][rowCounter];
    if(ledId >-1){
        PinballLED* thisCLed = LEDs[ledId].ledObject;
      if(thisCLed->isEnabled() == false)
      {
        thisCLed->enable();
        thisCLed->setFlashSpeed(0);
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();
      }else{
        thisCLed->disable();
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();      
      }
    }
  }
    
  rowCounter++;
  if(rowCounter < maxRows)
  {
    //do nothing
  }else{
    rowCounter=0;
  }
  return rowCounter;
}

int LED_display_chase_pf_down(int rowCounter, int maxRows) //return pfRowCounter
{
  //int* pfLEDArray = playfieldRows[rowCounter];
  for(int i = 0; i < pfColCount; i++)
  {
    int ledId = pfMatrix[i][rowCounter];
    if(ledId >-1)
    {
      PinballLED* thisCLed = LEDs[ledId].ledObject;
      if(thisCLed->isEnabled() == false)
      {
        thisCLed->enable();
        thisCLed->setFlashSpeed(0);
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();
      }else{
        thisCLed->disable();
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();      
      }
    }
  }
  if(rowCounter > 0)
  {
    rowCounter--;

  }else{
    rowCounter=maxRows-1;
  }
  return rowCounter;
}

int LED_display_chase_flash_pf_up(int rowCounter, int maxRows, int flashesPerSecond) //return pfRowCounter
{
  
  //int* pfLEDArray = playfieldRows[rowCounter];
  for(int i = 0; i < pfColCount; i++)
  {
    
    int ledId = pfMatrix[i][rowCounter];
    if(ledId >-1){
        PinballLED* thisCLed = LEDs[ledId].ledObject;
        thisCLed->flashOnce(flashesPerSecond); 
    }
  }
  
  //convert code to handle led matrix
  /*for(int i = 0; i < pfColCount; i++)
  {
    int* pfLEDArray = pfMatrix[pfColCount][rowCounter];
    int ledId = pfLEDArray[0]; 
    if(ledId >-1){
        PinballLED* thisCLed = LEDs[ledId].ledObject;
        thisCLed->flashOnce(3); 
    }
  }*/
    
  rowCounter++;
  if(rowCounter < maxRows)
  {
    //do nothing
  }else{
    rowCounter=0;
  }
  return rowCounter;
}

int LED_display_chase_flash_pf_down(int rowCounter, int maxRows, int flashesPerSecond) //return pfRowCounter
{
  //int* pfLEDArray = playfieldRows[rowCounter];
  //we need to use the matrix
  
  for(int i = 0; i < pfColCount; i++)
  {
    int ledId = pfMatrix[i][rowCounter];
    if(ledId >-1)
    {
      PinballLED* thisCLed = LEDs[ledId].ledObject;
      thisCLed->flashOnce(flashesPerSecond); 
    }
  }
  if(rowCounter > 0)
  {
    rowCounter--;

  }else{
    rowCounter=maxRows-1;
  }
  return rowCounter;
}


int snakeCol= 0;
int snakeRow =0;

int snakeMaxRows = 42;
int snakeMaxColumns = 15;

bool snakeUp = true;

void LED_display_chase_snake() 
{
  //here we snake up and down the playfield
  //Serial.print("Start: rowCounter = ");
  //Serial.println(rowCounter);

  int myX = 0;
  int myY = 0;
  //if we are moving up....
  if(snakeUp = true)
  {
    //going up
    //check if able to move up?
    if(snakeRow < snakeMaxRows)
    {
      //we are good

    }else{
      //we need to move column and change direction
      snakeUp = false;
      snakeRow--;
      if(snakeCol < snakeMaxColumns-1)
      {
        //space to move
        snakeCol++;
      }else{
        snakeCol=0;
      }
    }
    
    //display
    myX = snakeCol;
    myY = snakeRow;
  }else{
    //going down
    //check if able to go down
    if(snakeRow > -1)
    {
      //we are good

    }else{
      //we need to move column and change direction
      snakeUp = true;
      snakeRow++;
      if(snakeCol < snakeMaxColumns-1)
      {
        //space to move
        snakeCol++;
      }else{
        snakeCol=0;
      }
    }

    //display
    myX = snakeCol;
    myY = snakeRow;

  }
  //display
  //Get LED ID from 

  //make changes
  
}
/*
LED_display_oddsAndEvens
For the led array supplied, process an alternate flash for adds and even leds in the array.  This will need to be executed by another loop, as the function is not a loop itself, just a point in time.
*/
bool LED_display_oddsAndEvens(char LED_ID_array[], char LED_array_length, bool isEven, int flashesPerSecond)
{
  bool isActioned = false;
  for(char ledId = 0; ledId < LED_array_length; ledId++)
    {
      if ((isEven == true) && (ledId % 2) == 0) //if number is even and we are workinh with even
      {
        PinballLED* thisCLed = LEDs[LED_ID_array[ledId]].ledObject;
        if(thisCLed->isEnabled() == false)
        {
          thisCLed->flashOnce(flashesPerSecond); 
          isActioned = true;
        }
      }else if ((isEven == false) && ((ledId % 2) != 0))//its an odd number and we are working with odd
      {
        
        PinballLED* thisCLed = LEDs[LED_ID_array[ledId]].ledObject;
        if(thisCLed->isEnabled() == false)
        {
          thisCLed->flashOnce(flashesPerSecond); 
          isActioned = true;
        }
      }
    }
    if(isActioned == true)
    {
      isEven = !isEven;
    }
    return isEven;
}
/*
LED_display_chase
For the led array supplied, process a chase effect.  This will need to be executed by another loop, as the function is not a loop itself, just a point in time.
*/
char LED_display_chase(char LED_ID_array[], char LED_array_length, int flashesPerPeriod, char counter)
{
  PinballLED* thisCLed = LEDs[LED_ID_array[counter]].ledObject;

  if(thisCLed->flashOnce(flashesPerPeriod) == true)
  {
    counter++;
  }
  if(counter == LED_array_length)
  {
    counter = 0;
  }
  
  return counter;
}

/*
LED_display_flashBlock
For the led array supplied, process a flash effect for all leds at once.  This will need to be executed by another loop, as the function is not a loop itself, just a point in time.
*/
void LED_display_flashBlock(char LED_ID_array[], char LED_array_length, int flashesPerPeriod)
{
  for(char ledId = 0; ledId < LED_array_length; ledId++)
    {
      PinballLED* thisCLed = LEDs[LED_ID_array[ledId]].ledObject;
      if(thisCLed->isEnabled() == false)
      {
        thisCLed->flashOnce(flashesPerPeriod); 
      }
    }
}

int LED_display_chase_flash_pf_left(int colCounter, int maxCols, int flashesPerSecond) //return pfColCounter
{
  //int* pfLEDArray = playfieldCols[colCounter];
  for(int i = 0; i < pfRowCount; i++)
  {
    
    int ledId = pfMatrix[colCounter][i];
    if(ledId >-1){
        PinballLED* thisCLed = LEDs[ledId].ledObject;
      /*if(thisCLed->isEnabled() == false)
      {
        thisCLed->enable();
        thisCLed->setFlashSpeed(0);
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();
      }else{
        thisCLed->disable();
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();      
      }*/
     //if(thisCLed->isEnabled() == false)
     // {
        thisCLed->flashOnce(flashesPerSecond); 
     // }
    }
  }
    
  colCounter++;
  if(colCounter < maxCols)
  {
    //do nothing
  }else{
    colCounter=0;
  }
  return colCounter;
}
int LED_display_chase_flash_pf_right(int colCounter, int maxCols, int flashesPerSecond) //return pfColCounter
{
  //int* pfLEDArray = playfieldCols[colCounter];
  for(int i = 0; i < pfRowCount; i++)
  {
    
    int ledId = pfMatrix[colCounter][i];
    if(ledId >-1){
        PinballLED* thisCLed = LEDs[ledId].ledObject;
      /*if(thisCLed->isEnabled() == false)
      {
        thisCLed->enable();
        thisCLed->setFlashSpeed(0);
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();
      }else{
        thisCLed->disable();
        thisCLed->resetCalculatedRGB();
        thisCLed->updateLed();      
      }*/
     //if(thisCLed->isEnabled() == false)
     // {
        thisCLed->flashOnce(flashesPerSecond); 
     // }
    }
  }
  if(colCounter > 0)
  {
    colCounter--;

  }else{
    colCounter=maxCols-1;
  }
  return colCounter;  
  
}
