#include <Arduino.h>
TaskHandle_t DoubleTriggerTask;
TaskHandle_t TripleTriggerTask;
TaskHandle_t Tune1TriggerTask;
TaskHandle_t Tune2TriggerTask;
TaskHandle_t Tune3TriggerTask;

void DoubleTriggerFunction(void * pvParameters);
void TripleTriggerFunction(void * pvParameters);
void Tune1TriggerFunction(void * pvParameters);
void Tune2TriggerFunction(void * pvParameters);
void Tune3TriggerFunction(void * pvParameters);


bool ChimeRing(char coilNum)
{
  if(chimesOn==true)
  {
    PinballCoil* ChimeCoil = coils[coilNum].coilObject;
  
    if(ChimeCoil->fireCoil()){
      coilActive[coilNum]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
      ProcessShifts(ChimeCoil); //action the turning on
      write_sr_coils(); //update shift register
      return true;
    }
  }

  return false;
}


void DoubleTrigger()
{
  
  xTaskCreatePinnedToCore(
    DoubleTriggerFunction,
    "DoubleTriggerFunction",
    2000,
    NULL,
    10,
    &DoubleTriggerTask,
    0);

}
void TripleTrigger()
{
  
  xTaskCreatePinnedToCore(
    TripleTriggerFunction,
    "TripleTriggerFunction",
    2000,
    NULL,
    10,
    &TripleTriggerTask,
    0);

}

void Tune1Trigger()
{
  
  xTaskCreatePinnedToCore(
    Tune1TriggerFunction,
    "Tune1TriggerFunction",
    2000,
    NULL,
    10,
    &Tune1TriggerTask,
    0);

}

void Tune2Trigger()
{
  
  xTaskCreatePinnedToCore(
    Tune2TriggerFunction,
    "Tune2TriggerFunction",
    2000,
    NULL,
    10,
    &Tune2TriggerTask,
    0);

}

void Tune3Trigger()
{
  
  xTaskCreatePinnedToCore(
    Tune3TriggerFunction,
    "Tune3TriggerFunction",
    2000,
    NULL,
    10,
    &Tune3TriggerTask,
    0);

}

void DoubleTriggerFunction(void * pvParameters)
{
  //do something
  //eg: set up timer
  //do loop 
  char LoopCount = 2;
  for(char i = 0;i < LoopCount; i++)
  {
      extern String tso_pinballAudio;
      Serial.println("[DoubleTriggerFunction] Run");
      outgoing2 = 254;
      //ProcessAudioShifts(audios[0].AudioObject); //set shift register bytes to turn on audio channel
      //write_sr_audio(); //update shift register
      vTaskDelay(750);
      //ResetAudioShifts();
      vTaskDelay(5);
  }
         
  vTaskDelete(NULL);
}

void TripleTriggerFunction(void * pvParameters)
{
  //do something
  //eg: set up timer
  //do loop 
  char LoopCount = 3;
  for(char i = 0;i < LoopCount; i++)
  {
      extern String tso_pinballAudio;
      Serial.println("[DoubleTriggerFunction] Run");
      outgoing2 = 254;
      //ProcessAudioShifts(audios[0].AudioObject); //set shift register bytes to turn on audio channel
      //write_sr_audio(); //update shift register
      vTaskDelay(750);
      //ResetAudioShifts();
      vTaskDelay(5);
  }
         
  vTaskDelete(NULL);
}

void Tune1TriggerFunction(void * pvParameters)
{
  //do something
  //eg: set up timer
  //do loop 
  char LoopCount = 2;
  for(char i = 0;i < LoopCount; i++)
  {
      //so basically a 120bpm song has two seconds per bar.  This means each beat is 0.5 seconds long
      
      ChimeRing(11);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125

      ChimeRing(12);

      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      
      ChimeRing(11);
      vTaskDelay(250); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      
      ChimeRing(14);
      vTaskDelay(500); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125

      ChimeRing(12);
      vTaskDelay(1000); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
  }
         
  vTaskDelete(NULL);
}

void Tune2TriggerFunction(void * pvParameters)
{
  //do something
  //eg: set up timer
  //do loop 
  char LoopCount = 1;
  for(char i = 0;i < LoopCount; i++)
  {
      //so basically a 120bpm song has two seconds per bar.  This means each beat is 0.5 seconds long
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(11);
      vTaskDelay(500); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125

      ChimeRing(11);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(11);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(11);
      vTaskDelay(500); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125

      ChimeRing(11);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(11);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(11);
      vTaskDelay(250); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125

      
      ChimeRing(12);
      vTaskDelay(250); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125


      ChimeRing(14);
      vTaskDelay(250); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125


      ChimeRing(12);
      vTaskDelay(250); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125

      ChimeRing(11);
      vTaskDelay(250); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
  }
         
  vTaskDelete(NULL);
}


void Tune3TriggerFunction(void * pvParameters)
{
  //do something
  //eg: set up timer
  //do loop 
  char LoopCount = 4;
  for(char i = 0;i < LoopCount; i++)
  {
      //so basically a 120bpm song has two seconds per bar.  This means each beat is 0.5 seconds long
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(11);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(12);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(14);
      vTaskDelay(125); //one bar 2000, two beats 1000, one beat 500, half beat 250, quarter beat 125
      ChimeRing(12);
      
  }
         
  vTaskDelete(NULL);
}



