#include "PinballGame.h"

PinballGame::PinballGame(String GameName)
{
 //initialiser
 this->_gameName = GameName;
}

  void PinballGame::newGame()
  {
    //reset values
    this->resetAllPlayerData();
    this->_currentPlayer = 1;
    this->_playerCount = 1;
    this->_ballSave = true;
    this->_gameActive = true;
    this->DMDTopLine = "New";
    this->DMDBottomLine = "Game";
    delay(500);
    this->_player1CurrentBall = 1; 
    this->DMDTopLine = "1 Player";
    this->DMDBottomLine = "Game";
    //this->resetAllPlayerData();
    //enable power to coils
    extern const int setting_hvrPin;
    //digitalWrite(setting_hvrPin, HIGH);
  }
  void PinballGame::endGame()
  {
    this->_gameActive = false;
    this->_currentPlayer = 1;
    this->DMDTopLine = "Game";
    this->DMDBottomLine = "Over";
    extern const int setting_hvrPin;
    //digitalWrite(setting_hvrPin, LOW);
  }
  void PinballGame::addPlayer()
  {
    if((this->_playerCount < 4) && (this->getCurrentBallNumber(1)==1))//Only add players when still on ball 1
    {
        this->_playerCount = this->_playerCount+1;

        switch (this->_playerCount)
        {
        case 2:
            {
              this->_player2CurrentBall = this->_player2CurrentBall +1;
              this->DMDTopLine = "2 Player";
              this->DMDBottomLine = "Game";
              break;
            }
        case 3:
            {
              this->_player3CurrentBall = this->_player3CurrentBall +1;
              this->DMDTopLine = "3 Player";
              this->DMDBottomLine = "Game";
              break;
            }
        case 4:
            {
              this->DMDTopLine = "4 Player";
              this->DMDBottomLine = "Game";
              this->_player4CurrentBall = this->_player4CurrentBall +1;
              break;
            }
        
        }
    }
    

  }
  void PinballGame::endOfBall(int playerNumber)
  {
    
    if(this->_gameActive == false)
    {
      return;
    }
    //are there any other players?
    extern String tso_PinballGame;
    tso_PinballGame = "[PinballGame] Call endOfBall";
    
    int ballCounter = 0;
    switch (playerNumber)
    {
    case 1:
        {
         
          //tso_PinballGame = "[PinballGame] End of ball -> Player1 add a ball";
          this->DMDTopLine = "End of Ball";
          this->DMDBottomLine = "Player 1";
          this->_player1CurrentBall = this->_player1CurrentBall +1;
          ballCounter = this->_player1CurrentBall;
          delay(3000); 
          break;
        }
    case 2:
        {
          //Serial.println("[PinballGame] End of ball : Player2 add a ball");
          //tso_PinballGame = "[PinballGame] Call endOfBall";
          this->DMDTopLine = "End of Ball";
          this->DMDBottomLine = "Player 2";
          this->_player2CurrentBall = this->_player2CurrentBall +1; 
          ballCounter = this->_player2CurrentBall; 
          delay(3000); 
          break;
        }
    case 3:
        {
          //Serial.println("[PinballGame] End of ball : Player3 add a ball");
          this->_player3CurrentBall = this->_player3CurrentBall +1; 
          this->DMDTopLine = "End of Ball";
          this->DMDBottomLine = "Player 3";
          ballCounter = this->_player3CurrentBall; 
          delay(3000); 
          break;
        }
    case 4:
        {
          //Serial.println("[PinballGame] End of ball : Player4 add a ball");
          this->_player4CurrentBall = this->_player4CurrentBall +1; 
          this->DMDTopLine = "End of Ball";
          this->DMDBottomLine = "Player 4";
          ballCounter = this->_player4CurrentBall;
          delay(3000); 
          break;
        }
    }
    //Serial.print("[PinballGame] End of ball : ballCounter=");
    //Serial.println(ballCounter);

    if(playerNumber < this->_playerCount)
    {
      //Serial.println("[PinballGame] End of ball : There are more players than current");
      playerNumber +=1;
      this->DMDTopLine = "Next up";
      this->DMDBottomLine = "Player " + String(playerNumber);
      
    }else{
      //Serial.println("[PinballGame] End of ball : Set to Player1");
      playerNumber=1;
      this->DMDTopLine = "Next up";
      this->DMDBottomLine = "Player " + String(playerNumber);
      
    }
    if((playerNumber == 1) && (this->_player1CurrentBall > this->_maxBalls))
    {
      //Serial.println("[PinballGame] End of ball : Out of balls");
      //game over - game over code needs to run, sould, lights, diaplay, but thats beyond the scope of this class - we can check for game over elsewhere.
      this->_player1CurrentBall = this->_maxBalls;
      endGame();
   
    }
    else
    {
      //Serial.println("[PinballGame] End of ball : Ball save set to ON, next ball");
      
      tso_PinballGame = tso_PinballGame + "[PinballGame] End of ball";
      this->_currentPlayer = playerNumber;
      this->_ballSave = true;
    }
    
    
  }
  int PinballGame::getCurrentBallNumber(int playerNumber)
  {
    switch (playerNumber)
    {
    case 1:
        {
          return this->_player1CurrentBall;
          break;  
        }
    case 2:
        {
          return this->_player2CurrentBall;
          break;   
        }
    case 3:
        {
          return this->_player3CurrentBall;
          break;   
        }
    case 4:
        {
          return this->_player4CurrentBall;
          break;  
        }
    }
    return 0;
  }
  bool PinballGame::isGameActive()
  {
    return this->_gameActive;
  }
  bool PinballGame::isBallSave()
  {
    return this->_ballSave;
  }
  int PinballGame::getMaxBalls(){
    return this->_maxBalls;
  }
  void PinballGame::setMaxBalls(int maxBalls){
    this->_maxBalls = maxBalls;
  }



  String PinballGame::getName()
  {
    return this->_gameName;
  }
  unsigned long PinballGame::getPlayerScore(int playerNumber)
  {
    unsigned long returnScore = 0;
    switch (playerNumber)
    {
    case 1:
        {
          returnScore = this->_player1score;
          break;  
        }
    case 2:
        {
          returnScore = this->_player2score;
          break;  
        }
    case 3:
        {
          returnScore = this->_player3score;
          break;  
        }
    case 4:
        {
          returnScore = this->_player4score;
          break;  
        }
    }
    return returnScore;
  }
  void PinballGame::setPlayerScore(int playerNumber, unsigned long playerScore)
  {
    
    if(_gameActive == true)
    {
      this->_ballSave = false;
      this->_dropsReset = false;

      switch (playerNumber)
      {
      case 1:
          {
            this->_player1score = playerScore;
            
            break;  
          }
      case 2:
          {
            this->_player2score = playerScore;
            break;   
          }
      case 3:
          {
            this->_player3score = playerScore;
            break;   
          }
      case 4:
          {
            this->_player4score = playerScore;
            break;  
          }
      }
      this->DMDBottomLine = "Score: " + String(playerScore);
      this->DMDTopLine = "P" + String(playerNumber) + " Ball " + String(getCurrentBallNumber(playerNumber));
    }
    
  }
  void PinballGame::resetAllPlayerData()
  {
    this->_player1score = 0;
    this->_player2score = 0;
    this->_player3score = 0;
    this->_player4score = 0;
    this->_player1ExtraBalls = 0;
    this->_player2ExtraBalls = 0;
    this->_player3ExtraBalls = 0;
    this->_player4ExtraBalls = 0;
    this->_player1CurrentBall = 0;
    this->_player2CurrentBall = 0;
    this->_player3CurrentBall = 0;
    this->_player4CurrentBall = 0; 
    this->_ballSave = false;
    this->_playerCount = 0; 
    this->_currentPlayer = 1;
  }
  int PinballGame::getCurrentPlayerNumber()
  {
    return this->_currentPlayer;
  }
  int PinballGame::getCurrentPlayerNumbers()
  {
    return this->_playerCount;
  }
  int PinballGame::getPlayfieldMultiplier()
  {
    return this->_playfieldMultiplier;
  }
  void PinballGame::setPlayfieldMultiplier(int multiplier)
  {
    this->_playfieldMultiplier = multiplier;
  }
  int PinballGame::getBonusMultiplier()
  {
    return this->_bonusMultiplier;
  }
  void PinballGame::setBonusMultiplier(int multiplier)
  {
    this->_bonusMultiplier = multiplier;
  }
  String PinballGame::getDMDTopLine()
  {
    return this->DMDTopLine;
  }
  String PinballGame::getDMDBottomLine()
  {
    return this->DMDBottomLine;
  }

  void PinballGame::setDMDTopLine(String DMDText)
  {
    this->DMDTopLine = DMDText;
  }
  void PinballGame::setDMDBottomLine(String DMDText)
  {
    this->DMDBottomLine = DMDText;
  }

  void PinballGame::setDMDText(String DMDTopLine, String DMDBottomLine)
  {
    this->DMDTopLine = DMDTopLine;
    this->DMDBottomLine = DMDBottomLine;
  }

  int PinballGame::checkDropReset()
  {
    return this->_dropsReset;
  }

