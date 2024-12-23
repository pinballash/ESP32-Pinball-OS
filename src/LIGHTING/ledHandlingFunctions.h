#include <Arduino.h>

void ProcessLedsFunction( void * pvParameters)
{
  
  Serial.print("ProcessLedsFunction running on core ");
  Serial.println(xPortGetCoreID());
  unsigned long lastMillisSw = 0;
  unsigned long lastMicrosLoopRan = 0;
  unsigned long scanMicro = 0;
  unsigned long flipperMicro = 0;
  unsigned long triggerSwitchMicro = 0;
  unsigned long manageCoilMicro = 0;
  unsigned long processSwitchMicro = 0;
  unsigned long measureMicro = 0;
  for(;;)
  {
    if((micros() - lastMicrosLoopRan >= UpdateLedsEveryMicroSeconds)) //&& (runningLeds==false))//we must not let this loop run away with itself, rate limiter here
    {
      
      runningLeds = true;
      //do processing
      //Serial.println("Processing LEDs");
      measureMicro = micros();
      processAllLeds();
      processSwitchMicro = processSwitchMicro + (micros() - measureMicro);
      lastMicrosLoopRan = micros();
    }else{
      //release the CPU for processing other tasks
      vTaskDelay(pdMS_TO_TICKS(10)); //yeild
    }  
  }
}

/*
* Function processAllLeds
* loop through all columns and rows and check for a switchScored array values that are true. 
* If a switch is assigned a special designation, like Start, Credit, Outhole or Flipper, action funtions can be called from here
* TODO: If a switch is bound to a coil, without instanfFire, rules will need to be consulted to determine if coil needs to be fired or not
*/
void processAllLeds()
{
  
  if (cycleLedPottedBalls == true)
  {
    //ledArrayPottedBallsEven =  LED_display_oddsAndEvens(ledArray_PottedBalls, ledArrayPottedBallsCount, ledArrayPottedBallsEven, 2);
     ledArrayPottedBallsCounter = LED_display_chase(ledArray_PottedBalls, ledArrayPottedBallsCount, 1, ledArrayPottedBallsCounter);

  }
    
  if (cycleLedEIGHTBALL == true)
  {
    //LED_display_flashBlock(ledArray_EIGHTBALL, ledArrayEIGHTBALLCount, 2);
    ledArrayEIGHTBALLCounter = LED_display_chase(ledArray_EIGHTBALL, ledArrayEIGHTBALLCount, 4, ledArrayEIGHTBALLCounter);
  }

  if (cycleledLowerRing == true)
  {
    //LED_display_flashBlock(ledArray_EIGHTBALL, ledArrayEIGHTBALLCount, 2);
    ledArrayLowerRingCounter = LED_display_chase(ledArray_lowerrRing, ledArrayLowerRingCount, 4, ledArrayLowerRingCounter);
  }
  
  
  if (cycleLedLeftSide == true)
  {
    ledArrayLeftSideCounter = LED_display_chase(ledArray_LeftSide, ledArrayLeftSideCount, 6, ledArrayLeftSideCounter);
  }

  if (cycleLedRightSide == true)
  {
    ledArrayRightSideCounter = LED_display_chase(ledArray_RightSide, ledArrayRightSideCount, 6, ledArrayRightSideCounter);
  }

  if (cycleLedCHAMP == true)
  {
    LED_display_flashBlock(ledArray_CHAMP, ledArrayCHAMPCount, 1);
  }
  
  bool needsReload = false;
  for (byte id = 0; id < NUM_LEDS ; id++) 
  {
    //get the led object and read its state
    PinballLED* thisLed = LEDs[id].ledObject; //get the PinballCoil instance associated
    thisLed->tick();
    if(thisLed->getUpdate() == true)
    {
      needsReload = true;
      if(thisLed->isOn()){
        //Serial.println("LED " + String(id) + " IS ON - Colour: " + thisLed->getColour()+ " R: "+ String(thisLed->getRed()) +" G: "+ String(thisLed->getGreen()) +" B: "+ String(thisLed->getBlue()));
        ledArray[id].setRGB(thisLed->getRed(),thisLed->getGreen(), thisLed->getBlue());  // it only takes effect if pixels.show() is called
        thisLed->setUpdate();
      }else{
        //this led is off
        //Serial.println("LED " + String(id) + " IS OFF");
        ledArray[id] = CRGB::Black; // it only takes effect if pixels.show() is called
        thisLed->setUpdate();
      }
      //FastLED.show();
    }
  }

  if(needsReload == true)
  {
    FastLED.show();  // update to the WS2812B Led Strip
  }
  runningLeds = false;
  //vTaskDelay(5);
}


