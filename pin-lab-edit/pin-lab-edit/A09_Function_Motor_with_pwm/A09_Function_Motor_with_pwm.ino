// define left motor pins
#define PIN_MOL_PWM    6
#define PIN_MOL_CW     7
#define PIN_MOL_CCW    8

// define right motor pins
#define PIN_MOR_PWM    9
#define PIN_MOR_CW    10
#define PIN_MOR_CCW   11

// "cw" is short from "clockwise"
// "ccw" is short from "counter-clockwise"
// "pwm" is short from "pulse width moduration"

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
    // initialize motor control pins
    pinMode(PIN_MOL_CW, OUTPUT);
    pinMode(PIN_MOL_CCW, OUTPUT); 
    pinMode(PIN_MOL_PWM, OUTPUT);

    pinMode(PIN_MOR_CW, OUTPUT);
    pinMode(PIN_MOR_CCW, OUTPUT);
    pinMode(PIN_MOR_PWM, OUTPUT); 
}

void loop() 
{
    int pwmForwordLeft = 100, pwmForwordRight = 100;  //min = 0 and max = 255
    int pwmRotateLeft = 80, pwmRotateRight = 80;      //min = 0 and max = 255

    // move forward with forward speed for half seconds
    forward(pwmForwordLeft, pwmForwordRight);
    delay(500);
    
    // stop movement for half second
    stopRobot();
    delay(1000);

    // turn right with turning speed for half second
    turnRight(pwmRotateLeft, pwmRotateLeft);
    delay(500);

    // stop movement for half of second
    stopRobot();
    delay(1000); 
}

