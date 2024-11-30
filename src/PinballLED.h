#ifndef PinballLED_H
#define PinballLED_H
#include <Arduino.h>

class PinballLED
{
	private:
		int _ID; 
        String _colour = "000000";
        String _LEDName = "Name not set";
        bool _enabled = false;
        bool _isOn = true;
        int _flashSpeed = 0;
        byte _red;
        byte _green;
        byte _blue;
        bool _needsUpdate = false;
        unsigned long _lastBlink = 0;
        bool _flashOnce = false;
  public:
   


  //constructor
 
  PinballLED(int ID);
  
  //Public Functions 
  void setValues(String ledName, String colour, bool isOn, int flashSpeed);
  void changeColour(String colour);
  void updateRGB();
  String getName();
  String getColour();
  String getColourHex();
  int getRed();
  int getGreen();
  int getBlue();
  void updateLed();
  bool getUpdate();
  void setUpdate();
  bool isOn();
  void turnOn();
  void turnOff();
  void tick();
  void enable();
  void disable();
  void flashOnce(int flashTime);
  void setFlashSpeed(int speed);
  
  
};
#endif
