#ifndef PINBALLAUDIO_H
#define PINBALLAUDIO_H
#include <Arduino.h>


class PinballAudio
{
  private:
    int _ID;
    bool _enable = false; //can we turn the audio on perminantly
    bool _isOn = false;
    int _pulseTime = 200; //default pulse time 200ms
    int _pulseBackOff = 100; //default amount of time to back off before initiating again
    byte _shiftRegister; // which shift register 0 or 1
    byte _shiftRegisterBit; // which bit in the shift register 0-7
    unsigned long _lastMillis; //when last inititiated
    String _audioName = "No name set";

    bool _debug = true;
    String _debugLog = "";
    //in future we may wish to add pulse modulation after initial pulse time, lets leave for now.
  
  public:
  //set up ShiftRegisterItem


   
  //constructor
  PinballAudio(int ID);
  //PinballCoil(String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff); //String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff
  
  //Public Functions
  void init();
  void setValues(String audioName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff);
  String getName();

  bool fireAudio();
  void releaseAudio();

  bool checkStatus();

  void enable();
  void disable();
  void manage();
  byte getSR();
  byte getSRBit();

  void toggleDebug();
  String getDebugLog();
  void clearDebugLog();

};
#endif
