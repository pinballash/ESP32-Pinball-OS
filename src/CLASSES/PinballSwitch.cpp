#include "CLASSES\PinballSwitch.h"
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
void PinballSwitch::setValues(String switchName, int debounce, bool isFlipper, bool isStart, bool isCredit, bool isOuthole, bool debug, bool autoOn)
{
  this->_switchName = switchName;
  this->_debounce = debounce;
  this->_isFlipper = isFlipper;
  this->_isStart = isStart;
  this->_isCredit = isCredit;
  this->_isOuthole = isOuthole;
  this->_debug = debug;
  this->_autoOn = autoOn;

}

//to fire the switch run mySwitchName.triggerSwitch(), this will return true or false depending on whether it was ok or not
bool PinballSwitch::triggerSwitch()
{
  //need a function to check if its ok to trigger the switch again.  For example, a drop traget will trigger over and over
  //again so we may need to use this->_autoOn - if default as true, switch operates normally, but if is set to false, then we will supress further switch triggers until this->_isOn = false
  if(this->_debug == true)
  {
    extern String tso_PinballSwitch;
    tso_PinballSwitch = tso_PinballSwitch + "[CLASS] PinballSwitch: [triggerSwitch] Switch " + this->getName() + "Fired";

  }
  bool proceed = false;
  if(this->_autoOn == true)
  {
    proceed = true; 
  }else if((this->_isOn == false) && (this->_fired == false))
  {
    proceed = true;
  }
  if(proceed == true)
  {
    if((millis() - this->_lastMillis > this->_debounce) || this->_isFlipper)
    {
      this->_isOn = true; 
      this->_fired = true;
      this->_lastMillis = millis();
      //switch triggered
      return true;
    }else
    {
      //switch supressed
      return false;        
    }
  }
  else
  {
	  //switch supressed
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

void PinballSwitch::turnOff()
{
  this->_isOn = false;
}

int PinballSwitch::getSwitchScore()
{ 
  return this->_pointsScore;
}

void PinballSwitch::setSwitchScore(int pointsScore)
{
  
  this->_pointsScore = pointsScore;
  //extern String tso_PinballSwitch;
  //tso_PinballSwitch = tso_PinballSwitch + "[CLASS] PinballSwitch: [setSwitchScore] Switch " + this->getName() + " " + String(pointsScore);
}

void PinballSwitch::reEnable()
{
  this->_isOn = false;
  this->_fired = false;
}

bool PinballSwitch::isOn()
{ 
  
  return this->_isOn;
}
bool PinballSwitch::hasFired()
{ 
  
  return this->_fired;
}
 
