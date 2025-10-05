#include "CLASSES/PinballCoil.h"


PinballCoil::PinballCoil(int ID)
{
  this->_ID = ID;
}

void PinballCoil::setValues(String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff)
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
  //so how do we want to handle this - present thinking is we dont fire again if already firing, this could lead to perminant coil lock on.
  if(millis() - this->_lastMillis > (this->_pulseTime + this->_pulseBackOff))
  {
    if(this->_debug  == true)
    {
        extern String tso_PinballCoil;
        tso_PinballCoil = tso_PinballCoil + "[CLASS] PinballCoil: [fireCoil] Coil " + this->_coilName;

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
    //nothing to see here
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
      //nothing to see here
    }
    //turn on coil indefinitely
  }else{
    if(this->_debug  == true)
    {
      //nothing to see here
    }
  }
}

void PinballCoil::disable()
{
    this->_enable = false;
    this->manage();
    if(this->_debug  == true)
    {
      //nothing to see here
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
          //nothing to see here
        }
        this->releaseCoil();
      }else
      {
        //nothing to see here
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

  String PinballCoil::getDebugLog()
  {
    String DebugLog = this->_debugLog;
    clearDebugLog();
    return DebugLog;
  }
  void PinballCoil::clearDebugLog()
  {
    this->_debugLog = "";
  }