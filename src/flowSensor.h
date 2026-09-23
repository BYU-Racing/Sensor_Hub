#pragma once
#include <Arduino.h>
//Define constants in this file
//Constants must have UNITS in their name and/or description, unless it is not a standard unit.
//Each constant needs to have a description. 


#define READ_VMAX 1023 //maximum value from pin read Units: Arduino voltage reading
#define MAX_VOLTAGE 5  //Input voltage required to get that VMAX Units: voltage

#define read_flowSensor = 100; //Define the time between reads




float flowSensor_voltage(uint8_t pin);

float flowSensor_value_units(uint8_t pin,uint8_t mode);