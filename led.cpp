#include "led.h"





// Initialized Variables
static bool buttonPressed = false;
static uint16_t rawInput = 0;
static uint8_t appliedDuty = 0;





void pinLedConfig(void) {
  // GPIO Configurations
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_STATUS_PIN, OUTPUT);
  pinMode(LED_PWM_PIN, OUTPUT);

  // ADC Configuration
  analogReadResolution(12);
  analogSetPinAttenuation(POTENTIOMETER_PIN, ADC_11db);

  // PWM Configuration (Keeps looping until PWM pin is successfully configured)
  while(!ledcAttach(LED_PWM_PIN, 5000, 8)) {
    delay(100);
  }
  ledcWrite(LED_PWM_PIN, 0);
}





void inputRead(void) {
  buttonPressed = !digitalRead(BUTTON_PIN);
  rawInput = analogRead(POTENTIOMETER_PIN);
}





static uint8_t scaleToDuty(uint16_t raw) {
  raw = map(rawInput, 0, 4095, 0, 255);
  return constrain(raw, 0L, 255L);
}

void inputProcess(void) {
  // Calibrate rawInput Value Boundaries
  uint8_t requestedDuty = scaleToDuty(rawInput);

  // Update appliedDuty with either the Calibrated or 0 value
  appliedDuty = (buttonPressed) ? requestedDuty : 0;
}





static void avgFormula(void) {
  static uint16_t avgRaw = 0;
  static uint16_t avgDuty = 0;
  static uint8_t iteration = 1;
  avgRaw += rawInput;
  avgDuty += appliedDuty;
  iteration++;

  // Print once the summation terms achieve 20 terms
  if(iteration > 20) {
    Serial.println("Raw Value: "+ String(avgRaw / 20) + "\tPWM Duty Value: " + String(avgDuty / 20));

    // Reset avg and iteration
    avgRaw = avgDuty = 0;
    iteration = 1;
  }
}

void outputUpdate(void) {
  // Update Pin 18's State
  digitalWrite(LED_STATUS_PIN, buttonPressed ? HIGH : LOW);

  // Change Pin 19's PWM Duty Value
  ledcWrite(LED_PWM_PIN, appliedDuty);

  avgFormula();
}