#include <Arduino.h>
#include "LIGHTING\ledArrays-BallyEightBallChamp.h"

/*
 * Function switch_event_outhole(int switchId) is a function that manages the logic behing the ball entering teh outhole
 * If the game is active then..
 *    If ballsave is not active, it ends the ball for the current player
 *    If the ballsave is active, it kicks the ball into the outlane
 * If the game is still active, it kicks the ball into the outlane
 * If the game is no longer active, it ends the game
 */
void switch_event_outhole(int switchId)
{
  
  bool isGameActive = g_myPinballGame.isGameActive();
  if(isGameActive == true)
  {
      
    if(g_myPinballGame.isBallSave()==false)
    {
      //ball save dont end ball
      int thisPlayerNumber = g_myPinballGame.getCurrentPlayerNumber();
      g_myPinballGame.endOfBall(g_myPinballGame.getCurrentPlayerNumber());
      ScoreboardBText = "End of ball P" + (String)thisPlayerNumber; //this message isnt going to display for long without a delay - perhaps we need some additional display states to handle this.
      ScoreboardTText = "Next....";
      //do other end of ball stuff - call additional functions here
      g_myPinballGame.resetPlayerSwitchScores(thisPlayerNumber);
      resetBonusLeds();
      resetSpinnerLeds();
      resetChampLeds();
      
    }
    //need to get the coilNumber associated
    byte* coilNumber = switchCoilBindings[(byte)switchId].coilNumber; //get the coil number bound to the switch
    byte coilNumberByte = *coilNumber;
    //only fire if in a game
    Serial.println("[INFO][switch_event_outhole] Outhole switch triggered, game is active");
    if(g_myPinballGame.isGameActive()==true)
    {
      resetDrops();
      if(coilNumberByte >0)
      {
        //Serial.println("[switch_event_outhole] Fire Outhole");
        //Serial.println("[INFO][switch_event_outhole] Outhole firing");
        //Serial.print("[INFO][switch_event_outhole] Coil choice is ");
        //Serial.println(coilNumberByte);
        PinballCoil* switchCoil = coils[coilNumberByte].coilObject;
        if(switchCoil->fireCoil()){
          coilActive[coilNumberByte]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
          ProcessShifts(switchCoil); //action the turning on
          write_sr_coils(); //update shift register
        }
      }else{
        //Serial.println("[WARNING][switch_event_outhole] Outhole switch must be bound to a coil, please do this in the web gui");
      }
      
    }else
    {
      //ok so game was active, now its not, game over calls need to be made
  
      changeState(3); //moving to End of game
      digitalWrite(hvrPin, HIGH);
      turnOffAllLeds();
      turnOnAttractLEDs();
      //Serial.println("[INFO][switch_event_outhole] Thats the last ball, end of game");

      //need much more code here, but ok for now
    }
  }else
  {
    //Do nothing - ball should be here when game not on
    //Serial.println("[INFO][switch_event_outhole] Do nothing - the ball should be here");
  }
}
/*void switch_event_saucer(int switchID)
{
  //saucer code here
  Serial.println("Fire Saucer");
  ScoreboardTText = "Saucer";
  byte coilNumber = 7;
  PinballCoil* switchCoil = coils[coilNumber].coilObject;
  //delay(2000); //hold in saucer for 2 secs
  if(switchCoil->fireCoil()){
    coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
    ProcessShifts(switchCoil); //action the turning on
    write_sr_coils(); //update shift register
  }
  addScore(switchID);
}*/