void PinballGame::setDropStatus(bool status)
  {
    this->_dropsReset = status;

  }

  void PinballGame::setPlayerSwitchScore(char switchNumber, int score, int playerNumber) //if playerNumber is 0 then set base score
  {
    switch(playerNumber)
    {
      case 0:
      {
        this->_switchScoreArray[switchNumber] = score;
        break;
      }
      case 1:
      {
        this->_switchScoreArray_p1[switchNumber] = score;
        break;
      }
      case 2:
      {
        this->_switchScoreArray_p2[switchNumber] = score;
        break;
      }
      case 3:
      {
        this->_switchScoreArray_p3[switchNumber] = score;
        break;
      }
      case 4:
      {
        this->_switchScoreArray_p4[switchNumber] = score;
        break;
      }
    }
  }
  int PinballGame::getPlayerSwitchScore(char switchNumber, int playerNumber) //if playerNumber is 0 then get base score
  {
    switch(playerNumber)
    {
      case 0:
      {
        return this->_switchScoreArray[switchNumber];
      }
      case 1:
      {
        return this->_switchScoreArray_p1[switchNumber];
      }
      case 2:
      {
        return this->_switchScoreArray_p2[switchNumber];
      }
      case 3:
      {
        return this->_switchScoreArray_p3[switchNumber];
      }
      case 4:
      {
        return this->_switchScoreArray_p4[switchNumber];
      }
    }
    return 0;
  } 

  void PinballGame::resetPlayerSwitchScores(int playerNumber) 
  {
    for ( byte col = 0; col < 8 ; col++) {
      for (byte row = 0; row < 8; row++) 
      {    
        int switchNumber = (col * 8)+row;
        this->setPlayerSwitchScore(switchNumber,this->getPlayerSwitchScore(switchNumber,0),playerNumber);
      }
    
    }
  }

