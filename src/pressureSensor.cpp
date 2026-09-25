#include "pressureSensor.h"


// Analog pin the sensor is wired to. Saved by coolantPressure_init so the
// other functions don't need it passed in every time.
static uint8_t sensorPin;



void coolantPressure_init(uint8_t pin) {
    sensorPin = pin;
    // Plain INPUT: the voltage divider sets the voltage, so no internal pull-up.
    pinMode(sensorPin, INPUT);
    analogReadResolution(COOLANT_PRESSURE_ADC_RESOLUTION_BITS);
}

float coolantPressure_readAdc() {
    // Take several reads and average them to smooth out electrical noise.
    int adcSum = 0;
    for (uint8_t i = 0; i < COOLANT_PRESSURE_SAMPLES_TO_AVERAGE; i++) {
        adcSum += analogRead(sensorPin);
    }
    // Cast to float before dividing so the average keeps its decimal part.
    float adcAverage = (float)adcSum / COOLANT_PRESSURE_SAMPLES_TO_AVERAGE;
    return adcAverage;
}

float coolantPressure_adcToVolts(float adc) {
    // ADC count -> voltage at the Teensy pin (after the divider).
    float pin_v = adc / COOLANT_PRESSURE_ADC_MAX_COUNT * COOLANT_PRESSURE_ADC_REFERENCE_V;
    // Undo the divider to get the voltage the sensor is actually outputting.
    float sensor_v = pin_v / COOLANT_PRESSURE_DIVIDER_RATIO;
    return sensor_v;
}

float coolantPressure_voltsToBar(float sensor_v) {
    // The sensor output is a straight line from MIN_V at 0 bar to MAX_V at full scale.
    // Find how far along that line we are (0.0 to 1.0), then scale to bar.
    // Readings slightly below MIN_V come out slightly negative. That's left in on
    // purpose so any zero offset is visible during calibration.
    float fractionOfFullScale = (sensor_v - COOLANT_PRESSURE_SENSOR_MIN_V) / (COOLANT_PRESSURE_SENSOR_MAX_V - COOLANT_PRESSURE_SENSOR_MIN_V);
    float pressure_bar = fractionOfFullScale * COOLANT_PRESSURE_FULL_SCALE_BAR;
    return pressure_bar;
}

float coolantPressure_bar() {
    float adcAverage = coolantPressure_readAdc();
    float sensor_v = coolantPressure_adcToVolts(adcAverage);

    // A working sensor never outputs outside 0.5-4.5V, so anything well outside
    // that range means a broken wire or short, not a real pressure.
    if ((sensor_v < COOLANT_PRESSURE_FAULT_LOW_V) || (sensor_v > COOLANT_PRESSURE_FAULT_HIGH_V)) {
        return COOLANT_PRESSURE_INVALID_READING_VALUE;
    }
    float pressure_bar = coolantPressure_voltsToBar(sensor_v);
    return pressure_bar;
}
