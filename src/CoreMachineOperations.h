#include <Arduino.h>
#include "PinballSwitch.h"
#include "PinballCoil.h"
//#include "PinballAudio.h"
#include "PinballLED.h"
#include "PinballGame.h"

bool switchDebug = false;
bool coilDebug = false;
bool loopDebug = false;
bool threadDebug = false;
bool srDebug = false;
bool osrDebug = false;
bool generalMODebug = false;
bool memoryStats = false;
unsigned long ScanSwitchMatrixEveryMicroSeconds = 100; //this seems to be the value where we can operate at around 1000 times per second
unsigned long UpdateLedsEveryMicroSeconds = 100000; //10 times a second
bool runningLeds = false;

PinballGame g_myPinballGame(setting_MachineName);

//#include "switchArray_def.h" -> removing static definition in favour of dynamic from JSON files stored in SPIFFS and edited via Web page
#include "switchArray_fromJSON.h"
#include "coilArray_fromJSON.h"
#include "flipperBindings_def.h"
#include "coilBindings_fromJSON.h"
#include "ledArray_fromJSON.h"
//not using audio in this table - commented out
//#include "audioArray_fromJSON.h"

void ProcessSwitchesAndRulesFunction( void * pvParameters);
void ProcessLedsFunction( void * pvParameters);
void scanSwitchMatrix();

void triggerSwitches();
void processAllSwitches();
void processAllLeds();
void ProcessShifts(PinballCoil* CoilObject);
//void ProcessAudioShifts(PinballAudio* AudioObject);
//void ResetAudioShifts();
void manageCoils();
//void manageAudio();
void read_sr();
void write_sr_matrix();
//void write_sr_audio();
void write_sr_coils();
void switch_event_startbutton(int switchId);
void switch_event_outhole(int switchId);

void addScore(int switchID);
bool ChimeRing(char coilNum);
void turnOffAllLeds();
void setNewBallLEDs(bool dots); //sets up playfield lights - dots true, 1-7, false 9-15
void resetChampLeds();
bool checkChamp();
void changeState(int newState);

void DoubleTrigger();
void Tune1Trigger();
void resetDrops();


//define LED named objects
//CHAMP
PinballLED* c_champ = LEDs[82].ledObject;
PinballLED* h_champ = LEDs[19].ledObject;
PinballLED* a_champ = LEDs[20].ledObject;
PinballLED* m_champ = LEDs[21].ledObject;
PinballLED* p_champ = LEDs[78].ledObject;

//Table Balls
PinballLED* oneball_table = LEDs[39].ledObject;
PinballLED* twoball_table = LEDs[37].ledObject;
PinballLED* threeball_table = LEDs[34].ledObject;
PinballLED* fourball_table = LEDs[32].ledObject;
PinballLED* fiveeball_table = LEDs[30].ledObject;
PinballLED* sixball_table = LEDs[42].ledObject;
PinballLED* sevenball_table = LEDs[54].ledObject;
PinballLED* eightball_table = LEDs[2].ledObject;
PinballLED* nineball_table = LEDs[40].ledObject;
PinballLED* tenball_table = LEDs[14].ledObject;
PinballLED* elevenball_table = LEDs[33].ledObject;
PinballLED* twelveball_table = LEDs[31].ledObject;
PinballLED* thirteenball_table = LEDs[29].ledObject;
PinballLED* fourteenball_table = LEDs[43].ledObject;
PinballLED* fifteenball_table = LEDs[51].ledObject;

//Pocket Balls
PinballLED* oneball_pocket = LEDs[62].ledObject;
PinballLED* twoball_pocket = LEDs[64].ledObject;
PinballLED* threeball_pocket = LEDs[67].ledObject;
PinballLED* fourball_pocket = LEDs[70].ledObject;
PinballLED* fiveeball_pocket = LEDs[72].ledObject;
PinballLED* sixball_pocket = LEDs[73].ledObject;
PinballLED* sevenball_pocket = LEDs[75].ledObject;
PinballLED* eightball_pocket = LEDs[68].ledObject;
PinballLED* nineball_pocket = LEDs[63].ledObject;
PinballLED* tenball_pocket = LEDs[65].ledObject;
PinballLED* elevenball_pocket = LEDs[66].ledObject;
PinballLED* twelveball_pocket = LEDs[69].ledObject;
PinballLED* thirteenball_pocket = LEDs[71].ledObject;
PinballLED* fourteenball_pocket = LEDs[74].ledObject;
PinballLED* fifteenball_pocket = LEDs[76].ledObject;


hw_timer_t *Timer0_Cfg = NULL;
void IRAM_ATTR Timer0_ISR()
{
    if(scanInProgress == false)
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
  }
    
}
//setup a task to run on core 0;
//TaskHandle_t MonitorSwitchesAndRegister;
TaskHandle_t ProcessSwitchesAndRules;
TaskHandle_t ProcessLeds;

