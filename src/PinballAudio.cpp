#include "PinballAudio.h"


PinballAudio::PinballAudio(int ID)
{
  this->_ID = ID;

}
/*PinballCoil::PinballCoil(String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff)
{
  this->_coilName = coilName;
  this->_shiftRegister = shiftRegister;
  this->_shiftRegisterBit = shiftRegisterBit;
  this->_pulseTime = pulseTime;
  this->_pulseBackOff = pulseBackOff;
}*/

void PinballAudio::setValues(String audioName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff)
{
  this->_audioName = audioName;
  this->_shiftRegister = shiftRegister;
  this->_shiftRegisterBit = shiftRegisterBit;
  this->_pulseTime = pulseTime;
  this->_pulseBackOff = pulseBackOff;
  //extern String tso_PinballAudio;
  //tso_PinballAudio = tso_PinballAudio + "[CLASS] PinballAudio: [setValues] Audio " + this->_audioName + " SRb = " + String(this->_shiftRegisterBit);
}

//Public Functions

bool PinballAudio::fireAudio()
{
  //replaces Alan's doFireSolenoid
  //in that implementation we would fire a solenoid, wait for the selay time and then turn it off.  In this implementation we will leave the on off decisions to the main loop
  //so how do we want to handle this - present thinking is we dont fire again if already firing, this could lead to perminant coil lock on.
  if(millis() - this->_lastMillis > (this->_pulseTime + this->_pulseBackOff))
  {
    if(this->_debug  == true)
    {
        extern String tso_PinballAudio;
        tso_PinballAudio = tso_PinballAudio + "[CLASS] PinballAudio: [fireAudio] Audio " + this->_audioName + " SRb = " + String(this->_shiftRegisterBit);

    }
    this->_isOn = true;
    this->_lastMillis = millis();
    return true;
  }else
  {
    return false;        
  }
}

void PinballAudio::releaseAudio()
{
  //code to turn coil off
  if(this->_debug  == true)
  {
    

    //String DebugLog = this->_debugLog;
    extern String tso_PinballAudio;
    tso_PinballAudio = tso_PinballAudio + "[CLASS] PinballAudio: [fireAudio] Audio " + this->_audioName + " SRb = " + String(this->_shiftRegisterBit);


  }
  this->_isOn = false;
}

bool PinballAudio::checkStatus()
{
  return this->_isOn;
}

String PinballAudio::getName()
{
  return _audioName;
}

byte PinballAudio::getSR()
{
  return _shiftRegister;
}
byte PinballAudio::getSRBit()
{
  return _shiftRegisterBit;
}

void PinballAudio::enable()
{
  this->_enable = true;
  if(this->_isOn == false)
  {
    this->_isOn = true;
    this->fireAudio();
    if(this->_debug  == true)
    {

      //String DebugLog = this->_debugLog;  
      //DebugLog = DebugLog + "[CLASS] PinballCoil: [enable] Coil " + this->_coilName; 
      //this->_debugLog = DebugLog;

    }
    //turn on coil indefinitely
  }else{
    if(this->_debug  == true)
    {

      //String DebugLog = this->_debugLog; 
      //DebugLog = DebugLog + "[CLASS] PinballCoil: [enable] Coil " + this->_coilName + " failed, already marked as on";
      //this->_debugLog = DebugLog;
   
    }
  }
}

void PinballAudio::disable()
{
    this->_enable = false;
    this->manage();
    if(this->_debug  == true)
    {

      //String DebugLog = this->_debugLog;
      //DebugLog = DebugLog + "[CLASS] PinballCoil: [disable] " + this->_coilName;
      //this->_debugLog = DebugLog;

    }
}

void PinballAudio::manage()
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

          //String DebugLog = this->_debugLog;
          //DebugLog = DebugLog + "[CLASS] PinballCoil: [manage] turn off - " + this->_coilName;
          //this->_debugLog = DebugLog;

        }
        this->releaseAudio();
      }else
      {
        //Serial.print("[CLASS] PinballCoil: [FUNCTION] manage : I'm on and within pulse time - stay on - ");  
        //Serial.println(this->_coilName); 
      }
    }
  }

}




 
void PinballAudio::toggleDebug()
{
  this->_debug = !this->_debug;
}

  String PinballAudio::getDebugLog()
  {
    String DebugLog = this->_debugLog;
    clearDebugLog();
    return DebugLog;
  }
  void PinballAudio::clearDebugLog()
  {
    this->_debugLog = "";
  }