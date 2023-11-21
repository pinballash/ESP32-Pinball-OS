#include <Arduino.h>
#include "PinballSwitch.h"
#include "PinballCoil.h"
#include "PinballGame.h"

bool switchDebug = false;
bool coilDebug = false;
bool loopDebug = false;
bool threadDebug = false;
bool srDebug = false;
bool osrDebug = true;
bool generalMODebug = true;
unsigned long ScanSwitchMatrixEveryMicroSeconds = 800; //this seems to be the value where we can operate at around 500 times per second

PinballGame g_myPinballGame(setting_MachineName);


#include "switchArray_def.h"
#include "coilArray_def.h"
#include "flipperBindings_def.h"
#include "coilBindings_def.h"

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
void switch_event_outhole();
void switch_event_saucer(int switchID);
void switch_event_drop1(int switchID);
void switch_event_drop2(int switchID);
void switch_event_drop3(int switchID);
void switch_event_drop4(int switchID);
void switch_event_drop5(int switchID);
void switch_event_startbutton();
void switch_event_pop(int switchID);

void switch_event_outane_left(int switchID);
void switch_event_outane_right(int switchID);

void switch_event_lane_c(int switchID);
void switch_event_lane_h(int switchID);
void switch_event_lane_a(int switchID);
void switch_event_lane_m(int switchID);
void switch_event_lane_p(int switchID);

void switch_event_rollover_center(int switchID);
void switch_event_rollover_left(int switchID);
void switch_event_rollover_right(int switchID);

void switch_event_spinner(int switchID);

void switch_event_standup_e(int switchID);
void switch_event_standup_i(int switchID);
void switch_event_standup_g(int switchID);
void switch_event_standup_h(int switchID);
void switch_event_standup_t(int switchID);


void addScore(int switchID);
void changeState(int newState);

//setup a task to run on core 0;
TaskHandle_t MonitorSwitchesAndRegister;

//setup array for storing switch active
const int tableRows = 8; // 0 to 7
const int tableCols = 5; // 0 to 4
const int switchCount = tableRows * tableCols;
const int flipperButtons = 2;
bool switchActive[tableCols][tableRows];//cols, rows, only 5 cols used on 8 Ball champ - change arrays if need more cols.
bool switchScored[tableCols][tableRows];//cols, rows, only 5 cols used on 8 Ball champ - change arrays if need more cols.
char colflipper[flipperButtons]; // flipper button cols
char rowflipper[flipperButtons]; // flipper button rows
unsigned long player1score = 0;
unsigned long player2score = 0;
unsigned long player3score = 0;
unsigned long player4score = 0;
int playfieldMultiplier = 1;

//setup array fo maintaining the state of coils
const int coilCount = 17;
bool coilActive[coilCount];


// Define Connections to 74HC595 - Matrix Output Shift Register
const int osr1latchPin = 18;
const int osr1clockPin = 5;
const int osr1dataPin = 17;

// Define Connections to 74HC595 - Audio Output Shift Register
const int osr2latchPin = 2; //changed from 3
const int osr2clockPin = 21;
const int osr2dataPin = 19;

// Define Connections to 74HC595 - Coil Output Shift Registers
const int osr3latchPin = 23;
const int osr3clockPin = 22;
const int osr3dataPin = 15; //changed from 1

//Comms to 74HC165 - Input Shift Registers
int isrload = 25;
int isrclockEnablePin = 32; //latch
int isrdataIn = 33;
int isrclockIn = 26;

// input and output bytes for the shift registers
byte incoming;
byte incoming2;
byte outgoing=0; // used for switch matrix - only 5 cols implemented - can expand to 8
byte outgoing2=255; // used for sound, so needs to be all kept high
byte outgoing3=0;// used for solenoids
byte outgoing4=0;//used for solenoids

bool needsRegisterUpdate = false;

//High Voltage Relay pin
const int hvrPin = 27;

//Flipper 1 pin
const int flipper1Pin = 34;

