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
      if (this->_fadeOut == true)
      {
        /* here we fade out */
        if(this->_fadeLevel < 3)
        {
          this->_fadeLevel++;
          dimLed();
          this->_needsUpdate = true;
        }
      }
      if((this->_fadeOut == false) || (this->_fadeLevel == 3))
      {
        this->_isOn = !this->_isOn;
        this->_needsUpdate = true;
        this->_lastBlink = micros();
        resetCalculatedRGB();
        this->_fadeLevel = 0;
        if((this->_flashOnce == true) && (this->_isOn == false))
        {
          this->disable();
          this->_needsUpdate = true;
        }
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




 
