#include "flowSensor.h"



static volatile uint32_t countedClicks = 0;
static unsigned long mathLastPerformed = 0;
static float previousFlow = 0;





void flowSensor_isr() {
    countedClicks++;
}

void flowSensorInit(uint8_t pin) {
    pinMode(pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(pin), flowSensor_isr, RISING);
}

float flowSensor_rate_lpm() {
    unsigned long currentTime = millis();
    if ((currentTime - mathLastPerformed) < FLOWSENSOR_WINDOW_MS) {
        return previousFlow;
    } 
    noInterrupts();
    uint32_t currentCountedClicks = countedClicks;
    countedClicks = 0;
    interrupts();

    float timePassed = (currentTime - mathLastPerformed) / 1000.0;
    float clicksPerSecond = currentCountedClicks / timePassed;
    float litersPerMinute = clicksPerSecond / FLOWSENSOR_HZ_PER_LPM;
    previousFlow = litersPerMinute;
    mathLastPerformed = currentTime;
    return litersPerMinute;

}