#include "flowSensor.h"
#include <math.h>

float flowSensor_voltage(uint8_t pin){ //simply read the voltage of a given sensor pin
    float out = analogRead(pin);
    out = (out/READ_VMAX)*MAX_VOLTAGE;
    return(out);
}


float flowSensor_value_units(uint8_t pin,uint8_t mode){
    float out = flowSensor_voltage(pin);
    //now do the math you need to to get the correct value.
    //rename this function as follows:
    //sensorname: name of the sensor per data sheet
    //reading: Value in the units requested by the team using the sensor
    //units: what unit are you using? ex: °C, PSI, meters, rpm, m/s, radians.


    return(out);
}