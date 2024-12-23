#include <Arduino.h>

void setupShifts()
{
 // Setup pins for Switch Matrix Out
  pinMode(osr1latchPin, OUTPUT);
  pinMode(osr1clockPin, OUTPUT);
  pinMode(osr1dataPin, OUTPUT);

  // Setup pin for Audio Out
  pinMode(osr2latchPin, OUTPUT);
  pinMode(osr2clockPin, OUTPUT);
  pinMode(osr2dataPin, OUTPUT);
  
  // Setup pins for Coil Out
  pinMode(osr3latchPin, OUTPUT);
  pinMode(osr3clockPin, OUTPUT);
  pinMode(osr3dataPin, OUTPUT);
  
  // Setup 74HC165 connections for SMatrix in and Audio in
  pinMode(isrload, OUTPUT);
  pinMode(isrclockEnablePin, OUTPUT);
  pinMode(isrclockIn, OUTPUT);
  pinMode(isrdataIn, INPUT);
  
  // Set all outputs to zero
  //Open latch
  digitalWrite(osr1latchPin, LOW);
  digitalWrite(osr2latchPin, LOW);
  digitalWrite(osr3latchPin, LOW);
  // Shift out the bits
  shiftOut(osr1dataPin, osr1clockPin, MSBFIRST, 0);
  shiftOut(osr2dataPin, osr2clockPin, MSBFIRST, 0);
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, 0);
  shiftOut(osr3dataPin, osr3clockPin, MSBFIRST, 0); // 2 registers so we have to shift both
  // Close Latch
  digitalWrite(osr1latchPin, HIGH);
  digitalWrite(osr2latchPin, HIGH);
  digitalWrite(osr3latchPin, HIGH);


  //Serial.println("Flushing the shift registers.");
  write_sr_matrix(); // flush out the shift registers
  //write_sr_audio(); // flush out the shift registers
  write_sr_coils(); // flush out the shift registers
  //Serial.println(".");
  read_sr(); // read the shift registers. get rid of any spurious crap on power up.
  //Serial.println(".");
  delay(200);
  //Serial.println(".");
  write_sr_matrix(); // flush out the shift registers
  //write_sr_audio(); // flush out the shift registers
  write_sr_coils(); // flush out the shift registers
  //Serial.println(".");
  read_sr(); // read again after a short delay
  //Serial.println(".");
  delay(1000);
  //Serial.println("done.");

}