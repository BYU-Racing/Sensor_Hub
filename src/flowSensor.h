#pragma once
#include <Arduino.h>
//Define constants in this file
//Constants must have UNITS in their name and/or description, unless it is not a standard unit.
//Each constant needs to have a description.

// Coolant flow sensor (YF-S201)
// A small turbine spins as coolant flows through it, and the sensor outputs one
// pulse per step of rotation. More flow = faster pulses. We count the pulses
// over a fixed time window and convert pulses per second into liters per minute.
//
// Wiring:
//   Red    -> 5V (Teensy VIN)
//   Black  -> GND
//   Yellow -> voltage divider (10k from yellow to pin, 20k from pin to GND) -> signal pin
//   The sensor outputs a 0-5V square wave (checked on a scope), and Teensy pins
//   are only 3.3V tolerant, so the divider is required. Do not use INPUT_PULLUP.

#define COOLANT_FLOW_HZ_PER_LPM 7.5   // Calibration: pulses per second (Hz) produced by 1 L/min of flow. 7.5 is from the YF-S201 datasheet.
                                      // Initial bucket test (0.5 L in 20 s = 1.5 L/min) read ~11% low, suggesting ~6.7.
                                      // That test was at very low flow where the rotor slips, so retest at real coolant flow before changing.
#define COOLANT_FLOW_WINDOW_MS 1000   // In milliseconds: how long to count pulses before calculating a new flow rate.
                                      // Longer = smoother reading but slower to update.



void coolantFlow_init(uint8_t pin);  // Call once in setup(). Sets up the pin and starts counting pulses.
void coolantFlow_isr();              // Interrupt handler: runs automatically on every pulse. Do not call directly.
float coolantFlow_lpm();             // Returns flow rate in liters per minute. Safe to call as often as you like.
