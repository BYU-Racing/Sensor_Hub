#pragma once
#include <Arduino.h>
//Define constants in this file
//Constants must have UNITS in their name and/or description, unless it is not a standard unit.
//Each constant needs to have a description. 


#define COOLANT_TEMP_PULLUP_OHMS 1000.0
#define COOLANT_TEMP_ADC_RESOLUTION_BITS 10
#define COOLANT_TEMP_ADC_MAX_COUNT 1023
#define COOLANT_TEMP_SAMPLES_TO_AVERAGE 8
const float COOLANT_TEMP_TABLE_C[] = {-20, -10, 0, 10, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 140, 160};
const float COOLANT_TEMP_TABLE_OHMS[] = {28146, 15873, 9256, 5572, 3457, 2830, 2205, 1443, 992, 660, 475, 329, 244, 175, 134, 99, 60, 47};
#define COOLANT_TEMP_TABLE_LENGTH 18
#define COOLANT_TEMP_INVALID_READING_VALUE (-999.0)


void coolantTemp_init(uint8_t pin);      
float coolantTemp_readAdc();            
float coolantTemp_adcToOhms(float adc);
float coolantTemp_ohmsToC(float ohms);              
float coolantTemp_c();                        

