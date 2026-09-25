#include <Arduino.h>
#include "can.h"
#include "sensorname.h"
#include "sensorname.cpp"

// Arduino Pins
#define SENSORNAME_PIN 16

// Can IDs (check spreadsheet to assign available ids)
#define SENSORNAME_CAN_ID 0x000 //replace if needed

// Initialize CAN function
FlexCAN_T4<CAN2, RX_SIZE_256> can1;
FloatBytes fb;

//Define values for read time
unsigned long currentReadTime = 0; //current ms 
unsigned long previousReadTime = 0; //ms value of previous reads
unsigned long sensorReadFrequencyA = 100; //ms between reads


void setup() {
  Serial.begin(115200);
  //Set the pinmodes for each pin
  pinMode(SENSORNAME_PIN,INPUT);
  

  can1.begin();
  can1.setBaudRate(250000);
  while (!Serial) {
    ;
  }
  Serial.println("Setup complete");
  
  
}

void loop() {
  if (currentReadTime - previousReadTime >= sensorReadFrequencyA){  //Put all code not meant to run constantly here.
    //if your sensor requires a different read frequency or timer, it must be in a different loop.
    previousReadTime = currentReadTime; //Marks this as current read
    
    
    float sensorname_output_value = sensorname_convertdata(SENSORNAME_PIN, 1);
    //uncomment this block of code to read things with CAN
    //can1.write(can_format_message(SENSORNAME_CAN_ID, sensorname_output_value));

    //Uncomment the block of code to read things with serial monitor
    //Serial.print("Sensor Unit:");
    //Serial.println(sensorname_output_value);





  }
  //All code meant to run constantly after will run here.

}