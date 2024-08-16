#include <Arduino.h>
TaskHandle_t DoubleTriggerTask;
TaskHandle_t TripleTriggerTask;

void DoubleTriggerFunction(void * pvParameters);
void TripleTriggerFunction(void * pvParameters);

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
      write_sr_audio(); //update shift register
      vTaskDelay(750);
      ResetAudioShifts();
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
      write_sr_audio(); //update shift register
      vTaskDelay(750);
      ResetAudioShifts();
      vTaskDelay(5);
  }
         
  vTaskDelete(NULL);
}



