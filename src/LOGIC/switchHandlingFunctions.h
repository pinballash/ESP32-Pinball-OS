#include <Arduino.h>
void ScanSwitchMatrixFunction( void * pvParameters)
{
  /*if((scanInProgress == false) && (millis() - lastMillisSwINT > 10))
  {
    scanInProgress = true;
    scanSwitchMatrix();
    triggerSwitches();
    manageCoils();
    //manageAudio();
    INTHz++;
    scanInProgress = false;
  }
  if (millis() - lastMillisSwINT > 1000 )
  {
    reportedSwitchMatrixHz = INTHz;
    INTHz = 0;
    lastMillisSwINT = millis();
  }*/
  vTaskDelay(1);
}

void ProcessSwitchesAndRulesFunction( void * pvParameters)
{
  //identifyFlippers();
  int counterSw = 0;
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
    if(micros() - lastMicrosLoopRan >= processSwitchArrayEveryMicroSeconds) //we must not let this loop run away with itself, rate limiter here
    {
      //do processing 
      // count how many times we are scanning switch matrix per second, and display it, remove this debug message in live version
      counterSw++;
      //static int tempSound=1;
      if (millis() - lastMillisSw > 1000 )
      {
        if(threadDebug)
        {
          Serial.print("[threadDebug] ProcessSwitches Loop: CORE ");
          Serial.print(xPortGetCoreID());
          Serial.print(" : is currently running at approximatly ");
          Serial.print(counterSw);
          Serial.println("Hz (full program cycles per second)");
        }
        reportedSwitchMatrixHz = counterSw;
        counterSw = 0;
        lastMillisSw = millis();
        
      }// End of debug stuff 
      measureMicro = micros();
      //scanSwitchMatrix();
      //triggerSwitches();
      //manageCoils();
      processAllSwitches();//Needs to be done on a separate thread on a timer.
      processSwitchMicro = processSwitchMicro + (micros() - measureMicro);
      lastMicrosLoopRan = micros();
    }else{
      //release the CPU for processing other tasks
      vTaskDelay(pdMS_TO_TICKS(1));
    }  
  }
}

