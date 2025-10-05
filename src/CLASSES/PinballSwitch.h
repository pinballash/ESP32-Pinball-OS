#ifndef PINBALLSWITCH_H
#define PINBALLSWITCH_H
#include <Arduino.h>

class PinballSwitch
{
	private:
		int _ID; 
    int _debounce = 1000; //default to 1000 ms
		bool _isOn = false;
		unsigned long _lastMillis;
    String _switchName = "Name not set";
    bool _debug = true;
    bool _isFlipper = false;
    bool _isStart = false;
    bool _isCredit = false;
    bool _isOuthole = false;  
    bool _autoOn = false;
    int _pointsScore = 0;
    bool _fired = false;

  public:
  //constructor
  PinballSwitch(int ID);
  
  //Public Functions 
  void setValues(String switchName, int debounce, bool isFlipper, bool isStart, bool isCredit, bool isOuthole, bool debug, bool autoOn);
  String getName();
  bool triggerSwitch();
  bool isFlipper();
  bool isStart();
  bool isCredit();
  bool isOuthole();
  void toggleDebug();
  void turnOff();
  int getSwitchScore();
  void setSwitchScore(int pointsScore);
  void reEnable();
  bool isOn();
  bool hasFired();
  int getDebounce();
};
#endif
