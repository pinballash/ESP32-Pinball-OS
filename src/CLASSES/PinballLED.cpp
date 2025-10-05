#include "CLASSES/PinballLED.h"
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

void PinballLED::setValues(String ledName, String colour, bool isOn, int flashSpeed)
{
  this->_LEDName = ledName;
  this->_colour = colour;
  if(isOn == true)
  {
    this->enable();
  }else{
    this->disable();
  }
  this->_flashSpeed = flashSpeed;
  updateRGB();
  this->_needsUpdate = true;
}

void PinballLED::changeColour(String colour)
{
  this->_colour = colour;
  updateRGB();
  resetCalculatedRGB();
}

void PinballLED::updateRGB()
{
    String value;
    value=getColourHex();

    char charbuf[8];
    value.toCharArray(charbuf,8);
    long int rgb=strtol(charbuf,0,16);
    this->_red=(byte)(rgb>>16);
    this->_green=(byte)(rgb>>8);
    this->_blue=(byte)(rgb);
}

void PinballLED::resetCalculatedRGB()
{
    this->_calaculatedRed = this->_red;
    this->_calaculatedBlue = this->_blue;
    this->_calaculatedGreen = this->_green;
}

String PinballLED::getColour()
{
  return this->_colour;
}

String PinballLED::getColourHex()
{
  String Hex = this->_colour;
  Hex.remove(0,1);
  return Hex;
}

int PinballLED::getRed()
{
  
  return int(this->_calaculatedRed);
}

int PinballLED::getGreen()
{
  
  return int(this->_calaculatedGreen);
}

int PinballLED::getBlue()
{
  
  return int(this->_calaculatedBlue);
}
  
void PinballLED::updateLed()
{
  this->_needsUpdate = true;
}

bool PinballLED::getUpdate()
{
  return this->_needsUpdate;
}

void PinballLED::setUpdate()
{
  this->_needsUpdate = false;
}

bool PinballLED::isOn()
{
  return this->_isOn;
}

bool PinballLED::isEnabled()
{
  return this->_enabled;
}

void PinballLED::turnOn()
{
  this->_isOn = true;
}

void PinballLED::turnOff()
{
  this->_isOn = false;
}

void PinballLED::tick()
{
  unsigned ledPeriod = (1000000*this->_flashPeriodLength)/this->_flashSpeed;
  unsigned long halfLife = ledPeriod/2;  //blink interval is half flashPeriod length in miliseconds divided by flashSpeed
 if((this->_flashSpeed > 0) && (this->_enabled == true))
 {

    //so here we need to think about the whole period.  We need to be on for half the period and off for half the period
    unsigned long timerMicros = micros();
    if((timerMicros - this->_lastBlink >= halfLife) && (this->isEnabled() == true))
    {
      
      if(this->_isOn == true) //so we have be on for the half life
      {
        //turn off
        this->_isOn = false;
        this->resetCalculatedRGB();
        //Serial.println("[LED]"+this->_LEDName+",off,"+timerMicros+","+(timerMicros - this->_lastBlink)+","+halfLife);
        this->updateLed();
      }else{ //so we have be off for the half life
        
        if(this->_flashOnce == true)
        {
          this->_enabled = false;
          this->resetCalculatedRGB();
          this->_needsUpdate == true;
        }else
        {
          this->_isOn = true;
          this->_needsUpdate == true;
        }
      }
      this->_lastBlink = micros();
    }
 }
}

void PinballLED::enable()
{
  this->_isOn = true;
  this->_enabled = true;
}

void PinballLED::disable()
{
  this->_isOn = false;
  this->_enabled = false;
}

bool PinballLED::flashOnce(int flashTime)
{
  this->_lastBlink = micros();
  this->_flashSpeed = flashTime;
  this->_flashOnce = true;
  this->_enabled = true;
  this->_isOn = true;
  this->resetCalculatedRGB();
  this->_needsUpdate = true;
  return true;
}

void PinballLED::setFlashSpeed(int speed)
{
  this->_flashSpeed = speed;
}

void PinballLED::fadeOut()
{
  this->_fadeOut = true;
}

void PinballLED::dimLed()
{
  //half the led colour value
  this->_calaculatedRed = this->_calaculatedRed >> 2;
  this->_calaculatedGreen = this->_calaculatedGreen >> 2;
  this->_calaculatedBlue = this->_calaculatedBlue >> 2;
}