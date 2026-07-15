#include <Arduino.h>

#include <FastLED.h>

#define LED_PIN   18
#define LED_COUNT 45

CRGB leds[LED_COUNT];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(50);
}

void loop() {
  static uint8_t hue = 0;
  fill_rainbow(leds, LED_COUNT, hue++, 7);
  FastLED.show();
  delay(20);
}
