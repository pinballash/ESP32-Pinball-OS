#ifndef PINBALLGAME_H
#define PINBALLGAME_H
#include <Arduino.h>


class PinballGame
{
  private:
    bool _dropsReset = true;
    bool _gameActive = false;
    bool _ballSave = false;
    int _maxBalls = 3;
    int _playfieldMultiplier =1;
    int _bonusMultiplier = 1;
    int _lastSwitchTriggered = -1;
    unsigned long _lastSwitchTriggeredTimer = 0;

    int _playerCount = 0;
    String _gameName = "not set";
    int _currentPlayer = 0;
    
    int _player1CurrentBall = 0;
    int _player1ExtraBalls = 0;
    unsigned long _player1score = 0;

    int _player2CurrentBall = 0;
    int _player2ExtraBalls = 0;
    unsigned long _player2score = 0;

    int _player3CurrentBall = 0;
    int _player3ExtraBalls = 0;
    unsigned long _player3score = 0;

    int _player4CurrentBall = 0;
    int _player4ExtraBalls = 0;
    unsigned long _player4score = 0;

    int _switchScoreArray[1408] = {
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000
    };

    int _switchScoreArray_p1[1408] = {
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000
    };

    int _switchScoreArray_p2[1408] = {
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000
    };

    int _switchScoreArray_p3[1408] = {
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000
    };
    
    int _switchScoreArray_p4[1408] = {
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,
      1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000
    };
    
    String DMDTopLine = "";
    String DMDBottomLine = "";

    String _scoreDisplay1 ="0000000";
    String _scoreDisplay2 ="0000000";
    String _scoreDisplay3 ="0000000";
    String _scoreDisplay4 ="0000000";

    String _playerDisplay ="00";
    String _ballDisplay ="00";

    /*
    Variables from AlanJ - these used to exist in params.h in a gameParams Struct
    int ballsPerGame;
    bool playAttractMusic;
    int attractMusicNo;
    unsigned long HSTD[10];
    String HSTDName[10];
    bool extraBallsAllowed;
    int extraBallSetting; //0=easy,1=medium,2=hard*/
  
  public:
    unsigned long HSTD[10];
    String HSTDName[10];


   
  //constructor
  PinballGame(String GameName);
  
  //Public Functions
  void newGame();
  void endGame();
  void addPlayer();
  void endOfBall(int playerNumber);
  bool isGameActive();
  bool isBallSave();
  int getMaxBalls();
  void setMaxBalls(int maxBalls);
  int getCurrentBallNumber(int playerNumber);
  unsigned long getPlayerScore(int playerNumber);
  void setPlayerScore(int playerNumber, unsigned long playerScore);
  String getName();
  int getCurrentPlayerNumber();
  int getCurrentPlayerNumbers();
  void resetAllPlayerData();
  int getPlayfieldMultiplier();
  void setPlayfieldMultiplier(int multiplier);
  int getBonusMultiplier();
  void setBonusMultiplier(int multiplier);
  String getDMDTopLine();
  String getDMDBottomLine();

  String getScoreDisplay(int displayId);
  String getPlayerDisplay();  
  String getBallDisplay();  

  void setScoreDisplay(int displayId, String DMDText);
  void setPlayerDisplay(String DMDText);  
  void setBallDisplay(String DMDText); 

  void setDMDTopLine(String DMDText);
  void setDMDBottomLine(String DMDText);
  void setDMDText(String DMDTopLine, String DMDBottomLine);
  bool checkDropReset();
  void setDropStatus(bool status);
  void setPlayerSwitchScore(char switchNumber, int score, int playerNumber); //if playerNumber is 0 then set base score
  int getPlayerSwitchScore(char switchNumber, int playerNumber); //if playerNumber is 0 then get base score
  void resetPlayerSwitchScores(int playerNumber);
  void setLastSwitchTriggered(int switchId, unsigned long timer);
  int lastSwitchTriggered();
  unsigned long lastSwitchTriggeredTime();
};
#endif