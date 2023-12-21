#include <Arduino.h>
#include "PinballSwitch.h"
#include "PinballCoil.h"
#include "PinballGame.h"

bool switchDebug = true;
bool coilDebug = true;
bool loopDebug = false;
bool threadDebug = false;
bool srDebug = false;
bool osrDebug = true;
bool generalMODebug = true;
unsigned long ScanSwitchMatrixEveryMicroSeconds = 800; //this seems to be the value where we can operate at around 500 times per second

PinballGame g_myPinballGame(setting_MachineName);


//#include "switchArray_def.h" -> removing static definition in favour of dynamic from JSON files stored in SPIFFS and edited via Web page
#include "switchArray_fromJSON.h"
#include "coilArray_fromJSON.h"
#include "flipperBindings_def.h"
#include "coilBindings_fromJSON.h"

void fireFlipper(int firedSwitchID);
void releaseFlipper(int firedSwitchID);
void IRAM_ATTR fireFlipper1();
void IRAM_ATTR releaseFlipper1();
void IRAM_ATTR fireFlipper2();
void IRAM_ATTR releaseFlipper2();


void MonitorSwitchesAndRegisterFunction( void * pvParameters);
void scanSwitchMatrix();
void identifyFlippers(); //depriciated
void triggerFlippers(); //depriciated
void triggerSwitches();
void processAllSwitches();
void ProcessShifts(PinballCoil* CoilObject);
void manageCoils();
void read_sr();
void write_sr_matrix();
void write_sr_audio();
void write_sr_coils();
void switch_event_startbutton(int switchId);
void switch_event_outhole(int switchId);

void addScore(int switchID);
void changeState(int newState);

//setup a task to run on core 0;
TaskHandle_t MonitorSwitchesAndRegister;

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


// Define Connections to 74HC595 - Matrix Output Shift Register
//const int osr1latchPin = 18;
//const int osr1clockPin = 5;
//const int osr1dataPin = 17;
const int osr1latchPin = setting_osr1latchPin;
const int osr1clockPin = setting_osr1clockPin;
const int osr1dataPin = setting_osr1dataPin;

// Define Connections to 74HC595 - Audio Output Shift Register
//const int osr2latchPin = 2; //changed from 3
//const int osr2clockPin = 21;
//const int osr2dataPin = 19;
const int osr2latchPin = setting_osr2latchPin;
const int osr2clockPin = setting_osr2clockPin;
const int osr2dataPin = setting_osr2dataPin;

// Define Connections to 74HC595 - Coil Output Shift Registers
//const int osr3latchPin = 23;
//const int osr3clockPin = 22;
//const int osr3dataPin = 15; //changed from 1
const int osr3latchPin = setting_osr3latchPin;
const int osr3clockPin = setting_osr3clockPin;
const int osr3dataPin = setting_osr3dataPin; 

//Comms to 74HC165 - Input Shift Registers
//int isrload = 25;
//int isrclockEnablePin = 32; //latch
//int isrdataIn = 33;
//int isrclockIn = 26;
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

int counter;
unsigned long lastMillis;



int timerSw;
unsigned long lastMillisTimerSw;

int counterCoil;
unsigned long lastMillisCoil;


