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
              Serial.println("[changeState] - - Attract->Game");
              ScoreboardTText = "Lets, Play,";
              ScoreboardBText = "Pool!";
              MachineState = 2;
              lastMachineState = 1;
              forceDisplayUpdate = true;
              g_myPinballGame.newGame();
              //enable power to coils
              digitalWrite(hvrPin, LOW);
            }else if (newState == 5)
            {
              //moving from End Game to Atract : OK
              Serial.println("[[changeState] - - Attract->Diagnostics");
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
              Serial.println("[changeState] - - Game->End Game");

              MachineState = 3;
              lastMachineState = 2;
              forceDisplayUpdate = true;
              g_myPinballGame.endGame(); //end the game - this resets a load of stuff, we may want to run this on a new game start??
              //disable power to coils
              digitalWrite(hvrPin, HIGH);

            }else if (newState == 5)
            {
              //moving from End Game to Atract : OK
              Serial.println("[[changeState] - - Game->Diagnostics");
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
              //enable power to coils
              digitalWrite(hvrPin, HIGH);
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


