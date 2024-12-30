#include <Arduino.h>

/*
 * ProcessShifts is a function that updates the shift register byte variables based on the coil object sent
 */
void ProcessShifts(PinballCoil* CoilObject)
{
  if(CoilObject->getSR() == 0)
  {
    if(CoilObject->checkStatus())
    {
      if(osrDebug)
      {
        Serial.print("Turning on coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR3 - BIT:");
        Serial.println(CoilObject->getSRBit());
      } 
      bitSet(outgoing3,CoilObject->getSRBit());
    }else
    {
      if(osrDebug)
      {
        Serial.print("Turning off coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR3 - BIT:");
        Serial.println(CoilObject->getSRBit());
      }
      bitClear(outgoing3,CoilObject->getSRBit());
    }
  }else if(CoilObject->getSR() == 1)
  {
    if(CoilObject->checkStatus())
    {
      if(osrDebug)
      {
        Serial.print("Turning on coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR4 - BIT:");
        Serial.println(CoilObject->getSRBit());
      }
      bitSet(outgoing4,CoilObject->getSRBit());

    }else
    {
      if(osrDebug)
      {
        Serial.print("Turning off coil ");
        Serial.print(CoilObject->getName());
        Serial.print("- OSR4 - BIT:");
        Serial.println(CoilObject->getSRBit());
      }
      bitClear(outgoing4,CoilObject->getSRBit());
    }
  }
}
void manageCoils()
{
  for ( byte coilNumber = 0; coilNumber < coilCount ; coilNumber++) {
    if(coilActive[coilNumber]==true)
    {
      PinballCoil* activeCoil = coils[coilNumber].coilObject;
      activeCoil->manage();
      if(activeCoil->checkStatus()==false)
      {
        ProcessShifts(activeCoil); 
        write_sr_coils();
        coilActive[coilNumber]=false;
      }
    }
  }
}
/*void manageAudio()
{
  byte maxAudio = 39;
  for ( byte audioNumber = 0; audioNumber < maxAudio ; audioNumber++) {
    if(audioActive[audioNumber]==true)
    {
      PinballAudio* activeAudio = audios[audioNumber].AudioObject;
      activeAudio->manage();
      if(activeAudio->checkStatus()==false)    
      {
        audioActive[audioNumber]=false;
        ResetAudioShifts();
      }
    }
  }
}*/
/*
void ResetAudioShifts(){
  outgoing2 = 255;
  write_sr_audio();
  //tso_PinballAudio = tso_PinballAudio + "[ProcessAudioShifts] Setting Shift to "+String(outgoing2);
}
*/

/*void ProcessAudioShifts(PinballAudio* AudioObject)
{  
  outgoing2 = 255;
  outgoing2 = outgoing2 - AudioObject->getSRBit();
  //tso_PinballAudio = tso_PinballAudio + "[ProcessAudioShifts] Setting Shift to "+String(outgoing2);
}*/


void read_sr() {//Read input shift registers
  // Write pulse to load pin
  digitalWrite(isrload, LOW);
  digitalWrite(isrload, HIGH);
  incoming = 0;
  incoming2 = 0;
  digitalWrite(isrclockEnablePin, LOW);
  incoming = shiftIn(isrdataIn, isrclockIn, LSBFIRST);
  incoming2 = shiftIn(isrdataIn, isrclockIn, LSBFIRST);
  digitalWrite(isrclockEnablePin, HIGH);
  if(srDebug){
    Serial.print("read_sr : incoming");
    Serial.print("1->2[");
    Serial.print(incoming);
    Serial.print(",");
    Serial.print(incoming2);
    Serial.println("]");
  }
}
void write_sr_matrix() 
{ // Write to the output shift registers
  digitalWrite(osr1latchPin, LOW);
  shiftOut(osr1dataPin, osr1clockPin, LSBFIRST, outgoing); // changed to MSB to reflect physical wiring
  digitalWrite(osr1latchPin, HIGH);   
  if(srDebug){
    Serial.print("write_sr_matrix : outgoing [");
    Serial.print(outgoing);
    Serial.println("]");
  }   
}  
/*void write_sr_audio() 
{ // Write to the output shift registers
  digitalWrite(osr2latchPin, LOW);
  shiftOut(osr2dataPin, osr2clockPin, MSBFIRST, outgoing2); // changed to MSB to reflect physical wiring
  digitalWrite(osr2latchPin, HIGH);   
  if(srDebug){
    Serial.print("write_sr_audio : outgoing2 [");
    Serial.print(outgoing2);
    Serial.println("]");
  }   
} */  
void write_sr_coils() 
{ // Write to the output shift registers
  digitalWrite(osr3latchPin, LOW);
  
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, outgoing4); // changed to MSB to reflect physical wiring
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, outgoing3); // changed to MSB to reflect physical wiring
  // do it 4 times to simulate writing to 4 595s at once
  digitalWrite(osr3latchPin, HIGH);   
  if(osrDebug){
    Serial.print("write_sr_coils : outgoing");
    Serial.print("4->3[");
    Serial.print(outgoing4);
    Serial.print(",");
    Serial.print(outgoing3);
    Serial.println("]");
  }   
}   