//setup array for storing switch active
const int tableRows = 8;//(int8_t)setting_switchMatrixRows; // 0 to 7
const int tableCols = 8;//(int8_t)setting_switchMatrixColumns; // 0 to 4
const int switchCount = tableRows * tableCols;
const int flipperButtons = 2;
bool switchActive[tableCols][tableRows];
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
byte outgoing3=0;// used for solenoids
byte outgoing4=0;//used for solenoids

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
    if(micros() - lastMicrosLoopRan >= ScanSwitchMatrixEveryMicroSeconds) //we must not let this loop run away with itself, rate limiter here
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
        CMOHz = counterSw;
        counterSw = 0;
        lastMillisSw = millis();
        
      }// End of debug stuff 
        

      measureMicro = micros();
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

void ProcessLedsFunction( void * pvParameters)
{
  
  Serial.print("ProcessLedsFunction running on core ");
  Serial.println(xPortGetCoreID());
  //identifyFlippers();
  /*ws2812b.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  ws2812b.show();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  int counterSw = 0;*/
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
    if((micros() - lastMicrosLoopRan >= UpdateLedsEveryMicroSeconds) && (runningLeds==false))//we must not let this loop run away with itself, rate limiter here
    {
      
      runningLeds = true;
      //do processing
      //Serial.println("Processing LEDs");
      measureMicro = micros();
      processAllLeds();//Needs to be done on a separate thread on a timer.
      processSwitchMicro = processSwitchMicro + (micros() - measureMicro);
      lastMicrosLoopRan = micros();
    }else{
      //release the CPU for processing other tasks
      vTaskDelay(50); //yeild for a 20th of a second
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

              }

            }
            break;
          }

        }
        //finally, mark switch as processed
        switchScored[col][row]=false;
      }
    }
  }
  //need individual switch logic - things need to happen, different modes mean different outcomes - for later
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
    ledArrayPottedBallsEven =  LED_display_oddsAndEvens(ledArray_PottedBalls, ledArrayPottedBallsCount, ledArrayPottedBallsEven, 2);
  }
    
  if (cycleLedEIGHTBALL == true)
  {
    LED_display_flashBlock(ledArray_EIGHTBALL, ledArrayEIGHTBALLCount, 2);
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
    }
  }

  if(needsReload == true)
  {
    FastLED.show();  // update to the WS2812B Led Strip
  }
  //give 50ms for other processes (therefor max Hz of the LED is 1000/50 = 50Hz)
  runningLeds = false;
  vTaskDelay(5);
}

/*
 * ProcessShifts is a function that updates the shift register byte variables based on the coil object sent
 */
void ProcessShifts(PinballCoil* CoilObject)
{
  if(CoilObject->getSR() == 0)
  {
    if(CoilObject->checkStatus())
    {
      if(osrDebug)
      {
        Serial.print("Turning on coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR3 - BIT:");
        Serial.println(CoilObject->getSRBit());
      } 
      bitSet(outgoing3,CoilObject->getSRBit());
    }else
    {
      if(osrDebug)
      {
        Serial.print("Turning off coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR3 - BIT:");
        Serial.println(CoilObject->getSRBit());
      }
      bitClear(outgoing3,CoilObject->getSRBit());
    }
  }else if(CoilObject->getSR() == 1)
  {
    if(CoilObject->checkStatus())
    {
      if(osrDebug)
      {
        Serial.print("Turning on coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR4 - BIT:");
        Serial.println(CoilObject->getSRBit());
      }
      bitSet(outgoing4,CoilObject->getSRBit());

    }else
    {
      if(osrDebug)
      {
        Serial.print("Turning off coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR4 - BIT:");
        Serial.println(CoilObject->getSRBit());
      }
      bitClear(outgoing4,CoilObject->getSRBit());
    }
  }
}
void manageCoils()
{
  for ( byte coilNumber = 0; coilNumber < coilCount ; coilNumber++) {
    if(coilActive[coilNumber]==true)
    {
      PinballCoil* activeCoil = coils[coilNumber].coilObject;
      activeCoil->manage();
      if(activeCoil->checkStatus()==false)
      {
        ProcessShifts(activeCoil); 
        write_sr_coils();
        coilActive[coilNumber]=false;
      }
    }
  }
}
/*void manageAudio()
{
  byte maxAudio = 39;
  for ( byte audioNumber = 0; audioNumber < maxAudio ; audioNumber++) {
    if(audioActive[audioNumber]==true)
    {
      PinballAudio* activeAudio = audios[audioNumber].AudioObject;
      activeAudio->manage();
      if(activeAudio->checkStatus()==false)    
      {
        audioActive[audioNumber]=false;
        ResetAudioShifts();
      }
    }
  }
}*/
/*
void ResetAudioShifts(){
  outgoing2 = 255;
  write_sr_audio();
  //tso_PinballAudio = tso_PinballAudio + "[ProcessAudioShifts] Setting Shift to "+String(outgoing2);
}
*/

