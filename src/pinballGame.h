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
    
    String DMDTopLine = "";
    String DMDBottomLine = "";

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
  void setDMDTopLine(String DMDText);
  void setDMDBottomLine(String DMDText);
  void setDMDText(String DMDTopLine, String DMDBottomLine);
  int checkDropReset();
  void setDropStatus(bool status);
};
#endif