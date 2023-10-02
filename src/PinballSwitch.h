#ifndef PINBALLSWITCH_H
#define PINBALLSWITCH_H
#include <Arduino.h>

class PinballSwitch
{
	private:
		int _debounce = 1000; //default to 1000 ms
		bool _isOn = false;
		unsigned long _lastMillis;
    String _switchName = "Name not set";
    bool _debug = true;
    bool _isFlipper = false;
  
  public:
   


  //constructor
  PinballSwitch(String switchName, int debounce, bool isFlipper, bool debug);
  
  //Public Functions
  String getName();
  bool triggerSwitch();
  bool isFlipper();
  void toggleDebug();
};
#endif
