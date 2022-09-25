// define left motor pins
#define PIN_MOL_PWM   6
#define PIN_MOL_CW    7
#define PIN_MOL_CCW   8

// define right motor pins
#define PIN_MOR_PWM    9
#define PIN_MOR_CW    10
#define PIN_MOR_CCW   11

// "cw" is short from "clockwise"
// "ccw" is short from "counter-clockwise"

void forward() {
    // left motor rotate in ccw direction
    digitalWrite(PIN_MOL_CW, LOW);
    digitalWrite(PIN_MOL_CCW, HIGH);
    digitalWrite(PIN_MOL_PWM, HIGH);

    // right motor rotate in cw direction
    digitalWrite(PIN_MOR_CW, HIGH);
    digitalWrite(PIN_MOR_CCW, LOW);
    digitalWrite(PIN_MOR_PWM, HIGH);
}

void backward() {
    // left motor rotate in cw direction
    digitalWrite(PIN_MOL_CW, HIGH);
    digitalWrite(PIN_MOL_CCW, LOW);
    digitalWrite(PIN_MOL_PWM, HIGH);

    // right motor rotate in ccw direction
    digitalWrite(PIN_MOR_CW, LOW);
    digitalWrite(PIN_MOR_CCW, HIGH);
    digitalWrite(PIN_MOR_PWM, HIGH);
}

void turnLeft() {
    // left motor rotate in ccw direction
    digitalWrite(PIN_MOL_CW, HIGH);
    digitalWrite(PIN_MOL_CCW, LOW); 
    digitalWrite(PIN_MOL_PWM, HIGH);

    // right motor rotate in cw direction
    digitalWrite(PIN_MOR_CW, HIGH);
    digitalWrite(PIN_MOR_CCW, LOW);
    digitalWrite(PIN_MOR_PWM, HIGH);        
}

void turnRight() {
    // left motor rotate in cw direction
    digitalWrite(PIN_MOL_CW, LOW);
    digitalWrite(PIN_MOL_CCW, HIGH);
    digitalWrite(PIN_MOL_PWM, HIGH);

    // right motor rotate in ccw direction
    digitalWrite(PIN_MOR_CW, LOW);
    digitalWrite(PIN_MOR_CCW, HIGH);
    digitalWrite(PIN_MOR_PWM, HIGH);        
}

void stopRobot() {
    // left motor stop rotation (en = 0)
    digitalWrite(PIN_MOL_PWM, LOW);

    // right motor stop rotation (en = 0)
    digitalWrite(PIN_MOR_PWM, LOW);
}

void setup() {
    // initialize motor control pins
    pinMode(PIN_MOL_CW, OUTPUT);
    pinMode(PIN_MOL_CCW, OUTPUT); 
    pinMode(PIN_MOL_PWM, OUTPUT);

    pinMode(PIN_MOR_CW, OUTPUT);
    pinMode(PIN_MOR_CCW, OUTPUT);
    pinMode(PIN_MOR_PWM, OUTPUT); 
}

void loop() {
    // move forward for two seconds
    forward();
    delay(1000);

    // stop movement for two seconds
    stopRobot();
    delay(2000);

    // move backward for two seconds
    backward();
    delay(1000);

    // stop movement for two seconds
    stopRobot();
    delay(2000);
}