void switch_event_startbutton(int switchId)
{
  if(MachineState == 1)
  {
    changeState(2);
    //Serial.println("[switch_event_startbutton] Starting Game");
    //digitalWrite(hvrPin, LOW);
    //Serial.println("[switch_event_startbutton] Enabling High Voltage Relay");
    turnOffAllLeds();
    setNewBallLEDs(true);
  } else if(MachineState == 2)
  {//if player1 is still on first ball, add more players
    //Serial.println("[switch_event_startbutton] Add player");
    g_myPinballGame.addPlayer(); //This will add players up to the defined maximum

  } else if(MachineState == 3)
  {//new game
    //Serial.println("[switch_event_startbutton] Starting Another Game");
    changeState(2);
    turnOffAllLeds();
    setNewBallLEDs(true);
  }
}
void addScore(int switchID)
{
  
  int playerNumber = g_myPinballGame.getCurrentPlayerNumber();
  int score = g_myPinballGame.getPlayerSwitchScore(switchID,playerNumber) * g_myPinballGame.getPlayfieldMultiplier();
  int playerscore = g_myPinballGame.getPlayerScore(playerNumber) + score;
  g_myPinballGame.setPlayerScore(playerNumber,playerscore);
  //lets do a different chime for different levels of score
  //<1001 high - coil 11
  //>1000 medium and <3001- coil 12
  //>3001 - coil 14
  char coilid;
  if(score < 1001)
  {
    coilid = 11;
  }else if(score <3001)
  {
    coilid = 12;
  }else{
    coilid = 14;
  }
  ChimeRing(coilid);
}
void resetDrops()
{
  if(g_myPinballGame.checkDropReset() == false)
  {
        for(char x = 7;x < 11;x++){
        PinballCoil* switchCoil = coils[x].coilObject;
        if(switchCoil->fireCoil()){
          coilActive[x]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
          ProcessShifts(switchCoil); //action the turning on
          write_sr_coils(); //update shift register
        }
        vTaskDelay(300);
    }
    PinballCoil* switchCoil = coils[15].coilObject;
    if(switchCoil->fireCoil()){
      coilActive[15]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
      ProcessShifts(switchCoil); //action the turning on
      write_sr_coils(); //update shift register
    }
    g_myPinballGame.setDropStatus(true);
  }



}
bool checkChamp() //returns true is any champ lights are still on.  Returns false if champ lights are all off.
{
  
  if((c_champ->isOn() == false)&&(h_champ->isOn() == false)&&(a_champ->isOn() == false)&&(m_champ->isOn() == false) && (p_champ->isOn() == false))
  {
    return false;
  }
  return true;
  
}
void increaseBonusMultiplier() //setp the bonus multiplier up.
{
  
  if(twox_bonus->isOn() == false)//turn on 2x and spinner value
  {
    twox_bonus->enable();
    twox_bonus->setFlashSpeed(0);
    twox_bonus->updateLed();

  }else if(threex_bonus->isOn() == false)//turn on 3x and spinner value
  {
    threex_bonus->enable();
    threex_bonus->setFlashSpeed(0);
    threex_bonus->updateLed();

  }else if(fivex_bonus->isOn() == false)//tune on 5x and spinner value
  {
    fivex_bonus->enable();
    fivex_bonus->setFlashSpeed(0);
    fivex_bonus->updateLed();
  
  }else{
    //do nothing - bonus maxed out
    if((special_left_outlane->isOn()==false)&&(special_right_outlane->isOn()==false))//turn on left special
    {
      special_left_outlane->enable();
      special_left_outlane->setFlashSpeed(2);
      special_left_outlane->updateLed(); 

    }else if((special_left_outlane->isOn()==true)&&(special_right_outlane->isOn()==false))//turn of left and turn on right special
    {
      special_left_outlane->disable();
      special_left_outlane->updateLed(); 

      special_right_outlane->enable();
      special_right_outlane->setFlashSpeed(2);
      special_right_outlane->updateLed(); 

    }else if((special_left_outlane->isOn()==false)&&(special_right_outlane->isOn()==true))//turn on both lane specials
    {
      special_left_outlane->enable();
      special_left_outlane->setFlashSpeed(2);
      special_left_outlane->updateLed(); 
    }else{
      //do nothing
    }

  }
}
void increaseSpinnerValue()
{
  int playerNumber = g_myPinballGame.getCurrentPlayerNumber();
  if(onethousand_spinner->isOn() == false)//turn on 1000 spinner value
  {
    onethousand_spinner->enable();
    onethousand_spinner->setFlashSpeed(0);
    onethousand_spinner->updateLed();
    g_myPinballGame.setPlayerSwitchScore(24,1000, playerNumber);
  }else if(threethousand_spinner->isOn() == false)//turn on 3000 spinner value
  {  
    threethousand_spinner->enable();
    threethousand_spinner->setFlashSpeed(0);
    threethousand_spinner->updateLed();
    g_myPinballGame.setPlayerSwitchScore(24,3000, playerNumber);
  }else if(fivethousand_spinner->isOn() == false)//turn on 5000 spinner value
  {
    fivethousand_spinner->enable();
    fivethousand_spinner->setFlashSpeed(0);
    fivethousand_spinner->updateLed();
    g_myPinballGame.setPlayerSwitchScore(24,5000, playerNumber);
  }

}



//LEDS


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