/*void ProcessAudioShifts(PinballAudio* AudioObject)
{  
  outgoing2 = 255;
  outgoing2 = outgoing2 - AudioObject->getSRBit();
  //tso_PinballAudio = tso_PinballAudio + "[ProcessAudioShifts] Setting Shift to "+String(outgoing2);
}*/


void read_sr() {//Read input shift registers
  // Write pulse to load pin
  digitalWrite(isrload, LOW);
  digitalWrite(isrload, HIGH);
  incoming = 0;
  incoming2 = 0;
  digitalWrite(isrclockEnablePin, LOW);
  incoming = shiftIn(isrdataIn, isrclockIn, LSBFIRST);
  incoming2 = shiftIn(isrdataIn, isrclockIn, LSBFIRST);
  // read twice to simulate reading 2 165's
  digitalWrite(isrclockEnablePin, HIGH);
  if(srDebug){
    Serial.print("read_sr : incoming");
    Serial.print("1->2[");
    Serial.print(incoming);
    Serial.print(",");
    Serial.print(incoming2);
    Serial.println("]");
  }
}
void write_sr_matrix() 
{ // Write to the output shift registers
  digitalWrite(osr1latchPin, LOW);
  shiftOut(osr1dataPin, osr1clockPin, LSBFIRST, outgoing); // changed to MSB to reflect physical wiring
  digitalWrite(osr1latchPin, HIGH);   
  if(srDebug){
    Serial.print("write_sr_matrix : outgoing [");
    Serial.print(outgoing);
    Serial.println("]");
  }   
}  
/*void write_sr_audio() 
{ // Write to the output shift registers
  digitalWrite(osr2latchPin, LOW);
  shiftOut(osr2dataPin, osr2clockPin, MSBFIRST, outgoing2); // changed to MSB to reflect physical wiring
  digitalWrite(osr2latchPin, HIGH);   
  if(srDebug){
    Serial.print("write_sr_audio : outgoing2 [");
    Serial.print(outgoing2);
    Serial.println("]");
  }   
} */  
void write_sr_coils() 
{ // Write to the output shift registers
  digitalWrite(osr3latchPin, LOW);
  
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, outgoing4); // changed to MSB to reflect physical wiring
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, outgoing3); // changed to MSB to reflect physical wiring
  // do it 4 times to simulate writing to 4 595s at once
  digitalWrite(osr3latchPin, HIGH);   
  if(osrDebug){
    Serial.print("write_sr_coils : outgoing");
    Serial.print("4->3[");
    Serial.print(outgoing4);
    Serial.print(",");
    Serial.print(outgoing3);
    Serial.println("]");
  }   
}   

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
  } else if(MachineState == 2)
  {//if player1 is still on first ball, add more players
    //Serial.println("[switch_event_startbutton] Add player");
    g_myPinballGame.addPlayer(); //This will add players up to the defined maximum

  } else if(MachineState == 3)
  {//new game
    //Serial.println("[switch_event_startbutton] Starting Another Game");
    changeState(2);
    turnOffAllLeds();
  }
}

void addScore(int switchID)
{
  int score = (switches[switchID].switchObject->getSwitchScore()) * g_myPinballGame.getPlayfieldMultiplier();
  int playerNumber = g_myPinballGame.getCurrentPlayerNumber();
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

  //PinballCoil* switchCoil = coils[coilid].coilObject;
  //if(switchCoil->fireCoil()){
  //  coilActive[coilid]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
  //  ProcessShifts(switchCoil); //action the turning on
  //  write_sr_coils(); //update shift register
  //}
  //ScoreboardBText = g_myPinballGame.getPlayerScore(playerNumber);
  //ScoreboardTText = "P" + (String)playerNumber + " Ball " + (String)g_myPinballGame.getCurrentBallNumber(playerNumber);
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

bool ChimeRing(char coilNum)
{
  PinballCoil* ChimeCoil = coils[coilNum].coilObject;
 
  if(ChimeCoil->fireCoil()){
    coilActive[coilNum]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
    ProcessShifts(ChimeCoil); //action the turning on
    write_sr_coils(); //update shift register
    return true;
  }
  return false;
}

void turnOffAllLeds()
{
  cycleLedPottedBalls = false;
  cycleLedEIGHTBALL = false;
  cycleLedLeftSide = false;
  cycleLedRightSide = false;
  cycleLedCHAMP = false;


  
  for (byte id = 0; id < NUM_LEDS ; id++) 
  {
    //get the led object and read its state
    PinballLED* thisLed = LEDs[id].ledObject; //get the PinballCoil instance associated
    thisLed->disable();
    thisLed->setFlashSpeed(0);
    thisLed->updateLed();
  }

  setNewBallLEDs(true);
}
void setNewBallLEDs(bool dots)
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

bool checkChamp()
{
  
  if((c_champ->isOn() == false)&&(h_champ->isOn() == false)&&(a_champ->isOn() == false)&&(m_champ->isOn() == false) && (p_champ->isOn() == false))
  {
    return false;
  }
  return true;
  
}
