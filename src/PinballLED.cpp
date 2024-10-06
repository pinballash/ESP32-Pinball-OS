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
  
  return int(this->_red);
}

int PinballLED::getGreen()
{
  
  return int(this->_green);
}

int PinballLED::getBlue()
{
  
  return int(this->_blue);
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
 if((this->_flashSpeed > 0) && (this->_enabled == true))
 {
    unsigned long blinkInterval = (1000000/2)/this->_flashSpeed;
    if(micros() - this->_lastBlink >= blinkInterval) //we must not let this loop run away with itself, rate limiter here
    {
      this->_isOn = !this->_isOn;
      this->_needsUpdate = true;
      this->_lastBlink = micros();
      if((this->_flashOnce == true) && (this->_isOn == false))
      {
        this->disable();
      }

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

void PinballLED::flashOnce(int flashTime)
{
  this->_flashSpeed = flashTime;
  this->_enabled = true;
  this->_flashOnce = true;
}





 