//Flipper 2 pin
const int flipper2Pin = 35;

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
 for ( byte col = 0; col < tableCols ; col++) 
 {
  outgoing = 0;
  bitSet(outgoing,(7-col));  
  write_sr_matrix();  // So sets the column high,
  bitClear(outgoing,col); //no longer needs to be set, we sent it
  delayMicroseconds(2); // give the register time to update
  read_sr();
  for (byte row = 0; row < tableRows; row++) 
  {    
    if (bitRead(incoming,row)) 
    {
      switchActive[col][row] = true; 
    } else {
      switchActive[col][row] = false; //default to not active (off)
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
  for ( byte col = 0; col < tableCols ; col++) 
  {
    for (byte row = 0; row < tableRows; row++) 
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
  //IDEA - would it be faster to refine to just those with action? A list of switch numbers?
  for ( byte col = 0; col < tableCols ; col++) {
    for (byte row = 0; row < tableRows; row++) 
    {    
      int triggeredSwitchID = (col*8)+row;
      if((switchActive[col][row]==true) && (switches[triggeredSwitchID].switchObject->isFlipper()==false))//flipper processing done in triggerFlippers() function
      {//switch triggered physically and not flipper
        if(switches[triggeredSwitchID].switchObject->triggerSwitch()==true)//this will return false if debounce period still active
        {
          switchScored[col][row]=true; //get credit for hitting the switch - this is picked up in processAllSwitches()
          if(generalMODebug)
          {
            Serial.print("TriggerSwitches(): ");
            Serial.println(switches[triggeredSwitchID].switchObject->getName());
          } 
          if(switchCoilBindings[triggeredSwitchID].coilNumber > 0) //if we have a coil bound to the switch, it needs fireing immediately
          {
            if(generalMODebug)
            {
              Serial.print("Switch triggered with coil binding....");
              Serial.println(triggeredSwitchID);
              Serial.print("need to locate coil associated ");
              Serial.println(switchCoilBindings[triggeredSwitchID].coilNumber);              
            } 
            byte coilNumber = switchCoilBindings[triggeredSwitchID].coilNumber; //get the coil number bound to the switch
            PinballCoil* switchCoil = coils[coilNumber].coilObject; //get the PinballCoil instance associated
            if(MachineState == 2) //only if game is active
            {
              if(switchCoil->fireCoil()){ //try and fire the coil
                coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
                ProcessShifts(switchCoil); //set shift register bytes to turn on solenoid
                write_sr_coils(); //update shift register
              }
            }
          }else{
            //other switch actions can wait for processing
            //set switchProcessingArray
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
* If a switch is closed, make the switchScored array value true.
*/
void processAllSwitches()
{
  //Serial.println("[Function] processAllSwitches()");
  //look for switch scored
  //IDEA - would it be faster to refine to just those with action? A list of switch numbers?
  for ( byte col = 0; col < tableCols ; col++) 
  {
    for (byte row = 0; row < tableRows; row++) 
    {
      if(switchScored[col][row]==true)
      {
        //Serial.print("[Function] processAllSwitches() -> scoredSwitch = ");
        byte coilNumber = 0;
        int scoredSwitch = (col * 8)+row;
        Serial.println(scoredSwitch);

        switch(scoredSwitch)
        {
          case 0: //outhole switch fire coil 14 - outhole
          {
            switch_event_outhole();
            break;
          }
          case 13: //Start Button
          {
            switch_event_startbutton();
            break;
          }
          case 3: //Saucer
          {
            switch_event_saucer(3);
            break;
          }
          case 6: //Pop left
          {

            switch_event_pop(6);
            break;
          }
          case 7: //Pop right
          {
            switch_event_pop(7);
            break;
          }
          case 31: //Drop 1
          {
            switch_event_drop1(31);
            break;
          }
          case 29: //Drop 2
          {
            switch_event_drop2(29);
            break;
          }
          case 28: //Drop 3
          {
            switch_event_drop3(28);
            break;
          }
          case 27: //Center Rollover
          {
            switch_event_rollover_center(27);
            break;
          }
          case 26: //Drop 4
          {
            switch_event_drop4(26);
            break;
          }
          case 16: //Oulane Left
          {
            switch_event_outane_left(16);
            break;
          }
          case 17: //Outlane Right
          {
            switch_event_outane_right(17);
            break;
          }
          /*case 18: // not used
          {
            switch_event_(18);
            break;
          }*/
          case 19: //P Lane
          {
            switch_event_lane_p(19);
            break;
          }
          case 20: //M Lane
          {
            switch_event_lane_m(20);
            break;
          }
          case 21: //A Lane
          {
            switch_event_lane_a(21);
            break;
          }
          case 22: //H Lane
          {
            switch_event_lane_h(22);
            break;
          }
          case 23: //C Lane
          {
            switch_event_lane_c(23);
            break;
          }
          case 24: //Spinner
          {
            switch_event_spinner(24);
            break;
          }
          case 11: //Right Rollover
          {
            switch_event_rollover_right(11);
            break;
          }
          case 12: //Left Rollover
          {
            switch_event_rollover_left(12);
            break;
          }
          case 35: //T Standup
          {
            switch_event_standup_t(35);
            break;
          }
          case 36: //H Standup
          {
            switch_event_standup_h(36);
            break;
          }
          case 37: //G Standup
          {
            switch_event_standup_g(37);
            break;
          }
          case 38: //I Standup
          {
            switch_event_standup_i(38);
            break;
          }
          case 39: //E Standup
          {
            switch_event_standup_e(39);
            break;
          }
        }
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
  //Serial.print("Processing Shifts ");
  //Serial.println(CoilObject->getName());
 
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
  for ( byte coilNumber = 1; coilNumber < coilCount+1 ; coilNumber++) {
    if(coilActive[coilNumber]==true)
    {
      //if(generalMODebug) Serial.print("Attempting to manage coil....");
      //if(generalMODebug) Serial.println(coilNumber);
      //need to understand if its time to turn off the coil....
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
void switch_event_outhole()
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
    byte coilNumber = 14;
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
void switch_event_saucer(int switchID)
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
}
void switch_event_pop(int switchID)
{
  //saucer code here
  Serial.println("Fire Pop");
  //ScoreboardTText = "Pop!";
  addScore(switchID);
  
}
void switch_event_drop1(int switchID)
{
  //drop 1 code here
  Serial.println("Fire Drop 1");
  //ScoreboardTText = "Drop 1";
  byte coilNumber = 8;
  PinballCoil* switchCoil = coils[coilNumber].coilObject;
  if(switchCoil->fireCoil()){
    coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
    ProcessShifts(switchCoil); //action the turning on
    write_sr_coils(); //update shift register
  }
  addScore(switchID);
}
void switch_event_drop2(int switchID)
{
  //drop 2 code here
  Serial.println("Fire Drop 2");
  //ScoreboardTText = "Drop 2";
  byte coilNumber = 9;
  PinballCoil* switchCoil = coils[coilNumber].coilObject;
  if(switchCoil->fireCoil()){
    coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
    ProcessShifts(switchCoil); //action the turning on
    write_sr_coils(); //update shift register
  }
  addScore(switchID);
}
void switch_event_drop3(int switchID)
{
  //drop 3 code here
  Serial.println("Fire Drop 3");
  //ScoreboardTText = "Drop 3";
  byte coilNumber = 10;
  PinballCoil* switchCoil = coils[coilNumber].coilObject;
  if(switchCoil->fireCoil()){
    coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
    ProcessShifts(switchCoil); //action the turning on
    write_sr_coils(); //update shift register
  }
  addScore(switchID);
}
void switch_event_drop4(int switchID)
{
  //drop 4 code here
  Serial.println("Fire Drop 4");
  //ScoreboardTText = "Drop 4";
  byte coilNumber = 11;
  PinballCoil* switchCoil = coils[coilNumber].coilObject;
  if(switchCoil->fireCoil()){
    coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
    ProcessShifts(switchCoil); //action the turning on
    write_sr_coils(); //update shift register
  }
  addScore(switchID);
}
void switch_event_drop5(int switchID)
{
  //drop 5 code here
  Serial.println("Fire Drop 5");
  //ScoreboardTText = "Drop 5";
  byte coilNumber = 12;
  PinballCoil* switchCoil = coils[coilNumber].coilObject;
  if(switchCoil->fireCoil()){
    coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
    ProcessShifts(switchCoil); //action the turning on
    write_sr_coils(); //update shift register
  }
  addScore(switchID);
}
void switch_event_startbutton()
{
  Serial.println("switch_event_startbutton");
  if(MachineState == 1)
  {
      changeState(2);


  } else if(MachineState == 2)
  {//if player1 is still on first ball, add more players
      g_myPinballGame.addPlayer(); //This will add players up to the defined maximum
  } else if(MachineState == 3)
  {
    //new game
    changeState(2);
  }
}
void switch_event_outane_left(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_outane_right(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_lane_c(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_lane_h(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_lane_a(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_lane_m(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_lane_p(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_rollover_center(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_rollover_left(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_rollover_right(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_spinner(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_standup_t(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_standup_h(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_standup_i(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_standup_g(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
  }
}
void switch_event_standup_e(int switchID)
{
  if(MachineState == 2)
  {//if game active
    addScore(switchID);
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
  //ScoreboardTLText = "Ball " + (String)g_myPinballGame.getCurrentBallNumber(playerNumber);
}

