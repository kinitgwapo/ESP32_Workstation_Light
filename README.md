# ESP32_Workstation_Light

### Knob & PWM Duty Value Table

| Knob Position | PWM Duty Value | Expected PWM Duty Value |
| :-----------: | :------------: | :---------------------: |
| 0%            | 0              | 0                       |
| 50%           | 127            | 127.5                   |
| 100%          | 255            | 255                     |

### Project's use of Data Types

Static syntax were used to configure private objects, meaning it cannot be used directly from other source files except the led.cpp. The button used a boolean data type because the button can only produce two states, such as true or false, while uint16_t were used to hold values for rawInput ranging from (0-4095), especially for the averaging of values that goes up to 40k integer value with avgRaw. Macros for pin naming were used instead of a variable holding a number and initializing it as a constant.
