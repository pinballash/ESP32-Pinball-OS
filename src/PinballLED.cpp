#include "PinballLED.h"
#include <Arduino.h>



PinballLED::PinballLED(int ID)
{
  this->_ID = ID;
  this->_LEDName = "Unconfigured";
  this->_isOn = false;
  
}

String PinballLED::getName()
{
  return this->_LEDName;
}
void PinballLED::setValues(String ledName, String colour, bool isOn)
{
  this->_LEDName = ledName;
  this->_colour = colour;
  this->_isOn = isOn;
}


 
