#include "flowSensor.h"


// Number of pulses seen since the last calculation.
// "volatile" because the interrupt changes it behind the main loop's back,
// so the compiler must re-read it from memory every time.
static volatile uint32_t pulseCount = 0;

static unsigned long lastCalcTime_ms = 0;  // millis() when we last calculated a flow rate
static float lastFlow_lpm = 0;             // Most recent flow rate, returned between calculations



// Runs automatically every time the signal pin goes LOW -> HIGH (one pulse).
// Interrupts should be as short as possible, so all it does is count.
void flowSensor_isr() {
    pulseCount++;
}

void flowSensorInit(uint8_t pin) {
    // Plain INPUT: the voltage divider sets the voltage, so no internal pull-up.
    pinMode(pin, INPUT);
    // Call flowSensor_isr on every rising edge, so no pulses are missed
    // even while the main loop is busy doing something else.
    attachInterrupt(digitalPinToInterrupt(pin), flowSensor_isr, RISING);
}

float flowSensor_rate_lpm() {
    unsigned long now_ms = millis();

    // Not enough time has passed to count a full window yet,
    // so return the last value instead of calculating from too few pulses.
    if ((now_ms - lastCalcTime_ms) < FLOWSENSOR_WINDOW_MS) {
        return lastFlow_lpm;
    }

    // Copy the count and reset it with interrupts paused, so a pulse can't
    // arrive halfway through and get lost between the read and the reset.
    noInterrupts();
    uint32_t pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    // Pulses per second -> liters per minute.
    // Uses the real elapsed time rather than FLOWSENSOR_WINDOW_MS, since this
    // function may be called a little after the window ends.
    float elapsed_s = (now_ms - lastCalcTime_ms) / 1000.0;
    float pulsesPerSecond = pulses / elapsed_s;
    float flow_lpm = pulsesPerSecond / FLOWSENSOR_HZ_PER_LPM;

    lastFlow_lpm = flow_lpm;
    lastCalcTime_ms = now_ms;
    return flow_lpm;
}
