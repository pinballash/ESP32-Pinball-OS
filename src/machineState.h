#include <Arduino.h>

void changeState(int newState)
{
    /* states accepted are Bootup-0, Atract-1, Game-2, End Game-3, End Ball-4, Diagnostics-5
    Bootup, this is set during initialisation and cannot be set again
    Atract, this is fired automatically following bootup or end game
    Game, this can be triggered by start button press
    End Game, this is triggered when all balls played
    */
    //lets process based on current state then deal with the change request if we are allowed
    switch(MachineState){
      case 0: //Bootup
          {
            //only one valid change here - from Bootup to Atract
            if(newState == 1)
            {
              //moving from Bootup to Atract : OK
              Serial.println("[changeState] - Boot->Atract");
              MachineState = 1;
              lastMachineState = 0;
              forceDisplayUpdate = true;
            }
            break;
          }
      case 1: //Attract
          {
            //only one valid change here - from Atract to Game
            if(newState == 2)
            {
              //moving from Bootup to Atract : OK
              Serial.println("[changeState] - Attract->Game");
              ScoreboardTText = "Lets, Play,";
              ScoreboardBText = "Pool!";
              MachineState = 2;
              lastMachineState = 1;
              forceDisplayUpdate = true;
              g_myPinballGame.newGame();
              //enable power to coils
              digitalWrite(hvrPin, LOW);
              //custom game start code here
              /*fire the standups and enable score*/
              /*
              first we get the switch number, 
              then we get the switch coil binding
              we fire off the bound coil and then we reset the score
              */
             /*25,26,28,29,31*/
              //delay(100);
              byte switchByte1 = 25;
              PinballSwitch* thisSwitch1 = switches[switchByte1].switchObject;
              byte* thisSwitchCoilBinding1 = switchCoilBindings[switchByte1].coilNumber;
              PinballCoil* thisCoil1 = coils[*thisSwitchCoilBinding1].coilObject; //get the PinballCoil instance associated
              ScoreboardTText = "Firing ";
              ScoreboardBText = (String)thisCoil1->getName();
              forceDisplayUpdate = true;
              thisCoil1->fireCoil();
              thisSwitch1->turnOn();

              delay(50);
              byte switchByte2 = 26;
              PinballSwitch* thisSwitch2 = switches[switchByte2].switchObject;
              byte* thisSwitchCoilBinding2 = switchCoilBindings[switchByte2].coilNumber;
              PinballCoil* thisCoil2 = coils[*thisSwitchCoilBinding2].coilObject; //get the PinballCoil instance associated
              ScoreboardTText = "Fire";
              ScoreboardBText = "Solenoid 2";
              thisCoil2->fireCoil();
              thisSwitch2->turnOn();
              //delay(250);
              //ScoreboardTText = "-";
              //ScoreboardBText = "-";
              //forceDisplayUpdate = true;
             

              //end custom game start code


            }else if (newState == 5)
            {
              //moving from End Game to Atract : OK
              Serial.println("[[changeState] - Attract->Diagnostics");
              MachineState = 5;
              lastMachineState = 1;
              forceDisplayUpdate = true;
              
            }
            break;
          }    
      case 2: //Game
          {
            //valid changes here - from Game to End Game
            if(newState == 3)
            {
              //moving from Game to End Game : OK
              Serial.println("[changeState] - Game->End Game");

              MachineState = 3;
              lastMachineState = 2;
              forceDisplayUpdate = true;
              Serial.println("[changeState] - Ending Game");
              g_myPinballGame.endGame(); //end the game - this resets a load of stuff, we may want to run this on a new game start??
              //disable power to coils
              Serial.println("[changeState] - Disable High Voltage");
              digitalWrite(hvrPin, HIGH);

            }else if (newState == 5)
            {
              //moving from End Game to Atract : OK
              Serial.println("[[changeState] - Game->Diagnostics");
              MachineState = 5;
              lastMachineState = 2;
              forceDisplayUpdate = true;
              
            }
            break;
          }
      case 3: //End Game
          {
            //Two valid changes here - from End Game to Game and from End Game to Atract (later HSTD entry)
            if(newState == 2)
            {
              //moving from End Game to Game : OK
              Serial.println("[changeState] - - End Game->Game");
              ScoreboardTText = "Lets, Play,";
              ScoreboardBText = "Pool!";
              MachineState = 2;
              lastMachineState = 3;
              forceDisplayUpdate = true;
              g_myPinballGame.newGame();

            }else if (newState == 1)
            {
              //moving from End Game to Atract : OK
              Serial.println("[[changeState] - - End Game->Attract");
              MachineState = 1;
              lastMachineState = 3;
              forceDisplayUpdate = true;
              
            }
            break;
          }
      
    }

}


