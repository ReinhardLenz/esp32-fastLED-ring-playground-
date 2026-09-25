#include <Arduino.h>
#include "potentiometer.h"

// -------------------- Hardware configuration --------------------
static constexpr uint8_t ADC_PIN = 36; // T-Beam GPIO 36 -> potentiometer wiper

// This is the value you want to compute in the "one-liner" loop call
float PotentiometerCorrection_degrees = 0.0f;

void setup() {
  InitPotentiometerLedMapper();
}

void loop() {
  PotentiometerCorrection_degrees = UpdatePotentiometerCorrectionDegrees(ADC_PIN);
}