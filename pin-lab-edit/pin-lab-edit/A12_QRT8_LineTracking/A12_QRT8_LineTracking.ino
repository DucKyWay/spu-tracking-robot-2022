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

// define left motor pins
#define PIN_MOL_PWM    6
#define PIN_MOL_CW     7
#define PIN_MOL_CCW    8

// define right motor pins
#define PIN_MOR_PWM    9
#define PIN_MOR_CW     10
#define PIN_MOR_CCW    11

#define CALIBRATE_SPEED (30.0 / 100.0 * 255.0) 

void forward(unsigned int leftSpeed, unsigned int rightSpeed)
{
    // left motor rotate in ccw direction
    digitalWrite(PIN_MOL_CW, LOW);
    digitalWrite(PIN_MOL_CCW, HIGH);
    analogWrite(PIN_MOL_PWM, leftSpeed);

    // right motor rotate in cw direction
    digitalWrite(PIN_MOR_CW, HIGH);
    digitalWrite(PIN_MOR_CCW, LOW);
    analogWrite(PIN_MOR_PWM, rightSpeed);    
}

void backward(unsigned int leftSpeed, unsigned int rightSpeed)
{
    // left motor rotate in cw direction
    digitalWrite(PIN_MOL_CW, HIGH);
    digitalWrite(PIN_MOL_CCW, LOW);
    analogWrite(PIN_MOL_PWM, leftSpeed);

    // right motor rotate in ccw direction
    digitalWrite(PIN_MOR_CW, LOW);
    digitalWrite(PIN_MOR_CCW, HIGH);
    analogWrite(PIN_MOR_PWM, rightSpeed);
}

void turnLeft(unsigned int leftSpeed, unsigned int rightSpeed)
{
    // left motor rotate in ccw direction
    digitalWrite(PIN_MOL_CW, HIGH);
    digitalWrite(PIN_MOL_CCW, LOW); 
    analogWrite(PIN_MOL_PWM, leftSpeed);

    // right motor rotate in cw direction
    digitalWrite(PIN_MOR_CW, HIGH);
    digitalWrite(PIN_MOR_CCW, LOW);
    analogWrite(PIN_MOR_PWM, rightSpeed);        
}

void turnRight(unsigned int leftSpeed, unsigned int rightSpeed)
{
    // left motor rotate in cw direction
    digitalWrite(PIN_MOL_CW, LOW);
    digitalWrite(PIN_MOL_CCW, HIGH);
    analogWrite(PIN_MOL_PWM, leftSpeed);

    // right motor rotate in ccw direction
    digitalWrite(PIN_MOR_CW, LOW);
    digitalWrite(PIN_MOR_CCW, HIGH);
    analogWrite(PIN_MOR_PWM, rightSpeed);        
}

void stopRobot()
{
    // left motor stop rotation (en = 0)
    digitalWrite(PIN_MOL_PWM, LOW);

    // right motor stop rotation (en = 0)
    digitalWrite(PIN_MOR_PWM, LOW);
}

void setup()
{    
    // initialize communication buad rate 
    Serial.begin(9600);
      
    for (int i = 0; i < 50; i++)
    { 
        // calibrate for sometime by sliding the sensors across the line, 
        // or you may use auto-calibration instead
        // comment this part out for automatic calibration 

        // turn left or turn right to expose the sensors to the brightest and darkest 
        // readings that may be encountered
        if ( i  < 12 || i >= 38 ) 
            turnLeft(CALIBRATE_SPEED, CALIBRATE_SPEED);   
        else
            turnRight(CALIBRATE_SPEED, CALIBRATE_SPEED); 
      
        qtrrc.calibrate();     
    }
    
    stopRobot();

    Serial.print("Min: ");
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print(qtrrc.calibratedMinimumOn[i]);
        Serial.print("\t");
    }
    Serial.println();
  
    //delay(5); 
    Serial.print("Max: ");
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print(qtrrc.calibratedMaximumOn[i]);
        Serial.print("\t");
    }  
    Serial.println();
}

void loop()
{ 
    do
    {
        int position = qtrrc.readLine(sensorValues);
        Serial.println(position);
        if (position < 0)
        {
            stopRobot();
        }
        if (position >= 0 && position <= 1000)
        {    
            turnRight(100, 40); 
        }
        else if (position > 1000 && position <= 2000)    
        {
            turnRight(100, 30); 
        }
        else if (position > 2000 && position <= 3000)    
        {
            turnRight(100, 20); 
        }
        else if (position > 3000 && position <= 4000)    
        {
            forward(100, 100); 
        }
        else if (position > 4000 && position <= 5001)    
        {
            turnLeft(20, 100); 
        }
        else if (position > 5000 && position <= 6000)    
        {
            turnLeft(30, 100);
        }
        else if (position > 6000 && position <= 7000)    
        {
            turnLeft(40, 100);
        }
        else // position > 7000
        {
            stopRobot();   
        }
        
    } while(1);
}

