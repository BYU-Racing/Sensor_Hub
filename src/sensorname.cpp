#include "sensorname.h"
#include <math.h>

float sensorname_getrawdata(uint8_t pin){ 
    //simply read the voltage of a given sensor pin
    //if your sensor is just reading voltage, change getrawdata to "voltage"
    //if your sensor does NOT just read voltage (ex: I2C), rename as appropriate

    float out = analogRead(pin);
    out = (out/READ_VMAX)*MAX_VOLTAGE; 
    return(out);
}


float sensorname_convertdata(uint8_t pin,uint8_t mode){
    float out = sensorname_getrawdata(pin);
    //now do the math you need to to get the correct value.
    //rename this function as follows:
    //sensorname: name of the sensor per data sheet
    //reading: Value in the units requested by the team using the sensor
    //units: what unit are you using? ex: °C, PSI, meters, rpm, m/s, radians.


    return(out);
}