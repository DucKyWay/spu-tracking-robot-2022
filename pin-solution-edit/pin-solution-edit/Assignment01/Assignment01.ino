// define pins
int LED_BLUE = 13;  // pin number of blue led, active low
int LED_GREEN = 12; // pin number of green led, active low
int LED_RED = 52;   // pin number of red led, active high

void setup() 
{
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
    // turn on only red led for one second
    digitalWrite(LED_RED, HIGH); 
    digitalWrite(LED_BLUE, HIGH); 
    digitalWrite(LED_GREEN, HIGH); 
    delay(1000);

    // turn on only blue led for one second
    digitalWrite(LED_RED, LOW); 
    digitalWrite(LED_BLUE, LOW); 
    digitalWrite(LED_GREEN, HIGH); 
    delay(1000);

    // turn on only green led for one second
    digitalWrite(LED_RED, LOW); 
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, LOW); 
    delay(1000);
}
