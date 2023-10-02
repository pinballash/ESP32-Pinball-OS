#include "PinballCoil.h"



PinballCoil::PinballCoil(String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff)
{
  this->_coilName = coilName;
  this->_shiftRegister = shiftRegister;
  this->_shiftRegisterBit = shiftRegisterBit;
  this->_pulseTime = pulseTime;
  this->_pulseBackOff = pulseBackOff;
}

//Public Functions

bool PinballCoil::fireCoil()
{
  //replaces Alan's doFireSolenoid
  //in that implementation we would fire a solenoid, wait for the selay time and then turn it off.  In this implementation we will leave the on off decisions to the main loop
  //so how do we want to handle this - present thinking is we dont fire again if already firing, this could lead to perminant coil lock on.
  if(millis() - this->_lastMillis > (this->_pulseTime + this->_pulseBackOff))
  {
    if(this->_debug  == true)
    {
      Serial.print("[CLASS] PinballCoil: [FUNCTION] fireCoil ");
      Serial.println(this->_coilName);
    }
    this->_isOn = true;
    this->_lastMillis = millis();
    this->_needsAction = true;
    return true;
  }else
  {
    return false;        
  }
}

void PinballCoil::releaseCoil()
{
  //code to turn coil off
  if(this->_debug  == true)
  {
    Serial.print("[CLASS] PinballCoil: [FUNCTION] releaseCoil ");
    Serial.println(this->_coilName);
  }
  this->_needsAction = true;
  this->_isOn = false;
}

bool PinballCoil::checkStatus()
{
  return this->_isOn;
}

String PinballCoil::getName()
{
  return _coilName;
}

byte PinballCoil::getSR()
{
  return _shiftRegister;
}
byte PinballCoil::getSRBit()
{
  return _shiftRegisterBit;
}

void PinballCoil::enable()
{
  this->_enable = true;
  if(this->_isOn == false)
  {
    this->_isOn = true;
    this->fireCoil();
    if(this->_debug  == true)
    {
      Serial.print("[CLASS] PinballCoil: [FUNCTION] enable ");
      Serial.println(this->_coilName);
    }
    //turn on coil indefinitely
  }else{
    if(this->_debug  == true)
    {
      Serial.print("[CLASS] PinballCoil: [FUNCTION] enable ");
      Serial.print(this->_coilName);
      Serial.println(" failed, already marked as on");
    }
  }
}

void PinballCoil::disable()
{
    this->_enable = false;
    this->manage();
    if(this->_debug  == true)
    {
      Serial.print("[CLASS] PinballCoil: [FUNCTION] disable ");
      Serial.println(this->_coilName);
    }
}

void PinballCoil::manage()
{
  //am I energised
  //No, do nothing - yes, continue
  if(this->_isOn)
  {
    //am I enabled
    //if yes, do nothing - No continue
    if(this->_enable == false)
    {
      if(millis() - this->_lastMillis > (this->_pulseTime))
      {
        if(this->_debug  == true)
        {
          Serial.print("[CLASS] PinballCoil: [FUNCTION] manage : I'm on and outside pulse time - turn off - ");  
          Serial.println(this->_coilName);
        }
        this->releaseCoil();
      }else
      {
        //Serial.print("[CLASS] PinballCoil: [FUNCTION] manage : I'm on and within pulse time - stay on - ");  
        //Serial.println(this->_coilName); 
      }
    }
  }
  this->_needsAction = false;
}

bool PinballCoil::needsAction()
{
  return this->_needsAction;
}

void PinballCoil::actioned()
{
  this->_needsAction = false;
}
 
void PinballCoil::toggleDebug()
{
  this->_debug = !this->_debug;
}