/*
* Function scanSwitchMatrix
* loop through all columns and rows and check for a switch closure.  
* If a switch is closed, st the switchActive array value to true.
*/
void scanSwitchMatrix()
{
 for ( byte col = 0; col < setting_switchMatrixColumns ; col++) 
 {
  outgoing = 0;
  bitSet(outgoing,(7-col));  
  write_sr_matrix();  // So sets the column high,
  bitClear(outgoing,col); //no longer needs to be set, we sent it
  delayMicroseconds(2); // give the register time to update
  read_sr();
  for (byte row = 0; row < setting_switchMatrixRows; row++) 
  {    
    if (bitRead(incoming,row)) 
    {
      switchActive[col][row] = true; 
    } else {
      //switchActive[col][row] = false; //default to not active (off)
    }
  }
 }
 //Next we could read the values in the second input shift register.  
 //This is not being handled by scanning the matrix, each of the 8 switches that can be connected here
 //will be supplied by positive voltage constantly which will lead the input shift register to be high once pushed.
  for (byte row = 0; row < 8; row++) 
  {    
    if (bitRead(incoming2,row)) 
    {
      secondarySwitchActive[row] = true; 
    } else {
      //switchActive[col][row] = false; //default to not active (off)
    }
  }
} 
/*
* Function triggerSwitches
* This is called from a loop and checks the switchActive array for a switch trigger
* once an event is found, the switch is triggered and if outside debounce, a switchScored array is activated for the switch
* coil bindings are checked for the switch, if there is one, and if instantFire is true, the bound coil will be fired (should the game be active)
*/
void triggerSwitches()
{
  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {    
      int triggeredSwitchID = (col*8)+row;

      if(switchActive[col][row]==true) 
      {//switch triggered physically
        switchActive[col][row]=false;
        if(switches[triggeredSwitchID].switchObject->triggerSwitch()==true)//this will return false if debounce period still active
        {
          switchScored[col][row]=true; //get credit for hitting the switch of do switch hit activity - this is picked up in processAllSwitches()
          if(generalMODebug)
          {
            Serial.print("TriggerSwitches(): ");
            Serial.println(switches[triggeredSwitchID].switchObject->getName());
          } 
          byte* thisSwitchCoilBinding = switchCoilBindings[triggeredSwitchID].coilNumber;
   
          //should we really be doing this when game is not active?
          if(thisSwitchCoilBinding > 0) //if we have a coil bound to the switch
          {
            if(switchCoilBindings[triggeredSwitchID].instantFire == true) //we need to fire the coil straight away
            {
              if(generalMODebug)
              {
                Serial.print("Switch triggered with coil binding and Instant Trigger. Switch ID ");
                Serial.println(triggeredSwitchID);      
              } 
              //manual hack - we get interference on col 0 row 3 where left pop fires when saucer switch is active - so we will only fire if the saucer is not active
              if(switchScored[0][3]==false)
              {
                byte* coilNumber = switchCoilBindings[(byte)triggeredSwitchID].coilNumber; //get the coil number bound to the switch
                byte coilNumberByte = *coilNumber;
                PinballCoil* switchCoil = coils[coilNumberByte].coilObject; //get the PinballCoil instance associated
                if(MachineState == 2) //only if game is active
                {
                  if(switchCoil->fireCoil())
                  { //try and fire the coil
                    coilActive[coilNumberByte]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
                    ProcessShifts(switchCoil); //set shift register bytes to turn on solenoid
                    write_sr_coils(); //update shift register
                    stepLanesLeft();
                  }
                  
                }
              }

              
            }else{
              if(generalMODebug)
              {
                Serial.print("Switch triggered. Switch ID ");
                Serial.println(triggeredSwitchID);        
              } 
            }
            
          }else{
            //other switch actions can wait for processing
            if(generalMODebug)
            {
              Serial.print("Switch triggered without coil binding....actions can wait");
              Serial.println(triggeredSwitchID);
            }
          }
          
        }//end triggered switch processing  
      }
      //end switch processing
    }//end row processing
  }//end col processing 
}
/*
* Function processAllSwitches
* loop through all columns and rows and check for a switchScored array values that are true. 
* If a switch is assigned a special designation, like Start, Credit, Outhole or Flipper, action funtions can be called from here
* TODO: If a switch is bound to a coil, without instanfFire, rules will need to be consulted to determine if coil needs to be fired or not
*/
void processAllSwitches()
{
  //quickly handle directly wired switches - these dont trigger anything 
  for (byte row = 0; row < 8; row++) 
  {    
    if(secondarySwitchActive[row]==true) 
    {//switch needs processing
      secondarySwitchActive[row]=false;
      if(secondSwitches[row].switchObject->triggerSwitch()==true)//this will return false if debounce period still active
      {
        //do work
        Serial.print("Secondary Switch Processing - ");
        Serial.print(row);
        Serial.print(" - ");
        Serial.print(secondSwitches[row].switchObject->getName());
        secondarySwitchActive[row]=false;
        if(secondSwitches[row].switchObject->isStart()==true)
        {
          switch_event_startbutton();
        }
      }else{
        //Serial.print("Secondary Switch Processing - ");
        //Serial.print(secondSwitches[row].switchObject->getName());
        //Serial.println(" - Not ok to trigger");
       
      }//end triggered switch processing  
      
    }//end switch processing
  }

  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) 
  {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {
      if(switchScored[col][row]==true)
      {
        int triggeredSwitchID = (col * 8)+row;
        if(MachineState == 5)
        {
              if(ScoreboardTText == ScoreboardBText ){
                ScoreboardTText = ScoreboardBText;
                ScoreboardBText = switches[triggeredSwitchID].switchObject->getName();
              }else{
                ScoreboardTText = ScoreboardBText;
                ScoreboardBText = "Multi-hit";
              }
              
        }
        if(switches[triggeredSwitchID].switchObject->isStart()==true)
        {
          switch_event_startbutton();
        }else if(switches[triggeredSwitchID].switchObject->isOuthole()==true)
        {
          //Serial.println("[processAllSwitches] Outhole Fired");
          switch_event_outhole(triggeredSwitchID);
        }else if(switches[triggeredSwitchID].switchObject->isCredit()==true)
        {
          //switch_event_credit(triggeredSwitchID); //used when not on freeplay
        }else if(switches[triggeredSwitchID].switchObject->isFlipper()==true)
        {
          //switch_event_flipper(triggeredSwitchID); //Used for high score entry and menu navigation
        }else{
          //normal switch

          //check for active mode - default, level 1, level 2 etc

          //for the active mode, check for rule

          /* a little more on modes,
           * A mode can require events to complete
           * events can be count of switch hits, combinations, timers
           * for now we will be working just on default
          */
          addScore(triggeredSwitchID);
          /*if((audios[triggeredSwitchID].AudioObject->fireAudio()))
          { //try and play sound
            audioActive[triggeredSwitchID]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
            ProcessAudioShifts(audios[triggeredSwitchID].AudioObject); //set shift register bytes to turn on audio channel
            write_sr_audio(); //update shift register
          }*/
          //DoubleTrigger();
          
          


        }
        //Game rules go here. As we pick up switch triggers we can initiate logic.

        if(MachineState == 2)//only process these switches if game is active
        {
          switch(triggeredSwitchID)
          {
            case 23: //C - Inlane Left
            {
              //this is part of 5 bank 
              if(c_champ->isOn()==true)
              {
                c_champ->disable();
                c_champ->updateLed();
                if(checkChamp() == false)
                {
                  //champ off
                  //reset champ
                  resetChampLeds();

                  //increase multiplier - to do
                  triggerPlayfieldMultiplierIncrease = true;
                  triggerSpinnerValueIncrease = true;

                }

              }
              break;
            }
            case 22: //H - Lane Left
            {
              //this is part of 5 bank 
              if(h_champ->isOn()==true)
              {
                h_champ->disable();
                h_champ->updateLed();
                if(checkChamp() == false)
                {
                  //champ off
                  //reset champ
                  resetChampLeds();

                  //increase multiplier - to do
                  triggerPlayfieldMultiplierIncrease = true;
                  triggerSpinnerValueIncrease = true;

                }

              }
              break;
            }
            case 21: //A - Inlane middle
            {
              //this is part of 5 bank 
              if(a_champ->isOn()==true)
              {
                a_champ->disable();
                a_champ->updateLed();
                if(checkChamp() == false)
                {
                  //champ off
                  //reset champ
                  resetChampLeds();

                  //increase multiplier - to do
                  triggerPlayfieldMultiplierIncrease = true;
                  triggerSpinnerValueIncrease = true;

                }

              }
              break;
            }
            case 20: //M - Lane Right
            {
              //this is part of 5 bank 
              if(m_champ->isOn()==true)
              {
                m_champ->disable();
                m_champ->updateLed();
                if(checkChamp() == false)
                {
                  //champ off
                  //reset champ
                  resetChampLeds();

                  //increase multiplier - to do
                  triggerPlayfieldMultiplierIncrease = true;
                  triggerSpinnerValueIncrease = true;

                }

              }
              break;
            }
            case 19: //P - Inlane Right
            {
              //this is part of 5 bank 
              if(p_champ->isOn()==true)
              {
                p_champ->disable();
                p_champ->updateLed();
                if(checkChamp() == false)
                {
                  //champ off
                  //reset champ
                  resetChampLeds();

                  //increase multiplier - to do
                  triggerPlayfieldMultiplierIncrease = true;
                  triggerSpinnerValueIncrease = true;

                }

              }
              break;
            }
            case 24: //spinner
            {
              
              //do spinner work
              break;
            }
            case 3: //Saucer
            {
              
              switch_event_saucer(3);
              break;
            }
            case 31: //I - Drop
            {
              Serial.println("Switch 31 Drop");
              //if on, turn off, add to pocketed, reset drop and break
              if(oneball_table->isOn())
              {
                oneball_table->disable();
                oneball_table->updateLed();
                
                oneball_pocket->enable();
                oneball_pocket->resetCalculatedRGB();
                oneball_pocket->setFlashSpeed(0);
                oneball_pocket->updateLed();

                //reset drop
                resetDrop(7, 31);
                checkEightBall();
                break;
              }else if(twoball_table->isOn())
              {
                twoball_table->disable();
                twoball_table->updateLed();
                
                twoball_pocket->enable();
                twoball_pocket->resetCalculatedRGB();
                twoball_pocket->setFlashSpeed(0);
                twoball_pocket->updateLed();

                //no more balls to pot - dont reset drop
                checkEightBall();
                break;
              }else if(nineball_table->isOn())
              {
                nineball_table->disable();
                nineball_table->updateLed();
                
                nineball_pocket->enable();
                nineball_pocket->resetCalculatedRGB();
                nineball_pocket->setFlashSpeed(0);
                nineball_pocket->updateLed();

                //reset drop
                resetDrop(7, 31);
                checkEightBall();
                break;
              }else if(tenball_table->isOn())
              {
                tenball_table->disable();
                tenball_table->updateLed();
                
                tenball_pocket->enable();
                tenball_pocket->resetCalculatedRGB();
                tenball_pocket->setFlashSpeed(0);
                tenball_pocket->updateLed();

                //no more balls to pot - dont reset drop
                checkEightBall();
                break;
              }
              break;
            }  
            case 28: //H - Drop
            {
              Serial.println("Switch 28 Drop");
              //check each tabled ball in turn, 
              //if on, turn off, add to pocketed, reset drop and break
              if(fourball_table->isOn())
              {
                fourball_table->disable();
                fourball_table->updateLed();
                
                fourball_pocket->enable();
                fourball_pocket->resetCalculatedRGB();
                fourball_pocket->setFlashSpeed(0);
                fourball_pocket->updateLed();

                //reset drop
                resetDrop(9, 28);
                checkEightBall();
                break;
              }else if(fiveball_table->isOn())
              {
                fiveball_table->disable();
                fiveball_table->updateLed();
                
                fiveball_pocket->enable();
                fiveball_pocket->resetCalculatedRGB();
                fiveball_pocket->setFlashSpeed(0);
                fiveball_pocket->updateLed();

                //no more balls to pot - dont reset drop
                checkEightBall();
                break;
              }else if(twelveball_table->isOn())
              {
                twelveball_table->disable();
                twelveball_table->updateLed();
                
                twelveball_pocket->enable();
                twelveball_pocket->resetCalculatedRGB();
                twelveball_pocket->setFlashSpeed(0);
                twelveball_pocket->updateLed();

                //reset drop
                resetDrop(9, 28);
                checkEightBall();
                break;
              }else if(thirteenball_table->isOn())
              {
                thirteenball_table->disable();
                thirteenball_table->updateLed();
                
                thirteenball_pocket->enable();
                thirteenball_pocket->resetCalculatedRGB();
                thirteenball_pocket->setFlashSpeed(0);
                thirteenball_pocket->updateLed();

                //no more balls to pot - dont reset drop
                checkEightBall();
                break;
              }
              break;
            }   
            case 29: //G - Drop
            {
              Serial.println("Switch 28 Drop");
              //if on, turn off, add to pocketed, reset drop and break
              if(threeball_table->isOn())
              {
                threeball_table->disable();
                threeball_table->updateLed();
                
                threeball_pocket->enable();
                threeball_pocket->resetCalculatedRGB();
                threeball_pocket->setFlashSpeed(0);
                threeball_pocket->updateLed();

                //no more balls to pot - dont reset drop
                checkEightBall();
                break;
              }else if(elevenball_table->isOn())
              {
                elevenball_table->disable();
                elevenball_table->updateLed();
                
                elevenball_pocket->enable();
                elevenball_pocket->resetCalculatedRGB();
                elevenball_pocket->setFlashSpeed(0);
                elevenball_pocket->updateLed();
                checkEightBall();
                break;
              }
              break;
            }  
            case 26: //E - Drop
            {
              Serial.println("Switch 26 Drop");
              //check each tabled ball in turn, 
              //if on, turn off, add to pocketed, reset drop and break
              if(sixball_table->isOn())
              {
                sixball_table->disable();
                sixball_table->updateLed();
                
                sixball_pocket->enable();
                sixball_pocket->resetCalculatedRGB();
                sixball_pocket->setFlashSpeed(0);
                sixball_pocket->updateLed();

                //no more balls to pot - dont reset drop
                checkEightBall();
                break;
              }else if(fourteenball_table->isOn())
              {
                fourteenball_table->disable();
                fourteenball_table->updateLed();
                
                fourteenball_pocket->enable();
                fourteenball_pocket->resetCalculatedRGB();
                fourteenball_pocket->setFlashSpeed(0);
                fourteenball_pocket->updateLed();
                checkEightBall();
                break;
              }
              break;
            } 
            case 25: //T - Drop
            {
              Serial.println("Switch 25 Drop");
              //if on, turn off, add to pocketed, reset drop and break
              if(sevenball_table->isOn())
              {
                sevenball_table->disable();
                sevenball_table->updateLed();
                
                sevenball_pocket->enable();
                sevenball_pocket->resetCalculatedRGB();
                sevenball_pocket->setFlashSpeed(0);
                sevenball_pocket->updateLed();

                //no more balls to pot - dont reset drop
                checkEightBall();
                break;
              }else if(fifteenball_table->isOn())
              {
                fifteenball_table->disable();
                fifteenball_table->updateLed();
                
                fifteenball_pocket->enable();
                fifteenball_pocket->resetCalculatedRGB();
                fifteenball_pocket->setFlashSpeed(0);
                fifteenball_pocket->updateLed();
                checkEightBall();
                break;
              }
              break;
            }  
            case 39: //E Standup
            {
              Serial.println("Switch 39");
              if(E_led->isEnabled()==false)
              {
                E_led->enable();
                E_led->resetCalculatedRGB();
                E_led->setFlashSpeed(0);
                E_led->updateLed();
                checkEightWord();
              }
              
              break;
            } 
            case 38: //I Standup
            {
              Serial.println("Switch 38");
              if(I_led->isEnabled()==false)
              {
                I_led->enable();
                I_led->resetCalculatedRGB();
                I_led->setFlashSpeed(0);
                I_led->updateLed();
                checkEightWord();
              }
              break;
            } 
            case 37: //G Standup
            {
              Serial.println("Switch 37");
              if(G_led->isEnabled()==false)
              {
                G_led->enable();
                G_led->resetCalculatedRGB();
                G_led->setFlashSpeed(0);
                G_led->updateLed();
                checkEightWord();
              }
              break;
            } 
            case 36: //H Standup
            {
              Serial.println("Switch 36");
              if(H_led->isEnabled()==false)
              {
                H_led->enable();
                H_led->resetCalculatedRGB();
                H_led->setFlashSpeed(0);
                H_led->updateLed();
                checkEightWord();
              }
              break;
            } 
            case 35: //T Standup
            {
              Serial.println("Switch 35");
              if(T_led->isEnabled()==false)
              {
                T_led->enable();
                T_led->resetCalculatedRGB();
                T_led->setFlashSpeed(0);
                T_led->updateLed();
                checkEightWord();
              }
              break;
            } 
             

          }
      
        }
        //finally, mark switch as processed
        switchScored[col][row]=false;

        //then pick up any logic that needs dealing with
        if(triggerBonusMultiplierIncrease == true)
        {
          increaseBonusMultiplier();
          
          //now we are done reset.
          triggerBonusMultiplierIncrease = false;
          
        }
        if(triggerSpinnerValueIncrease == true)
        {
          increaseSpinnerValue();
          triggerSpinnerValueIncrease = false;
        }
        if(triggerPlayfieldMultiplierIncrease == true)
        {
          increasePlayfieldMultiplier();
          triggerPlayfieldMultiplierIncrease = false;
        }
      }
    }
  }
  //need individual switch logic - things need to happen, different modes mean different outcomes - for later

}
