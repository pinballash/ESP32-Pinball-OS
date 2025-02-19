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
        int _flashSpeed = 0; //flashes per period
        int _flashPeriodLength = 2; //in seconds
        bool _blinkOn = true;
        byte _red;
        byte _green;
        byte _blue;
        bool _needsUpdate = false;
        unsigned long _lastBlink = 0;
        bool _flashOnce = false;
        bool _fadeOut = true;
        int _fadeLevel = 0;
        byte _calaculatedRed;
        byte _calaculatedBlue;
        byte _calaculatedGreen;

  public:
   


  //constructor
 
  PinballLED(int ID);
  
  //Public Functions 
  void setValues(String ledName, String colour, bool isOn, int flashSpeed);
  void changeColour(String colour);
  void updateRGB();
  void resetCalculatedRGB();
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
  bool isEnabled();
  void turnOn();
  void turnOff();
  void tick();
  void enable();
  void disable();
  bool flashOnce(int flashTime);
  void setFlashSpeed(int speed);
  void fadeOut();
  void dimLed();
  
};
#endif
