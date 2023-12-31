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
    this->_playerCount = 1;
    this->_currentPlayer = 1;
    this->_ballSave = true;
    this->_gameActive = true;
    this->_player1CurrentBall = this->_player1CurrentBall +1; 
    //this->resetAllPlayerData();
  }
  void PinballGame::endGame()
  {
     this->_gameActive = false;
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
              break;
            }
        case 3:
            {
              this->_player3CurrentBall = this->_player3CurrentBall +1;
              break;
            }
        case 4:
            {
              this->_player4CurrentBall = this->_player4CurrentBall +1;
              break;
            }
        
        }
    }
    

  }
  void PinballGame::endOfBall(int playerNumber)
  {
    
    //are there any other players?
    Serial.println("[PinballGame] End of ball");
    
    int ballCounter = 0;
    switch (playerNumber)
    {
    case 1:
        {
          Serial.println("[PinballGame] End of ball : Player1 add a ball");
          this->_player1CurrentBall = this->_player1CurrentBall +1;
          ballCounter = this->_player1CurrentBall;
          break;
        }
    case 2:
        {
          Serial.println("[PinballGame] End of ball : Player2 add a ball");
          this->_player2CurrentBall = this->_player2CurrentBall +1; 
          ballCounter = this->_player2CurrentBall; 
          break;
        }
    case 3:
        {
          Serial.println("[PinballGame] End of ball : Player3 add a ball");
          this->_player3CurrentBall = this->_player3CurrentBall +1; 
          ballCounter = this->_player3CurrentBall;  
          break;
        }
    case 4:
        {
          Serial.println("[PinballGame] End of ball : Player4 add a ball");
          this->_player4CurrentBall = this->_player4CurrentBall +1; 
          ballCounter = this->_player4CurrentBall;
          break;
        }
    }
    Serial.print("[PinballGame] End of ball : ballCounter=");
    Serial.println(ballCounter);
    if(playerNumber < this->_playerCount)
    {
      Serial.println("[PinballGame] End of ball : There are more players than current");
      playerNumber +=1;
      
    }else{
      Serial.println("[PinballGame] End of ball : Set to Player1");
      playerNumber=1;
      
    }
    if((playerNumber == 1) && (this->_player1CurrentBall > this->_maxBalls))
    {
      Serial.println("[PinballGame] End of ball : Out of balls");
      //game over - game over code needs to run, sould, lights, diaplay, but thats beyond the scope of this class - we can check for game over elsewhere.
      this->_gameActive = false;
    }
    else
    {
      Serial.println("[PinballGame] End of ball : Ball save set to ON, next ball");
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
    
    this->_ballSave = false;

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
    this->_currentPlayer = 0;
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