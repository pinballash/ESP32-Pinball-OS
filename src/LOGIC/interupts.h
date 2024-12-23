#include <Arduino.h>

//Timer running to ensure the switch matrix is read, switches are triggered and coils are handled.  These are the MOST important things the CPU has to deal with.
hw_timer_t *Timer0_Cfg = NULL;
void IRAM_ATTR Timer0_ISR()
{
  if(scanInProgress == false)
  {
    scanInProgress = true;
    scanSwitchMatrix();
    triggerSwitches();
    manageCoils();
    //manageAudio();
    INTHz++;
    scanInProgress = false;
  }
  if (millis() - lastMillisSwINT > 1000 )
  {
    reportedSwitchMatrixHz = INTHz;
    INTHz = 0;
    lastMillisSwINT = millis();
  }
    
}