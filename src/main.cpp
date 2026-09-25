#include <Arduino.h>
#include <FastLED.h>

// -------------------- Hardware configuration --------------------
static constexpr uint8_t  LED_PIN   = 13;     // T-Beam GPIO 13 -> NeoPixel DIN
static constexpr uint8_t  ADC_PIN   = 36;     // T-Beam GPIO 36 -> potentiometer wiper
static constexpr uint16_t NUM_LEDS  = 45;

static constexpr uint8_t  BRIGHTNESS = 40;    // keep current low; adjust as needed
static constexpr EOrder   COLOR_ORDER = GRB;


// ADC / voltage mapping
static constexpr float VREF = 3.3f;           // potentiometer supplied from 3V3
static constexpr int   ADC_MAX = 4095;        // ESP32 ADC is 12-bit by default (0..4095)
float angle = 0;
float raw = 0;


// -------------------- Globals --------------------
CRGB leds[NUM_LEDS];
float filteredAdc = 0.0f;

void setup() {
  Serial.begin(115200);
  delay(200);

  // FastLED init
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);

  // ADC setup (ESP32)
  analogReadResolution(12);                 // 0..4095
  analogSetPinAttenuation(ADC_PIN, ADC_11db); // allows reading up to ~3.3V range

  // Prime filter
  int raw = analogRead(ADC_PIN);

  Serial.println("ESP32 ADC->45-LED ring mapper started.");
}

void loop() {
  // 1) Read ADC
  float raw = analogRead(ADC_PIN);

  // 3) Convert to voltage (approx; ESP32 ADC is not perfectly linear)
  float angle = int(raw * 0.088);
  
  
 int ledIndex = (int)(raw/91);



  // Clamp to valid range (important when voltage == VREF)
  if (ledIndex < 0) ledIndex = 0;
  if (ledIndex >= (int)NUM_LEDS) ledIndex = NUM_LEDS - 1;


  // 6) Light exactly one LED, turn others off
  FastLED.clear(false);
  leds[ledIndex] = CRGB::Blue;   // choose your color
  Serial.println(angle, 2);

  FastLED.show();



  delay(10);
}