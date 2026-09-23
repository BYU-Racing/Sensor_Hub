#pragma once
#include <Arduino.h>
//Define constants in this file
//Constants must have UNITS in their name and/or description, unless it is not a standard unit.
//Each constant needs to have a description. 

#define FLOWSENSOR_HZ_PER_LPM 7.5         // Per second, 1 liter per minute, the datasheet says 7.5 clicks per second = 1 liter per minute.
#define FLOWSENSOR_WINDOW_MS 1000     // In milliseconds, count clicks for 1000 ms (1 second).



void flowSensorInit(uint8_t pin);
void flowSensor_isr();
float flowSensor_rate_lpm();
