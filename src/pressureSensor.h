#pragma once
#include <Arduino.h>
//Define constants in this file
//Constants must have UNITS in their name and/or description, unless it is not a standard unit.
//Each constant needs to have a description.

// Coolant pressure sensor (Nuke Performance 10 bar / 150 psi)
// Outputs a voltage that rises in a straight line with pressure:
// 0.5V at 0 bar up to 4.5V at 10 bar. We read that voltage with the ADC
// and convert it back to bar.
//
// Wiring:
//   Pin A, Black      -> GND
//   Pin B, Red        -> 5V (Teensy VIN)
//   Pin C, Blue/Green -> voltage divider (10k from signal to pin, 20k from pin to GND) -> analog pin
//   The sensor outputs up to 4.5V, and Teensy pins are only 3.3V tolerant,
//   so the divider is required. Add a 0.1uF cap from the analog pin to GND to reduce noise.
//
// Output is ratiometric: it scales with the 5V supply, so if VIN is not exactly 5V
// the readings shift slightly. Calibrate against a known gauge.

#define COOLANT_PRESSURE_DIVIDER_RATIO 0.6667      // Pin voltage / sensor voltage. 20k / (10k + 20k). Replace with measured value.
#define COOLANT_PRESSURE_ADC_REFERENCE_V 3.3       // In volts: the voltage that reads as ADC max count.
#define COOLANT_PRESSURE_ADC_RESOLUTION_BITS 10    // ADC resolution in bits, passed to analogReadResolution().
#define COOLANT_PRESSURE_ADC_MAX_COUNT 1023.0      // Highest ADC reading at this resolution (2^10 - 1).
#define COOLANT_PRESSURE_SENSOR_MIN_V 0.5          // In volts: sensor output at 0 bar (from product listing).
#define COOLANT_PRESSURE_SENSOR_MAX_V 4.5          // In volts: sensor output at full scale pressure (from product listing).
#define COOLANT_PRESSURE_FULL_SCALE_BAR 10.0       // In bar: pressure when the sensor outputs its max voltage.
#define COOLANT_PRESSURE_SAMPLES_TO_AVERAGE 8      // Number of ADC reads averaged per reading, to smooth out noise.
#define COOLANT_PRESSURE_FAULT_LOW_V 0.25          // In volts at the sensor: below this means a broken wire or short to GND.
#define COOLANT_PRESSURE_FAULT_HIGH_V 4.75         // In volts at the sensor: above this means a short to 5V.
#define COOLANT_PRESSURE_INVALID_READING_VALUE (-999.0)  // Returned instead of a pressure when a fault is detected.



void coolantPressure_init(uint8_t pin);            // Call once in setup(). Sets up the analog pin and ADC resolution.
float coolantPressure_readAdc();                   // Returns the averaged raw ADC count.
float coolantPressure_adcToVolts(float adc);       // Converts an ADC count to the sensor's output voltage (before the divider).
float coolantPressure_voltsToBar(float sensor_v);  // Converts sensor output voltage to pressure in bar.
float coolantPressure_bar();                       // Returns pressure in bar, or COOLANT_PRESSURE_INVALID_READING_VALUE on a fault.
