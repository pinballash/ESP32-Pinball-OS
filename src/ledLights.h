#include <Arduino.h>
//include dependancies
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B setting_ledPin  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS setting_leds   // The number of LEDs (pixels) on WS2812B LED strip

int ledBrightness = 5; //out of 255

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
