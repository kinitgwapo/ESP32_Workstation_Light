#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>
#include <Arduino.h>

// Pin Names Macros
#define BUTTON_PIN 23
#define POTENTIOMETER_PIN 34
#define LED_STATUS_PIN 18
#define LED_PWM_PIN 19

// Function Declarations
void pinLedConfig(void); // Config the macro pins
void inputRead(void); // Read button & potentiometer pins

/*
Private function, used to calibrate the rawInput from inputProcess function
static uint8_t scaleToDuty(uint16_t raw);
*/

void inputProcess(void); // Process raw Analog input from potentiometer (ADC)
void outputUpdate(void); // Updates the LED status and PWM pin



#endif