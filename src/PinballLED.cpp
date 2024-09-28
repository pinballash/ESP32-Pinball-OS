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
  this->_isOn = isOn;
  this->_flashSpeed = flashSpeed;
  updateRGB();
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




 
