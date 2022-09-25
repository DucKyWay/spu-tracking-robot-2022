// define left motor pins
#define PIN_MOL_PWM   6
#define PIN_MOL_CW    7
#define PIN_MOL_CCW   8

// define right motor pins
#define PIN_MOR_PWM   9
#define PIN_MOR_CW    10
#define PIN_MOR_CCW   11

// define pins
const byte ledPin = 13;
const byte interruptPinL = 2;
const byte interruptPinR = 21;

// variable to count for left and right motors 
int counterL = 0;
int counterR = 0;

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

void stopRobot()
{
    // left motor stop rotation (en = 0)
    digitalWrite(PIN_MOL_PWM, LOW);

    // right motor stop rotation (en = 0)
    digitalWrite(PIN_MOR_PWM, LOW);
}

void setup() 
{
    // initialize motor pins
    pinMode(PIN_MOL_CW, OUTPUT);
    pinMode(PIN_MOL_CCW, OUTPUT); 
    pinMode(PIN_MOL_PWM, OUTPUT);
    
    pinMode(PIN_MOR_CW, OUTPUT);
    pinMode(PIN_MOR_CCW, OUTPUT);
    pinMode(PIN_MOR_PWM, OUTPUT); 

    // initialize pins
    pinMode(ledPin, OUTPUT);
    pinMode(interruptPinL, INPUT_PULLUP);
    pinMode(interruptPinR, INPUT_PULLUP);
    
    // attach isr (interrupt subroutine)
    attachInterrupt(digitalPinToInterrupt(interruptPinL), fun_counterL, CHANGE);
    attachInterrupt(digitalPinToInterrupt(interruptPinR), fun_counterR, CHANGE);
    
    // initialize communication buad rate 
    Serial.begin(115200);
}

void loop() 
{
    digitalWrite(ledPin, HIGH);
    
    Serial.println(counterL);
    while (counterL < 400)
    {
        forward(100, 100); 
    }
    
    stopRobot(); 

    digitalWrite(ledPin, LOW);
}

void fun_counterL() 
{
    counterL++;
}

void fun_counterR() 
{
    counterR++;
}
