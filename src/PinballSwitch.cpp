#include "PinballSwitch.h"
#include <Arduino.h>



PinballSwitch::PinballSwitch(int ID)
{
  this->_ID = ID;
  this->_switchName = "Unconfigured";
  this->_debounce = 1000;
  this->_debug = false;
  
}

String PinballSwitch::getName()
{
  return _switchName;
}
void PinballSwitch::setValues(String switchName, int debounce, bool isFlipper, bool isStart, bool isCredit, bool isOuthole, bool debug)
{
  this->_switchName = switchName;
  this->_debounce = debounce;
  this->_isFlipper = isFlipper;
  this->_isStart = isStart;
  this->_isCredit = isCredit;
  this->_isOuthole = isOuthole;
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
      Serial.print("[CLASS] PinballSwitch: [triggerSwitch] - ");
      Serial.print(this->getName());
      Serial.println(" - Success");
    }
  	return true;
  }else
  {
	  if(this->_debug  == true)
    {
      Serial.print("[CLASS] PinballSwitch: [triggerSwitch] - ");
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

bool PinballSwitch::isStart()
{
  return this->_isStart;
}

bool PinballSwitch::isCredit()
{
  return this->_isCredit;
}

bool PinballSwitch::isOuthole()
{
  return this->_isOuthole;
}


void PinballSwitch::toggleDebug()
{
  this->_debug = !this->_debug;
}
 
