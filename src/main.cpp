#include <Arduino.h>
#include "can.h"
#include "flowSensor.h"
#include "pressureSensor.h"

// Arduino Pins
#define COOLANT_FLOW_PIN 16
#define COOLANT_TEMP_PIN 17
#define COOLANT_PRESSURE_PIN 18

// Can IDs (check spreadsheet to assign available ids)
#define COOLANT_FLOW_CAN_ID 0x000 //replace
#define COOLANT_TEMP_CAN_ID 0x000 //replace
#define COOLANT_PRESSURE_CAN_ID 0x000 //replace

// Initialize CAN function
FlexCAN_T4<CAN2, RX_SIZE_256> can1;
FloatBytes fb;

//Define values for read time
unsigned long currentReadTime = 0; //current ms 
unsigned long previousReadTime = 0; //ms value of previous reads
unsigned long sensorReadFrequency = 100; //ms between reads


void setup() {
  Serial.begin(115200);
  //Set the pinmodes for each pin
  coolantFlow_init(COOLANT_FLOW_PIN);
  coolantPressure_init(COOLANT_PRESSURE_PIN);
  

  can1.begin();
  can1.setBaudRate(250000);
  while (!Serial) {
    ;
  }
  Serial.println("Setup complete");
  
  
}

void loop() {
  currentReadTime = millis();

  if (currentReadTime - previousReadTime >= sensorReadFrequency){  //Put all code not meant to run constantly here.
    //if your sensor requires a different read frequency or timer, it must be in a different loop.
    previousReadTime = currentReadTime; //Marks this as current read
    
    
    float flow_lpm = coolantFlow_lpm();
    float pressure_bar = coolantPressure_bar();
  
    //uncomment this block of code to read things with CAN
    //can1.write(can_format_message(COOLANT_FLOW_CAN_ID, flow_lpm));
    //can1.write(can_format_message(COOLANT_PRESSURE_CAN_ID, pressure_bar));

    //Uncomment the block of code to read things with serial monitor
    Serial.print("Flow L/min: ");
    Serial.println(flow_lpm);
    Serial.print("Pressure bar: ");
    Serial.println(pressure_bar);  // -999 means sensor fault (broken wire or short)





  }
  //All code meant to run constantly after will run here.

}