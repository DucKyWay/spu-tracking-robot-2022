#include "QTRSensors.h"

// define constant for QTR sensor
#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN   4  

// sensor connected through analog pins A0 - A5 i.e. digital pins 14 - 19
unsigned char sensorPins[] = {22, 23, 24, 25, 26, 27, 28, 29};
QTRSensorsRC qtrrc(sensorPins, NUM_SENSORS, TIMEOUT, EMITTER_PIN);

// variable to store all sensor status
unsigned int sensorValues[NUM_SENSORS];

void setup() {    
    // initialize communication buad rate 
    Serial.begin(9600);
}

void loop() { 
    do {
        qtrrc.read(sensorValues); 
        Serial.print(sensorValues[7]);
        Serial.print("\t");
        Serial.print(sensorValues[6]);
        Serial.print("\t");
        Serial.print(sensorValues[5]);
        Serial.print("\t");
        Serial.print(sensorValues[4]);
        Serial.print("\t");
        Serial.print(sensorValues[3]);
        Serial.print("\t");
        Serial.print(sensorValues[2]);
        Serial.print("\t");
        Serial.print(sensorValues[1]);
        Serial.print("\t");
        Serial.print(sensorValues[0]);
        Serial.println();
        delay(500);
    } while(1);
}

