#ifndef PinballLED_H
#define PinballLED_H
#include <Arduino.h>

class PinballLED
{
	private:
		int _ID; 
        String _colour = "000000";
        String _LEDName = "Name not set";
        bool _isOn = false;

  public:
   


  //constructor
 
  PinballLED(int ID);
  
  //Public Functions 
  void setValues(String ledName, String colour, bool isOn);
  String getName();
  
};
#endif
