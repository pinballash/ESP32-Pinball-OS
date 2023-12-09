#include "PinballSwitch.h"
#include <Arduino.h>



PinballSwitch::PinballSwitch(int ID)
{
  this->_ID = ID;
  this->_switchName = "Unconfigured";
  this->_debounce = 1000;
  this->_isFlipper = false;
  this->_debug = false;
  
}

String PinballSwitch::getName()
{
  return _switchName;
}
void PinballSwitch::setValues(String switchName, int debounce, bool isFlipper, bool debug)
{
  this->_switchName = switchName;
  this->_debounce = debounce;
  this->_isFlipper = isFlipper;
  this->_debug = debug;
  
}

//to fire the switch run mySwitchName.triggerSwitch(), this will return true or false depending on whether it was ok or not
bool PinballSwitch::triggerSwitch()
{
  if((millis() - this->_lastMillis > this->_debounce) || this->_isFlipper)
  {
  	this->_isOn = true;
  	this->_lastMillis = millis();
    if(this->_debug == true)
    {
      Serial.print("[CLASS]PinballSwitch: [FUNCTION]triggerSwitch() - Name:");
      Serial.print(this->getName());
      Serial.println(" - Success");
    }
  	return true;
  }else
  {
	  if(this->_debug  == true)
    {
      Serial.print("[CLASS]PinballSwitch: [FUNCTION]triggerSwitch() - Name:");
      Serial.print(this->getName());
      Serial.println(" - Suppressed");
    }
	  return false;        
  }
}

bool PinballSwitch::isFlipper()
{
  return this->_isFlipper;
}

void PinballSwitch::toggleDebug()
{
  this->_debug = !this->_debug;
}
 
