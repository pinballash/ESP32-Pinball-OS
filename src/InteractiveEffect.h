#include <Arduino.h>
TaskHandle_t DoubleTriggerTask;
TaskHandle_t TripleTriggerTask;
TaskHandle_t Tune1TriggerTask;

void DoubleTriggerFunction(void * pvParameters);
void TripleTriggerFunction(void * pvParameters);
void Tune1TriggerFunction(void * pvParameters);


//setup a task handler;


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




