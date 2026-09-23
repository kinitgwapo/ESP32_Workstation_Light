#include "led.h"

// Setup Program Function
void setup() {
  Serial.begin(115200);

  pinLedConfig();
  
  Serial.println("PWM Configuration Successful!");
}


// Iteration Codes Function
void loop() {
  // Polling-type function calls
  inputRead();
  inputProcess();
  outputUpdate();
  delay(20);
}