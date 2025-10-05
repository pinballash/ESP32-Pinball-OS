#ifndef PINBALLCOIL_H
#define PINBALLCOIL_H
#include <Arduino.h>


class PinballCoil
{
  private:
    int _ID;
    bool _enable = false; //can we turn the solenoid on perminantly - flippers and locks
    bool _isOn = false;
    int _pulseTime = 200; //default pulse time 200ms
    int _pulseBackOff = 100; //default amount of time to back off before energising again - to prevent lock ons.
    byte _shiftRegister; // which shift register 0 or 1
    byte _shiftRegisterBit; // which bit in the shift register 0-7
    unsigned long _lastMillis; //when last energised
    String _coilName = "No name set";
    bool _needsAction = false;
    bool _debug = false;
    String _debugLog = "";
    //in future we may wish to add pulse modulation after initial pulse time, lets leave for now.
  
  public:
  //set up ShiftRegisterItem
    SemaphoreHandle_t i2cSemaphoreCOIL;

   
  //constructor
  PinballCoil(int ID);
  
  //Public Functions
  void init();
  void setValues(String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff);
  String getName();
  void setPulseTime(int pulseTime);
  bool fireCoil();
  void releaseCoil();
  void updateStatus();
  bool checkStatus();
  bool needsAction();
  void enable();
  void disable();
  void manage();
  byte getSR();
  byte getSRBit();
  void actioned();
  void toggleDebug();
  String getDebugLog();
  void clearDebugLog();

};
#endif
