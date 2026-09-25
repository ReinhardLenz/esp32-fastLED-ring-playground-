#include "potentiometer.h"
#include <FastLED.h>

// -------------------- Hardware configuration --------------------
static constexpr uint8_t  LED_PIN   = 13;     // T-Beam GPIO 13 -> NeoPixel DIN
static constexpr uint16_t NUM_LEDS  = 45;

static constexpr uint8_t  BRIGHTNESS = 40;
static constexpr int      ADC_MAX    = 4095;  // ESP32 12-bit ADC (0..4095)

// -------------------- Module globals --------------------
static CRGB leds[NUM_LEDS];

void InitPotentiometerLedMapper() {
  Serial.begin(115200);
  delay(200);

  // FastLED init
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);

  // ADC setup (ESP32)
  analogReadResolution(12);                   // 0..4095
  analogSetPinAttenuation(36, ADC_11db);      // ~0..3.3V range (pin is fixed on your board)

  // Prime read (optional)
  (void)analogRead(36);

  Serial.println("ESP32 ADC->45-LED ring mapper started.");
}

float UpdatePotentiometerCorrectionDegrees(uint8_t adcPin) {
  // Read ADC
  const int raw = analogRead(adcPin); // 0..4095

  // LED index mapping (0..44)
  int ledIndex = 44 - (raw * NUM_LEDS) / (ADC_MAX + 1);

  // Clamp LED index (safety)
  if (ledIndex < 0) ledIndex = 0;
  if (ledIndex >= (int)NUM_LEDS) ledIndex = NUM_LEDS - 1;

  // Drive LED ring
  FastLED.clear(false);
  leds[ledIndex] = CRGB::Blue;
  FastLED.show();

  // Compute angle in centi-degrees using integer math with rounding
  const int cdeg = (raw * 36000 + (ADC_MAX / 2)) / ADC_MAX; // 0..36000

  // Convert to float degrees (0.00..360.00)
  const float degrees = cdeg / 100.0f;

  // Debug print
  Serial.println(degrees, 2);

  delay(10);
  return degrees;
}