void MonitorSwitchesAndRegisterFunction( void * pvParameters)
{
  Serial.print("MonitorSwitches running on core ");
  Serial.println(xPortGetCoreID());
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
          Serial.print("[threadDebug] MonitorSwitches Loop: CORE ");
          Serial.print(xPortGetCoreID());
          Serial.print(" : is currently running at approximatly ");
          Serial.print(counterSw);
          Serial.println("Hz (full program cycles per second)");
          
        }
        CMOHz = counterSw;
        counterSw = 0;
        lastMillisSw = millis();
        
      }// End of debug stuff 
        
      //if(generalMODebug) Serial.println("[generalMODebug] Switch Matrix Processing...");
      //Check for switch triggers
      measureMicro = micros();
      scanSwitchMatrix();
      scanMicro = scanMicro + (micros() - measureMicro);
      //if(generalMODebug) Serial.println("[generalMODebug] Flipper triggering...");  
      //fire off flippers if triggered 
      measureMicro = micros();
      triggerFlippers();//soon to be redundant when flipper switches are direct connected to GPIO pins.
      flipperMicro = flipperMicro + (micros() - measureMicro);
      //if(generalMODebug) Serial.println("[generalMODebug] Switch triggering...");
      //process switch events
      measureMicro = micros();
      triggerSwitches();//Needs to be done on a separate thread on a timer.
      triggerSwitchMicro = triggerSwitchMicro + (micros() - measureMicro);
      //if(generalMODebug) Serial.println("[generalMODebug] Coil processing...");
      //manage coils - release if needed
      measureMicro = micros();
      manageCoils();//Needs to be done on a separate thread on a timer.
      manageCoilMicro = manageCoilMicro + (micros() - measureMicro);
      //if(generalMODebug) Serial.println("[generalMODebug] Switch processing...");
      measureMicro = micros();
      processAllSwitches();//Needs to be done on a separate thread on a timer.
      processSwitchMicro = processSwitchMicro + (micros() - measureMicro);
      lastMicrosLoopRan = micros();


      if(threadDebug)
      {
        unsigned long totalLoopProcessingTime = 0;

        Serial.print("Scan Switch Matrix Time (uS) : ");
        Serial.println(scanMicro);
        totalLoopProcessingTime = totalLoopProcessingTime + scanMicro;
        scanMicro = 0;

        Serial.print("Trigger Flipper Time (uS) : ");
        Serial.println(flipperMicro);
        totalLoopProcessingTime = totalLoopProcessingTime + flipperMicro;
        flipperMicro = 0;

        Serial.print("Trigger Switch Time (uS) : ");
        Serial.println(triggerSwitchMicro);
        totalLoopProcessingTime = totalLoopProcessingTime + triggerSwitchMicro;
        triggerSwitchMicro = 0;

        Serial.print("Manage Coil Time (uS) : ");
        Serial.println(manageCoilMicro);
        totalLoopProcessingTime = totalLoopProcessingTime + manageCoilMicro;
        manageCoilMicro = 0;

        Serial.print("Process Switch Time (uS) : ");
        Serial.println(processSwitchMicro);
        totalLoopProcessingTime = totalLoopProcessingTime + processSwitchMicro;
        processSwitchMicro = 0;

        Serial.print("Total Task Processing time uS : ");
        Serial.println(totalLoopProcessingTime);

        Serial.println("_________________________________");
      }



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
* Function identifyFlippers
* loop through all columns and rows and check for a switches that are marked as flippers.  
* When they are identified, set the leftFlipperCol, LeftFlipperRow, rightFlipperCol, rightFlipperRow variables.
*/
void identifyFlippers()
{
  //IDEA - would it be faster to refine to just those with action? A list of switch numbers?
  char i = 0;
  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) 
  {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {    
      int flipperSwitchID = (col*8)+row;
      if(switches[flipperSwitchID].switchObject->isFlipper()==true) //we are desling with flippers
      { 
        colflipper[i] = col;
        rowflipper[i] = row;    
        Serial.print("Flipper ");
        Serial.print(i);
        Serial.print(" Detected on Column[");
        Serial.print(col);
        Serial.print("] x Row[");
        Serial.print(row);
        Serial.println("]");
        i++;
      }
    }
  }   
}
/*
* Function triggerFlippers
* loop through all columns and rows and check for a switches that are marked as flippers.  
* If a switch is closed, and its a flipper - enable the flipper solenoid.
* If a switch is open, and its a flipper and the solenoid id on - disable the flipper solenoid.
*/
void triggerFlippers()
{
  //IDEA - would it be faster to refine to just those with action? A list of switch numbers?
  for(char i = 0; i < flipperButtons; i++)
  {
    char col = colflipper[i];
    char row = rowflipper[i];
    int flipperSwitchID = (col*8)+row;
    PinballCoil* flipperCoil = coils[flipperCoilBindings[flipperSwitchID].coilNumber].coilObject;
    if((switchActive[col][row]==true)) //flipper button is pressed
    {
      
      if(generalMODebug)
      {
        Serial.print("Flipper button pressed....");
        Serial.println(flipperSwitchID);
        Serial.print("need to locate coil associated ");
        Serial.println(flipperCoilBindings[flipperSwitchID].coilNumber);
      } 
      if(flipperCoil->checkStatus()==false) //coil is currently off
      {
        if(generalMODebug)
        {
          Serial.print("Coil disabled but button pressed, enabling ");
          Serial.println(flipperCoil->getName());
        }
        if(MachineState == 2) //only if game is active
        {
          flipperCoil->enable(); //mark the coil as enabled - perminantly on
          ProcessShifts(flipperCoil); //set shift register bytes to turn on solenoid
          write_sr_coils();  //action shift register changes
          flipperCoil->actioned(); //mark the coil changes as done
        }

      }
    }else if(flipperCoil->checkStatus()==true)//so the button isnt on, but the coil is
    {
      if(generalMODebug)
      {
        Serial.println("Coil enable but button not pressed, starting manage() function to determine if it can be turned off");
        Serial.println("Coil insists it needs action to turn on or off");  
      } 
      flipperCoil->disable(); //mark the coil as off
      flipperCoil->manage(); //run management routine to do the needful
      ProcessShifts(flipperCoil); //set shift register bytes to turn off solenoid
      write_sr_coils(); //action shift register changes
      flipperCoil->actioned(); //mark the coil changes as done
    }//end button not presesed  
  } 
}
/*
* Function triggerSwitches
* loop through all columns and rows and check for a switches that are marked as NOT flippers, but are marked true in the switchActive array.  
* If a switch is closed, make the switchScored array value true
* If a switch is closed and bound to a coil, fire the associated coil.
* If a switch is closed and nat bound to a coil, do no more work.
*/

