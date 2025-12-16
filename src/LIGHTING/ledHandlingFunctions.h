#include <Arduino.h>

void ProcessLedsFunction( void * pvParameters)
{
  Serial.print("ProcessLedsFunction running on core ");
  Serial.println(xPortGetCoreID());
  unsigned long lastMillisSw = 0;
  unsigned long lastMicrosLoopRan = 0;
  unsigned long scanMicro = 0;
  unsigned long flipperMicro = 0;
  unsigned long triggerSwitchMicro = 0;
  unsigned long manageCoilMicro = 0;
  unsigned long processSwitchMicro = 0;
  unsigned long measureMicro = 0;
  for(;;)
  {
    if((micros() - lastMicrosLoopRan >= UpdateLedsEveryMicroSeconds)) //&& (runningLeds==false))//we must not let this loop run away with itself, rate limiter here
    {
      runningLeds = true;
      //do processing
      measureMicro = micros();
      processAllLeds(); //exists with the LOGIC\gameRules-[gamename].h
      processSwitchMicro = processSwitchMicro + (micros() - measureMicro);
      lastMicrosLoopRan = micros();
    }else{
      //release the CPU for processing other tasks
      vTaskDelay(pdMS_TO_TICKS(10)); //yeild
    }  
  }
}

