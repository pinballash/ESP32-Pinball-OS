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
  //Serial.print("MonitorSwitches running on core ");
  //Serial.println(xPortGetCoreID());
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


      /*if(threadDebug)
      {
        unsigned long totalLoopProcessingTime = 0;

        Serial.print("Process Switch Time (uS) : ");
        Serial.println(processSwitchMicro);
        totalLoopProcessingTime = totalLoopProcessingTime + processSwitchMicro;
        processSwitchMicro = 0;

        Serial.print("Total Task Processing time uS : ");
        Serial.println(totalLoopProcessingTime);

        Serial.println("_________________________________");
      }*/



    }else{
      //release the CPU for processing other tasks
      //Serial.println("Switch Scan Taking a breather");
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
                  //todo: add score and other mode logic
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
      }//end switch processing
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
          switch_event_startbutton(triggeredSwitchID);
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
        bool triggerBonusMultiplierIncrease = false; //we need to track this and execute once switches have finished processing
        bool triggerSpinnerValueIncrease = false;
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
                triggerBonusMultiplierIncrease = true;
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
                triggerBonusMultiplierIncrease = true;
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
                triggerBonusMultiplierIncrease = true;
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
                triggerBonusMultiplierIncrease = true;
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
                triggerBonusMultiplierIncrease = true;
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

        }
        //finally, mark switch as processed
        switchScored[col][row]=false;

        //then pick up any logic that needs dealing with
        if(triggerBonusMultiplierIncrease == true)
        {
          increaseBonusMultiplier();
          increaseSpinnerValue();
          //now we are done reset.
          triggerBonusMultiplierIncrease = false;
          triggerSpinnerValueIncrease = false;
        }
      }
    }
  }
  //need individual switch logic - things need to happen, different modes mean different outcomes - for later
}
