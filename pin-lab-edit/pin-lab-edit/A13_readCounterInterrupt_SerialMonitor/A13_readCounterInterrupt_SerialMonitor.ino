// define pins
const byte ledPin = 13;
const byte interruptPinL = 2;
const byte interruptPinR = 21;

// variable to count for left and right motors 
int counterL = 0;
int counterR = 0;

void setup() 
{
    // initialize pins
    pinMode(ledPin, OUTPUT);
    pinMode(interruptPinL, INPUT_PULLUP);
    pinMode(interruptPinR, INPUT_PULLUP);
    
    // attach isr (interrupt subroutine)
    attachInterrupt(digitalPinToInterrupt(interruptPinL), fun_counterL, CHANGE);
    attachInterrupt(digitalPinToInterrupt(interruptPinR), fun_counterR, CHANGE);

    // initialize communication buad rate 
    Serial.begin(9600);
}

void loop() 
{
    static int tempCounterL, tempCounterR;
    if (tempCounterL != counterL || tempCounterR != counterR)
    {
        digitalWrite(ledPin, LOW);
        Serial.print(counterL);
        Serial.print("\t");
        Serial.println(counterR);
        tempCounterL = counterL;
        tempCounterR = counterR;
    }  
    digitalWrite(ledPin, HIGH);
}

void fun_counterL() 
{
    counterL++;
}

void fun_counterR() 
{
    counterR++;
}