void IRAM_ATTR fireFlipper(int flipperSwitchID)
{
  PinballCoil* flipperCoil = coils[flipperCoilBindings[flipperSwitchID].coilNumber].coilObject;

  if(generalMODebug)
  {
    Serial.print("Flipper button pressed....");
    Serial.println(flipperSwitchID);
    Serial.print("need to locate coil associated ");
    Serial.println(flipperCoilBindings[flipperSwitchID].coilNumber);
  } 
  if(flipperCoil->checkStatus()==false) //coil is currently off
  {
    if(generalMODebug)
    {
      Serial.print("Coil disabled but button pressed, enabling ");
      Serial.println(flipperCoil->getName());
    }
    if(MachineState == 2) //only if game is active
    {
      flipperCoil->enable(); //mark the coil as enabled - perminantly on
      ProcessShifts(flipperCoil); //set shift register bytes to turn on solenoid
      write_sr_coils();  //action shift register changes
      flipperCoil->actioned(); //mark the coil changes as done
    }
  }  
}
void IRAM_ATTR releaseFlipper(int flipperSwitchID)
{
  PinballCoil* flipperCoil = coils[flipperCoilBindings[flipperSwitchID].coilNumber].coilObject;

  if(generalMODebug)
  {
    Serial.print("Flipper button pressed....");
    Serial.println(flipperSwitchID);
    Serial.print("need to locate coil associated ");
    Serial.println(flipperCoilBindings[flipperSwitchID].coilNumber);
  } 
  if(flipperCoil->checkStatus()==true) //coil is currently off
  {
    
    if(MachineState == 2) //only if game is active
    {
      if(generalMODebug)
      {
        Serial.println("Coil enable but button not pressed, starting manage() function to determine if it can be turned off");
        Serial.println("Coil insists it needs action to turn on or off");  
      } 
      flipperCoil->disable(); //mark the coil as off
      flipperCoil->manage(); //run management routine to do the needful
      ProcessShifts(flipperCoil); //set shift register bytes to turn off solenoid
      write_sr_coils(); //action shift register changes
      flipperCoil->actioned(); //mark the coil changes as done
    }
  }  
}
void IRAM_ATTR fireFlipper1()
{
  fireFlipper(1);
}
void IRAM_ATTR releaseFlipper1()
{
  releaseFlipper(1);
}
void IRAM_ATTR fireFlipper2()
{
  fireFlipper(2);
}
void IRAM_ATTR releaseFlipper2()
{
  fireFlipper(2);
}


