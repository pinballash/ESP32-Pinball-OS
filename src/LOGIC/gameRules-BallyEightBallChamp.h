#include <Arduino.h>
#include "LIGHTING\ledArrays-BallyEightBallChamp.h"

bool triggerBonusMultiplierIncrease = false; 
bool triggerSpinnerValueIncrease = false;
bool triggerPlayfieldMultiplierIncrease = false;

void resetBallLEDs();
void bonusCountdown();
void addBonus(int scoreValue, int multipler);
void fireBonusLed(PinballLED* LED, int score, int multiplier);
void resetPlayfieldMultiplierLeds();

void LED_display_chase_pf();
bool LED_display_oddsAndEvens(char LED_ID_array[], char LED_array_length, bool isEven, int flashesPerSecond);
char LED_display_chase(char LED_ID_array[], char LED_array_length, int flashesPerSecond, char counter);
void LED_display_flashBlock(char LED_ID_array[], char LED_array_length, int flashesPerSecond);

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
    //To Do: need additional check here to ensure its not a phantom trigger, so double check switch activated  
    if(g_myPinballGame.isBallSave()==false)
    {
      //ball save dont end ball
      bonusCountdown();
      int thisPlayerNumber = g_myPinballGame.getCurrentPlayerNumber();
      g_myPinballGame.endOfBall(g_myPinballGame.getCurrentPlayerNumber());
      //do other end of ball stuff - call additional functions here
      g_myPinballGame.resetPlayerSwitchScores(thisPlayerNumber);
      g_myPinballGame.setPlayfieldMultiplier(1);
      resetBonusLeds();
      resetSpinnerLeds();
      resetChampLeds();
      resetPlayfieldMultiplierLeds();
      //calculatebonus();
         
      
    }
    //need to get the coilNumber associated
    byte* coilNumber = switchCoilBindings[(byte)switchId].coilNumber; //get the coil number bound to the switch
    byte coilNumberByte = *coilNumber;
    //only fire if in a game
    //Serial.println("[INFO][switch_event_outhole] Outhole switch triggered, game is active");
    if(g_myPinballGame.isGameActive()==true)
    {
      resetDrops();
      turnOffAllLeds();
      if((g_myPinballGame.getCurrentPlayerNumber() == 1)||(g_myPinballGame.getCurrentPlayerNumber() == 3))
      {
        setNewBallLEDs(true, true);
      }else{
        setNewBallLEDs(false, true);
      }  
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
void switch_event_saucer(int switchId)
{
  //saucer code here
  //Serial.println("Fire Saucer");

  //ScoreboardTText = "Saucer";
  byte* coilNumber = switchCoilBindings[(byte)switchId].coilNumber; //get the coil number bound to the switch
  byte coilNumberByte = *coilNumber;
  PinballCoil* switchCoil = coils[coilNumberByte].coilObject; //get the PinballCoil instance associated
  if(MachineState == 2) //only if game is active
  {
    Serial.println("Saucer");
    triggerBonusMultiplierIncrease = true;
    if(eightball_table->isEnabled()==true)
    {
      Serial.println("8 Ball was lit");
      eightball_table->disable();
      eightball_table->updateLed(); 
      eightball_pocket->disable();
      eightball_pocket->updateLed();

      Tune1Trigger();
      resetDrops();

      if(onehundredtwentythousand_bonus->isEnabled() == false)
      {
        onehundredtwentythousand_bonus->enable();
        onehundredtwentythousand_bonus->resetCalculatedRGB();
        onehundredtwentythousand_bonus->setFlashSpeed(0);
        onehundredtwentythousand_bonus->updateLed(); 

      }else if(twohundredfortythousand_bonus->isEnabled() == false)
      {
        twohundredfortythousand_bonus->enable();
        twohundredfortythousand_bonus->resetCalculatedRGB();
        twohundredfortythousand_bonus->setFlashSpeed(0);
        twohundredfortythousand_bonus->updateLed(); 

      }else if(special_big->isEnabled() == false)
      {
        special_big->enable();
        special_big->resetCalculatedRGB();
        special_big->setFlashSpeed(0);
        special_big->updateLed();
      }
      if((g_myPinballGame.getCurrentPlayerNumber()==1)||(g_myPinballGame.getCurrentPlayerNumber()==3))
      {
        setNewBallLEDs(true, false);
      }else{
        setNewBallLEDs(false, false);
      }
      resetBallLEDs();
      vTaskDelay(1000);
    }
    else{
      Serial.println("8 Ball was not lit");
      vTaskDelay(1000);
    }
    
    if(switchCoil->fireCoil())
    { //try and fire the coil
      coilActive[coilNumberByte]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
      ProcessShifts(switchCoil); //set shift register bytes to turn on solenoid
      write_sr_coils(); //update shift register
      //todo: add score and other mode logic
    }

    addScore(switchId);


  }
  
}

void switch_event_startbutton()
{
  if(MachineState == 1)
  {
    changeState(2);
    //Serial.println("[switch_event_startbutton] Starting Game");
    //digitalWrite(hvrPin, LOW);
    //Serial.println("[switch_event_startbutton] Enabling High Voltage Relay");
    turnOffAllLeds();
    setNewBallLEDs(true, true);
  } else if(MachineState == 2)
  {//if player1 is still on first ball, add more players
    //Serial.println("[switch_event_startbutton] Add player");
    g_myPinballGame.addPlayer(); //This will add players up to the defined maximum

  } else if(MachineState == 3)
  {//new game
    //Serial.println("[switch_event_startbutton] Starting Another Game");
    changeState(2);
    turnOffAllLeds();
    setNewBallLEDs(true, true);
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
void addBonus(int scoreValue, int multiplier)
{
  int playerNumber = g_myPinballGame.getCurrentPlayerNumber();
  int playerscore = g_myPinballGame.getPlayerScore(playerNumber) + scoreValue;
  g_myPinballGame.setPlayerScore(playerNumber,playerscore);
  //lets do a different chime for different levels of score
  //<1001 high - coil 11
  //>1000 medium and <3001- coil 12
  //>3001 - coil 14
  char coilid;
  if(scoreValue < 15001)
  {
    coilid = 11;
  }else if(scoreValue <120001)
  {
    coilid = 12;
  }else{
    coilid = 14;
  }
  for(int i=1;i<=multiplier;i++){
    int playerNumber = g_myPinballGame.getCurrentPlayerNumber();
    int playerscore = g_myPinballGame.getPlayerScore(playerNumber) + scoreValue;
    g_myPinballGame.setPlayerScore(playerNumber,playerscore);
    ChimeRing(coilid);
    vTaskDelay(100);
  }
  
}
void resetDrops()
{
  bool complete = true;
  if(g_myPinballGame.checkDropReset() == false)
  {
    //check E
    if(switches[31].switchObject->hasFired()==true)
    {
      //switch has been triggered, reset and send up the drop
      Serial.println("I Drop is on - need to reset");
      PinballCoil* switchCoil = coils[7].coilObject;
      if(switchCoil->fireCoil()){
        coilActive[7]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
        ProcessShifts(switchCoil); //action the turning on
        write_sr_coils(); //update shift register
      }
      vTaskDelay(250);
      switches[31].switchObject->reEnable();
      complete = false;
    }

    //check I
    if(switches[29].switchObject->hasFired()==true)
    {
      //switch has been triggered, reset and send up the drop
      Serial.println("G Drop is on - need to reset");
      PinballCoil* switchCoil = coils[8].coilObject;
      if(switchCoil->fireCoil()){
        coilActive[8]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
        ProcessShifts(switchCoil); //action the turning on
        write_sr_coils(); //update shift register
      }
      vTaskDelay(250);
      switches[29].switchObject->reEnable();
      complete = false;
    }

    //check G
    if(switches[28].switchObject->hasFired()==true)
    {
      //switch has been triggered, reset and send up the drop
      Serial.println("H Drop is on - need to reset");
      PinballCoil* switchCoil = coils[9].coilObject;
      if(switchCoil->fireCoil()){
        coilActive[9]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
        ProcessShifts(switchCoil); //action the turning on
        write_sr_coils(); //update shift register
      }
      vTaskDelay(250);
      switches[28].switchObject->reEnable();
      complete = false;
    }

    //check H
    if(switches[26].switchObject->hasFired()==true)
    {
      //switch has been triggered, reset and send up the drop
      Serial.println("E Drop is on - need to reset");
      PinballCoil* switchCoil = coils[10].coilObject;
      if(switchCoil->fireCoil()){
        coilActive[10]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
        ProcessShifts(switchCoil); //action the turning on
        write_sr_coils(); //update shift register
      }
      vTaskDelay(250);
      switches[26].switchObject->reEnable();
      complete = false;
    }

    //check T
    if(switches[25].switchObject->hasFired()==true)
    {
      //switch has been triggered, reset and send up the drop
      Serial.println("T Drop is on - need to reset");
      PinballCoil* switchCoil = coils[15].coilObject;
      if(switchCoil->fireCoil()){
        coilActive[15]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
        ProcessShifts(switchCoil); //action the turning on
        write_sr_coils(); //update shift register
      }
      vTaskDelay(250);
      switches[25].switchObject->reEnable();
      complete = false;
    }
    
    if(complete == true)
    {
      Serial.println("Drops reset");
      g_myPinballGame.setDropStatus(true);
    }else{
      Serial.println("Drops needed reseting, reprocessing to check");
      vTaskDelay(500);
      resetDrops();
    }
    
  }



}

bool resetDrop(int coilId, int switchId)
{
  bool complete = true;
  
    if(switches[switchId].switchObject->hasFired()==true)
    {
      //switch has been triggered, reset and send up the drop
      Serial.println("Drop is on - need to reset");
      PinballCoil* switchCoil = coils[coilId].coilObject;
      if(switchCoil->fireCoil()){
        coilActive[coilId]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
        ProcessShifts(switchCoil); //action the turning on
        write_sr_coils(); //update shift register
      }
      vTaskDelay(250);
      switches[switchId].switchObject->reEnable();
      complete = false;
    }
    if(complete == true)
    {
      Serial.println("Drop reset");
      return true;
    }else{
      Serial.println("Drop needed reseting, reprocessing to check");
      vTaskDelay(250);
      resetDrop(coilId, switchId);
    }
    return true;

}
bool checkChamp() //returns true is any champ lights are still on.  Returns false if champ lights are all off.
{
  
  if((c_champ->isEnabled() == false)&&(h_champ->isEnabled() == false)&&(a_champ->isEnabled() == false)&&(m_champ->isEnabled() == false) && (p_champ->isEnabled() == false))
  {
    return false;
  }
  return true;
  
}

void checkEightBall() 
{
  
  if(eightball_pocket->isEnabled() == false)
  {
    if(((g_myPinballGame.getCurrentPlayerNumber()==1)||(g_myPinballGame.getCurrentPlayerNumber()==3))&&
        (oneball_pocket->isEnabled()==true)&&
        (twoball_pocket->isEnabled()==true)&&
        (threeball_pocket->isEnabled()==true)&&
        (fourball_pocket->isEnabled()==true)&&
        (fiveball_pocket->isEnabled()==true)&&
        (sixball_pocket->isEnabled()==true)&&
        (sevenball_pocket->isEnabled()==true)
    )
    {
      //player 1 or 3 with all balls potted and EightBall is not on
      eightball_table->enable();
      eightball_table->resetCalculatedRGB();
      eightball_table->setFlashSpeed(0);
      eightball_table->updateLed(); 

      eightball_pocket->enable();
      eightball_pocket->resetCalculatedRGB();
      eightball_pocket->setFlashSpeed(2);
      eightball_pocket->updateLed(); 
    }else
      if(((g_myPinballGame.getCurrentPlayerNumber()==2)||(g_myPinballGame.getCurrentPlayerNumber()==4))&&
        (nineball_pocket->isEnabled()==true)&&
        (tenball_pocket->isEnabled()==true)&&
        (elevenball_pocket->isEnabled()==true)&&
        (twelveball_pocket->isEnabled()==true)&&
        (thirteenball_pocket->isEnabled()==true)&&
        (fourteenball_pocket->isEnabled()==true)&&
        (fifteenball_pocket->isEnabled()==true)
    )
    {
      //player 1 or 3 with all balls potted and EightBall is not on
      eightball_table->enable();
      eightball_table->resetCalculatedRGB();
      eightball_table->setFlashSpeed(0);
      eightball_table->updateLed(); 

      eightball_pocket->enable();
      eightball_pocket->resetCalculatedRGB();
      eightball_pocket->setFlashSpeed(2);
      eightball_pocket->updateLed(); 
    }

  }
  
}

bool checkBallWord()
{
  if(Ball_led->isEnabled()==false)
  {
    Ball_led->enable();
    Ball_led->resetCalculatedRGB();
    Ball_led->setFlashSpeed(0);
    Ball_led->updateLed(); 
    return true;
  }else if(bAll_led->isEnabled()==false)
  {
    bAll_led->enable();
    bAll_led->resetCalculatedRGB();
    bAll_led->setFlashSpeed(0);
    bAll_led->updateLed(); 
    return true;
  }else if(baLl_led->isEnabled()==false)
  {
    baLl_led->enable();
    baLl_led->resetCalculatedRGB();
    baLl_led->setFlashSpeed(0);
    baLl_led->updateLed(); 
    return true;
  }else if(balL_led->isEnabled()==false)
  {
    balL_led->enable();
    balL_led->resetCalculatedRGB();
    balL_led->setFlashSpeed(0);
    balL_led->updateLed(); 
    return true;
  }else{
    return false;
  }
}
void checkEightWord()
{
  if((E_led->isEnabled()==true) && (I_led->isEnabled()==true) && (G_led->isEnabled()==true) && (H_led->isEnabled()==true) && (T_led->isEnabled()==true))
  {
    vTaskDelay(500);
    if(checkBallWord() == true)
    {
      E_led->disable();
      E_led->updateLed();

      I_led->disable();
      I_led->updateLed(); 

      G_led->disable();
      G_led->updateLed(); 

      H_led->disable();
      H_led->updateLed(); 

      T_led->disable();
      T_led->updateLed(); 
    }
  } 
}
void increaseBonusMultiplier() //setp the bonus multiplier up.
{
  
  if(twox_bonus->isEnabled() == false)//turn on 2x and spinner value
  {
    twox_bonus->enable();
    twox_bonus->resetCalculatedRGB();
    twox_bonus->setFlashSpeed(0);
    twox_bonus->updateLed();

  }else if(threex_bonus->isEnabled() == false)//turn on 3x and spinner value
  {
    threex_bonus->enable();
    threex_bonus->resetCalculatedRGB();
    threex_bonus->setFlashSpeed(0);
    threex_bonus->updateLed();

  }else if(fivex_bonus->isEnabled() == false)//tune on 5x and spinner value
  {
    fivex_bonus->enable();
    fivex_bonus->resetCalculatedRGB();
    fivex_bonus->setFlashSpeed(0);
    fivex_bonus->updateLed();
  
  }else{
    //do nothing - bonus maxed out
    if((special_left_outlane->isEnabled()==false)&&(special_right_outlane->isEnabled()==false))//turn on left special
    {
      special_left_outlane->enable();
      special_left_outlane->setFlashSpeed(2);
      special_left_outlane->updateLed(); 

    }else if((special_left_outlane->isEnabled()==true)&&(special_right_outlane->isEnabled()==false))//turn of left and turn on right special
    {
      special_left_outlane->disable();
      special_left_outlane->updateLed(); 

      special_right_outlane->enable();
      special_right_outlane->setFlashSpeed(2);
      special_right_outlane->updateLed(); 

    }else if((special_left_outlane->isEnabled()==false)&&(special_right_outlane->isEnabled()==true))//turn on both lane specials
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
  if(onethousand_spinner->isEnabled() == false)//turn on 1000 spinner value
  {
    onethousand_spinner->enable();
    onethousand_spinner->resetCalculatedRGB();
    onethousand_spinner->setFlashSpeed(0);
    onethousand_spinner->updateLed();
    g_myPinballGame.setPlayerSwitchScore(24,1000, playerNumber);
  }else if(threethousand_spinner->isEnabled() == false)//turn on 3000 spinner value
  {  
    threethousand_spinner->enable();
    threethousand_spinner->resetCalculatedRGB();
    threethousand_spinner->setFlashSpeed(0);
    threethousand_spinner->updateLed();
    g_myPinballGame.setPlayerSwitchScore(24,3000, playerNumber);
  }else if(fivethousand_spinner->isEnabled() == false)//turn on 5000 spinner value
  {
    fivethousand_spinner->enable();
    fivethousand_spinner->resetCalculatedRGB();
    fivethousand_spinner->setFlashSpeed(0);
    fivethousand_spinner->updateLed();
    g_myPinballGame.setPlayerSwitchScore(24,5000, playerNumber);
  }

}

void increasePlayfieldMultiplier()
{
  if(double_playfield->isEnabled() == false)//turn on 2x and spinner value
  {
    double_playfield->enable();
    double_playfield->resetCalculatedRGB();
    double_playfield->setFlashSpeed(2);
    double_playfield->updateLed();
    g_myPinballGame.setPlayfieldMultiplier(2);

  }else if(triple_playfield->isEnabled() == false)//turn on 3x and spinner value
  {
    
    triple_playfield->enable();
    triple_playfield->resetCalculatedRGB();
    triple_playfield->setFlashSpeed(2);
    triple_playfield->updateLed();
    g_myPinballGame.setPlayfieldMultiplier(3);
    
    double_playfield->disable();
    double_playfield->updateLed();

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
  //this runs at ledUpdateFrequency

 
  //led patterns that will fire less frequently than this function does
  
  if((micros() - ledUpdateMicros >= (1000000/10))) //10 times a second
  {
    if (cycleLedPottedBalls == true)
    {
      ledArrayPottedBallsCounter = LED_display_chase(ledArray_PottedBalls, ledArrayPottedBallsCount, 3, ledArrayPottedBallsCounter);
    } 

    if (cycleLedTableBalls == true)
    {
      ledArrayTableBallsCounter = LED_display_chase(ledArray_TableBalls, ledArrayTableBallsCount, 1, ledArrayTableBallsCounter);
    } 

    if (cycleLedEIGHTBALL == true)
    {
      ledArrayEIGHTBALLCounter = LED_display_chase(ledArray_EIGHTBALL, ledArrayEIGHTBALLCount, 4, ledArrayEIGHTBALLCounter);
    }
    if (cycleledLowerRing == true)
    {
      ledArrayLowerRingCounter = LED_display_chase(ledArray_lowerrRing, ledArrayLowerRingCount, 4, ledArrayLowerRingCounter);
    }
    
    if (cycleLedLeftSide == true)
    {
      ledArrayLeftSideCounter = LED_display_chase(ledArray_LeftSide, ledArrayLeftSideCount, 4, ledArrayLeftSideCounter);
    }

    if (cycleLedRightSide == true)
    {
      ledArrayRightSideCounter = LED_display_chase(ledArray_RightSide, ledArrayRightSideCount, 4, ledArrayRightSideCounter);
    }
    
    if (cycleLedSpinner== true)
    {
      ledArraySpinnerCounter = LED_display_chase(ledArray_Spinner, ledArraySpinnerCount, 6, ledArraySpinnerCounter);
    }

    
    if (cycleLedTopLane== true)
    {
      ledArrayTopLaneCounter = LED_display_chase(ledArray_TopLane, ledArrayTopLaneCount, 6, ledArrayTopLaneCounter);
    }

    if (cycleLedCHAMP == true)
    {
      LED_display_flashBlock(ledArray_CHAMP, ledArrayCHAMPCount, 2);
    }

    if (cycleLedFiveThou == true)
    {
      LED_display_flashBlock(ledArray_FiveThou, ledArrayFiveThouCount, 4);
    }

    ledUpdateMicros = micros();


    
  } 
  //ledArrayTestBallsCounter = LED_display_chase(ledArray_TestBalls, ledArrayTestBallsCount, 1, ledArrayTestBallsCounter);
  
  bool needsReload = false;
  for (byte id = 0; id < NUM_LEDS ; id++) 
  {
    //get the led object and read its state
    PinballLED* thisLed = LEDs[id].ledObject; 
    thisLed->tick();
    if((thisLed->getUpdate() == true));// && (thisLed->isEnabled() == true))
    { 
      //Serial.println("[LED class] Update "+ (String)thisLed->getUpdate() + " enabled "+thisLed->isEnabled());
      needsReload = true;
      if(thisLed->isOn())
      {
        ledArray[id].setRGB(thisLed->getRed(),thisLed->getGreen(), thisLed->getBlue()); 
        thisLed->setUpdate();
        //Serial.println("[LED]"+thisLed->getName()+",on,initiated");
      }else{
        //this led is off
        ledArray[id] = CRGB::Black;
        thisLed->setUpdate();
        //Serial.println("[LED]"+thisLed->getName()+",off,initiated");
      }
    }
  }

  if(needsReload == true)
  {
    FastLED.show();  // update to the WS2812B Led Strip
  }
  runningLeds = false;
}


void turnOnAttractLEDs(){
  cycleLedPottedBalls = true;
  cycleLedEIGHTBALL = true;
  cycleLedLeftSide = true;
  cycleLedRightSide = true;
  cycleLedCHAMP = true;
  cycleledLowerRing = true;
  cycleLedTableBalls = true;
  cycleLedSpinner = true;
  cycleLedFiveThou = true;
  cycleLedTopLane = true;
}
void turnOffAllLeds() //literally turn every LED off
{
  //pause led processing
  vTaskSuspend(ProcessLeds);
  
  cycleLedPottedBalls = false;
  cycleLedEIGHTBALL = false;
  cycleLedLeftSide = false;
  cycleLedRightSide = false;
  cycleLedCHAMP = false;
  cycleledLowerRing = false;
  cycleLedTableBalls = false;
  cycleLedSpinner = false;
  cycleLedFiveThou = false;
  cycleLedTopLane = false;
  
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
  vTaskResume(ProcessLeds);

  
}
void setNewBallLEDs(bool dots, bool resetChamp) //turns on all table balls for dots or stripes.  If true argument its dots, if false, its stripes.
{

  //if dats = true - we need 1-7 else 9-15
  if(dots == true)
  {
    oneball_table->enable();
    oneball_table->resetCalculatedRGB();
    oneball_table->setFlashSpeed(0);
    oneball_table->updateLed();
    
    twoball_table->enable();
    twoball_table->resetCalculatedRGB();
    twoball_table->setFlashSpeed(0);
    twoball_table->updateLed();

    threeball_table->enable();
    threeball_table->resetCalculatedRGB();
    threeball_table->setFlashSpeed(0);
    threeball_table->updateLed();

    fourball_table->enable();
    fourball_table->resetCalculatedRGB();
    fourball_table->setFlashSpeed(0);
    fourball_table->updateLed();

    fiveball_table->enable();
    fiveball_table->resetCalculatedRGB();
    fiveball_table->setFlashSpeed(0);
    fiveball_table->updateLed();

    sixball_table->enable();
    sixball_table->resetCalculatedRGB();
    sixball_table->setFlashSpeed(0);
    sixball_table->updateLed();

    sevenball_table->enable();
    sevenball_table->resetCalculatedRGB();
    sevenball_table->setFlashSpeed(0);
    sevenball_table->updateLed();


  }else{
    nineball_table->enable();
    nineball_table->resetCalculatedRGB();
    nineball_table->setFlashSpeed(0);
    nineball_table->updateLed();
    
    tenball_table->enable();
    tenball_table->resetCalculatedRGB();
    tenball_table->setFlashSpeed(0);
    tenball_table->updateLed();

    elevenball_table->enable();
    elevenball_table->resetCalculatedRGB();
    elevenball_table->setFlashSpeed(0);
    elevenball_table->updateLed();

    twelveball_table->enable();
    twelveball_table->resetCalculatedRGB();
    twelveball_table->setFlashSpeed(0);
    twelveball_table->updateLed();

    thirteenball_table->enable();
    thirteenball_table->resetCalculatedRGB();
    thirteenball_table->setFlashSpeed(0);
    thirteenball_table->updateLed();

    fourteenball_table->enable();
    fourball_table->resetCalculatedRGB();
    fourteenball_table->setFlashSpeed(0);
    fourteenball_table->updateLed();

    fifteenball_table->enable();
    fifteenball_table->resetCalculatedRGB();
    fifteenball_table->setFlashSpeed(0);
    fifteenball_table->updateLed();
  }
  if(resetChamp==true)
  {
    resetChampLeds();
  }
  

}
void resetChampLeds()
{
  c_champ->enable();
  c_champ->resetCalculatedRGB();
  c_champ->setFlashSpeed(0);
  c_champ->updateLed();

  h_champ->enable();
  h_champ->resetCalculatedRGB();
  h_champ->setFlashSpeed(0);
  h_champ->updateLed();

  a_champ->enable();
  a_champ->resetCalculatedRGB();
  a_champ->setFlashSpeed(0);
  a_champ->updateLed();

  m_champ->enable();
  m_champ->resetCalculatedRGB();
  m_champ->setFlashSpeed(0);
  m_champ->updateLed();

  p_champ->enable();
  p_champ->resetCalculatedRGB();
  p_champ->setFlashSpeed(0);
  p_champ->updateLed();
}

void resetPlayfieldMultiplierLeds()
{
  double_playfield->disable();
  double_playfield->resetCalculatedRGB();
  double_playfield->updateLed();

  triple_playfield->disable();
  triple_playfield->resetCalculatedRGB();
  triple_playfield->updateLed();
}
void resetBonusLeds()
{
  twox_bonus->disable();
  twox_bonus->resetCalculatedRGB();
  twox_bonus->updateLed();

  threex_bonus->disable();
  threex_bonus->resetCalculatedRGB();
  threex_bonus->updateLed();

  fivex_bonus->disable();
  fivex_bonus->resetCalculatedRGB();
  fivex_bonus->updateLed();
}
void resetSpinnerLeds()

{
  onethousand_spinner->disable();
  onethousand_spinner->resetCalculatedRGB();
  onethousand_spinner->updateLed();

  threethousand_spinner->disable();
  threethousand_spinner->resetCalculatedRGB();
  threethousand_spinner->updateLed();

  fivethousand_spinner->disable();
  fivethousand_spinner->resetCalculatedRGB();
  fivethousand_spinner->updateLed();

}

void resetBallLEDs()
{
  oneball_pocket->disable();
  oneball_pocket->resetCalculatedRGB();
  oneball_pocket->updateLed();

  twoball_pocket->disable();
  twoball_pocket->resetCalculatedRGB();
  twoball_pocket->updateLed();

  threeball_pocket->disable();
  threeball_pocket->resetCalculatedRGB();
  threeball_pocket->updateLed();

  fourball_pocket->disable();
  fourball_pocket->resetCalculatedRGB();
  fourball_pocket->updateLed();

  fiveball_pocket->disable();
  fiveball_pocket->resetCalculatedRGB();
  fiveball_pocket->updateLed();

  sixball_pocket->disable();
  sixball_pocket->resetCalculatedRGB();
  sixball_pocket->updateLed();

  sevenball_pocket->disable();
  sevenball_pocket->resetCalculatedRGB();
  sevenball_pocket->updateLed();

  eightball_pocket->disable();
  eightball_pocket->resetCalculatedRGB();
  eightball_pocket->updateLed();

  nineball_pocket->disable();
  nineball_pocket->resetCalculatedRGB();
  nineball_pocket->updateLed();

  tenball_pocket->disable();
  tenball_pocket->resetCalculatedRGB();
  tenball_pocket->updateLed();

  elevenball_pocket->disable();
  elevenball_pocket->resetCalculatedRGB();
  elevenball_pocket->updateLed();

  twelveball_pocket->disable();
  twelveball_pocket->resetCalculatedRGB();
  twelveball_pocket->updateLed();

  thirteenball_pocket->disable();
  thirteenball_pocket->resetCalculatedRGB();
  thirteenball_pocket->updateLed();

  fourteenball_pocket->disable();
  fourteenball_pocket->resetCalculatedRGB();
  fourball_pocket->updateLed();

  fifteenball_pocket->disable();
  fifteenball_pocket->resetCalculatedRGB();
  fifteenball_pocket->updateLed();
}

void bonusCountdown()
{
  //identify if multiplier is in play
  int multiplier = 1; //set as one for now

  if(fivex_bonus->isEnabled()==true)
  {
    multiplier = 5;
  }else if(threex_bonus->isEnabled()==true)
  {
    multiplier = 3;
  }else if(twox_bonus->isEnabled()==true)
  {
    multiplier = 2;
  }

 
  //step through each bonus qualifying led
  if (E_led->isEnabled()==true)
  {
    fireBonusLed(E_led, 10000, multiplier);
  }
  if (I_led->isEnabled()==true)
  {
    fireBonusLed(I_led, 10000, multiplier);
  }
  if (G_led->isEnabled()==true)
  {
    fireBonusLed(G_led, 10000, multiplier);
  }
  if (H_led->isEnabled()==true)
  {
    fireBonusLed(H_led, 10000, multiplier);
  }
  if (T_led->isEnabled()==true)
  {
    fireBonusLed(T_led, 10000, multiplier);
  }

  if (Ball_led->isEnabled()==true)
  {
    fireBonusLed(Ball_led, 50000, multiplier);
  }

  if (bAll_led->isEnabled()==true)
  {
    fireBonusLed(bAll_led, 50000, multiplier);
  }

  if (baLl_led->isEnabled()==true)
  {
    fireBonusLed(baLl_led, 50000, multiplier);
  }

  if (balL_led->isEnabled()==true)
  {
    fireBonusLed(balL_led, 50000, multiplier);
  }


  //single potted balls first
  //Pocket Balls
  if (oneball_pocket->isEnabled()==true)
  {
    fireBonusLed(oneball_pocket, 15000, multiplier);
  }
  if (twoball_pocket->isEnabled()==true)
  {
    fireBonusLed(twoball_pocket, 15000, multiplier);
  }
  if (threeball_pocket->isEnabled()==true)
  {
    fireBonusLed(threeball_pocket, 15000, multiplier);
  }
  if (fourball_pocket->isEnabled()==true)
  {
    fireBonusLed(fourball_pocket, 15000, multiplier);
  }
  if (fiveball_pocket->isEnabled()==true)
  {
    fireBonusLed(fiveball_pocket, 15000, multiplier);
  }
  if (sixball_pocket->isEnabled()==true)
  {
    fireBonusLed(sixball_pocket, 15000, multiplier);
  }
  if (sevenball_pocket->isEnabled()==true)
  {
    fireBonusLed(sevenball_pocket, 15000, multiplier);
  }

  if (nineball_pocket->isEnabled()==true)
  {
    fireBonusLed(nineball_pocket, 15000, multiplier);
  }
  if (tenball_pocket->isEnabled()==true)
  {
    fireBonusLed(tenball_pocket, 15000, multiplier);
  }
  if (elevenball_pocket->isEnabled()==true)
  {
    fireBonusLed(elevenball_pocket, 15000, multiplier);
  }
  if (twelveball_pocket->isEnabled()==true)
  {
    fireBonusLed(twelveball_pocket, 15000, multiplier);
  }
  if (thirteenball_pocket->isEnabled()==true)
  {
    fireBonusLed(thirteenball_pocket, 15000, multiplier);
  }
  if (fourteenball_pocket->isEnabled()==true)
  {
    fireBonusLed(fourteenball_pocket, 15000, multiplier);
  }
  if (fifteenball_pocket->isEnabled()==true)
  {
    fireBonusLed(fifteenball_pocket, 15000, multiplier);
  }
  //To Do : E-I-G-H-T

  //To Do : B-A-L-L


  //lower ring awards next
  if(onehundredtwentythousand_bonus->isEnabled()==true)
  {
    fireBonusLed(onehundredtwentythousand_bonus, 120000, multiplier);
  }

  if(twohundredfortythousand_bonus->isEnabled()==true)
  {
    fireBonusLed(twohundredfortythousand_bonus, 240000, multiplier);
  }
  
}

void fireBonusLed(PinballLED* LED, int score, int multiplier)
{
  //flash LED, add score, play chimes, turn off led
    
    LED->setFlashSpeed(2);
    LED->updateLed();
    addBonus(score, multiplier);
    vTaskDelay(250);
    LED->disable();
    LED->resetCalculatedRGB();
    LED->setFlashSpeed(0);
    LED->updateLed();
}

void LED_display_chase_pf()
{
  int* ptr = playfieldRows[pfRowCounter];
  for(int i = 0; i < pfArraySize[pfRowCounter]; i++)
  {
    
    PinballLED* thisCLed = LEDs[*ptr].ledObject;
     if(thisCLed->isEnabled() == false)
      {
        thisCLed->flashOnce(1); //cycle once a second second
      }
    ptr++;
  }
  pfRowCounter++;
  if(pfRowCounter == pfRowCount)
  {
    pfRowCounter = 0;
  }
}


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