void turnOnAttractLEDs(){
  cycleLedPottedBalls = true;
  cycleLedEIGHTBALL = true;
  cycleLedLeftSide = true;
  cycleLedRightSide = true;
  cycleLedCHAMP = true;
  cycleledLowerRing = true;
}
void turnOffAllLeds() //literally turn every LED off
{
  cycleLedPottedBalls = false;
  cycleLedEIGHTBALL = false;
  cycleLedLeftSide = false;
  cycleLedRightSide = false;
  cycleLedCHAMP = false;
  cycleledLowerRing = false;


  
  for (byte id = 0; id < NUM_LEDS ; id++) 
  {
    //get the led object and read its state
    PinballLED* thisLed = LEDs[id].ledObject; //get the PinballCoil instance associated
    thisLed->disable();
    thisLed->setFlashSpeed(0);
    thisLed->updateLed();
  }

  
}
void setNewBallLEDs(bool dots) //turns on all table balls for dots or stripes.  If true argument its dots, if false, its stripes.
{

  //if dats = true - we need 1-7 else 9-15
  if(dots == true)
  {
    oneball_table->enable();
    oneball_table->setFlashSpeed(0);
    oneball_table->updateLed();
    
    twoball_table->enable();
    twoball_table->setFlashSpeed(0);
    twoball_table->updateLed();

    threeball_table->enable();
    threeball_table->setFlashSpeed(0);
    threeball_table->updateLed();

    fourball_table->enable();
    fourball_table->setFlashSpeed(0);
    fourball_table->updateLed();

    fiveeball_table->enable();
    fiveeball_table->setFlashSpeed(0);
    fiveeball_table->updateLed();

    sixball_table->enable();
    sixball_table->setFlashSpeed(0);
    sixball_table->updateLed();

    sevenball_table->enable();
    sevenball_table->setFlashSpeed(0);
    sevenball_table->updateLed();


  }else{
    nineball_table->enable();
    nineball_table->setFlashSpeed(0);
    nineball_table->updateLed();
    
    tenball_table->enable();
    tenball_table->setFlashSpeed(0);
    tenball_table->updateLed();

    elevenball_table->enable();
    elevenball_table->setFlashSpeed(0);
    elevenball_table->updateLed();

    twelveball_table->enable();
    twelveball_table->setFlashSpeed(0);
    twelveball_table->updateLed();

    thirteenball_table->enable();
    thirteenball_table->setFlashSpeed(0);
    thirteenball_table->updateLed();

    fourteenball_table->enable();
    fourteenball_table->setFlashSpeed(0);
    fourteenball_table->updateLed();

    fifteenball_table->enable();
    fifteenball_table->setFlashSpeed(0);
    fifteenball_table->updateLed();
  }
  resetChampLeds();

}
void resetChampLeds()
{
  c_champ->enable();
  c_champ->setFlashSpeed(0);
  c_champ->updateLed();

  h_champ->enable();
  h_champ->setFlashSpeed(0);
  h_champ->updateLed();

  a_champ->enable();
  a_champ->setFlashSpeed(0);
  a_champ->updateLed();

  m_champ->enable();
  m_champ->setFlashSpeed(0);
  m_champ->updateLed();

  p_champ->enable();
  p_champ->setFlashSpeed(0);
  p_champ->updateLed();
}


void resetBonusLeds()
{
  twox_bonus->disable();
  twox_bonus->updateLed();

  threex_bonus->disable();
  threex_bonus->updateLed();

  fivex_bonus->disable();
  fivex_bonus->updateLed();
}
void resetSpinnerLeds()

{
  onethousand_spinner->disable();
  onethousand_spinner->updateLed();

  threethousand_spinner->disable();
  threethousand_spinner->updateLed();

  fivethousand_spinner->disable();
  fivethousand_spinner->updateLed();

}