void triggerSwitches()
{
  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {    
      int triggeredSwitchID = (col*8)+row;

      if(switchActive[col][row]==true) 
      {//switch triggered physically
        Serial.println("function->triggerSwitches - switch name: " + switches[triggeredSwitchID].switchObject->getName());
        if(switches[triggeredSwitchID].switchObject->triggerSwitch()==true)//this will return false if debounce period still active
        {
          switchScored[col][row]=true; //get credit for hitting the switch of do switch hit activity - this is picked up in processAllSwitches()
          if(generalMODebug)
          {
            Serial.print("TriggerSwitches(): ");
            Serial.println(switches[triggeredSwitchID].switchObject->getName());
          } 
          if(switchCoilBindings[triggeredSwitchID].coilNumber > 0) //if we have a coil bound to the switch
          {
            if(switchCoilBindings[triggeredSwitchID].instantFire == true) //we need to fire the coil straight away
            {
              if(generalMODebug)
              {
                Serial.print("Switch triggered with coil binding....");
                Serial.println(triggeredSwitchID);
                Serial.println("need to locate coil associated ");         
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
                Serial.print("Switch triggered with coil binding, but no instant trigger");
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
          switchActive[col][row]=false;
        }//end triggered switch processing  
      }//end switch processing
    }//end row processing
  }//end col processing
}
/*
* Function processAllSwitches
* loop through all columns and rows and check for a switchScored array values that are true. 
* If a switch is closed, make the switchScored array value true.
*/
void processAllSwitches()
{
  //Serial.println("[Function] processAllSwitches()");
  //look for switch scored
  //IDEA - would it be faster to refine to just those with action? A list of switch numbers?
  for ( byte col = 0; col < setting_switchMatrixColumns ; col++) 
  {
    for (byte row = 0; row < setting_switchMatrixRows; row++) 
    {
      if(switchScored[col][row]==true)
      {
        //Serial.print("[Function] processAllSwitches() -> scoredSwitch = ");
        byte coilNumber = 0;
        int triggeredSwitchID = (col * 8)+row;
        if(switches[triggeredSwitchID].switchObject->isStart()==true)
        {
          Serial.println("function->triggerSwitches : this is start");
          switch_event_startbutton(triggeredSwitchID);
        }
          
        if(switches[triggeredSwitchID].switchObject->isOuthole()==true)
        {
          Serial.println("function->triggerSwitches : this is outhole");
          switch_event_outhole(triggeredSwitchID);
        }

        /*switch(scoredSwitch)
        {
          case 0: //outhole switch fire coil 14 - outhole
          {
            switch_event_outhole();
            break;
          }

        }*/
        switchScored[col][row]=false;
      }
    }
  }
  //need individual switch logic - things need to happen, different modes mean different outcomes - for later
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
      Serial.print("Turning off coil ");
      Serial.print(CoilObject->getName());
      Serial.print("- OSR3 - BIT:");
      Serial.println(CoilObject->getSRBit());
      bitClear(outgoing3,CoilObject->getSRBit());
    }
  }else if(CoilObject->getSR() == 1)
  {
    if(CoilObject->checkStatus())
    {
      Serial.print("Turning on coil ");
      Serial.print(CoilObject->getName());
      Serial.print("- OSR4 - BIT:");
      Serial.println(CoilObject->getSRBit());
      bitSet(outgoing4,CoilObject->getSRBit());

    }else
    {
      Serial.print("Turning off coil ");
      Serial.print(CoilObject->getName());
      Serial.print("- OSR4 - BIT:");
      Serial.println(CoilObject->getSRBit());
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
void write_sr_audio() 
{ // Write to the output shift registers
  digitalWrite(osr2latchPin, LOW);
  shiftOut(osr2dataPin, osr2clockPin, LSBFIRST, outgoing2); // changed to MSB to reflect physical wiring
  digitalWrite(osr2latchPin, HIGH);   
  if(srDebug){
    Serial.print("write_sr_audio : outgoing2 [");
    Serial.print(outgoing2);
    Serial.println("]");
  }   
}   
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
    byte coilNumber = 14; // fix this - must fin
    //only fire if in a game
    if(g_myPinballGame.isGameActive()==true)
    {
      Serial.println("Fire Outhole");
      PinballCoil* switchCoil = coils[coilNumber].coilObject;
      if(switchCoil->fireCoil()){
        coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
        ProcessShifts(switchCoil); //action the turning on
        write_sr_coils(); //update shift register
      }
    }else
    {
      //ok so game was active, now its not, game over calls need to be made
  
      changeState(3); //moving to End of game

      //need much more code here, but ok for now
    }
  }else
  {
    //Do nothing - ball should be here when game not on
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
  Serial.println("switch_event_startbutton");
  if(MachineState == 1)
  {
    changeState(2);
  } else if(MachineState == 2)
  {//if player1 is still on first ball, add more players
    g_myPinballGame.addPlayer(); //This will add players up to the defined maximum
  } else if(MachineState == 3)
  {//new game
    changeState(2);
  }
}

void addScore(int switchID)
{
  int score = (switches[switchID].baseScore) * g_myPinballGame.getPlayfieldMultiplier();
  int playerNumber = g_myPinballGame.getCurrentPlayerNumber();
  int playerscore = g_myPinballGame.getPlayerScore(playerNumber) + score;
  g_myPinballGame.setPlayerScore(playerNumber,playerscore);
  ScoreboardBText = g_myPinballGame.getPlayerScore(playerNumber);
  ScoreboardTText = "P" + (String)playerNumber + " Ball " + (String)g_myPinballGame.getCurrentBallNumber(playerNumber);
}

