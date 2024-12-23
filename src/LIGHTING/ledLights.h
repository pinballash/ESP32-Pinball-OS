#include <Arduino.h>
/*//include dependancies
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_WS2812B setting_ledPin  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS setting_leds   // The number of LEDs (pixels) on WS2812B LED strip

int ledBrightness = 64; //out of 255 //64 is 1/4 power 1.25A for 100 LEDS

//Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
*/
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#define DATA_PIN 16  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_LEDS 93  // The number of LEDs (pixels) on WS2812B LED strip

CRGB ledArray[NUM_LEDS];

