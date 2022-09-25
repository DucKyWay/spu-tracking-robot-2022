// define pins
const int LED_BLUE = 13;  // pin number of blue led
const int LED_GREEN = 12; // pin number of green led

// the setup function runs one time at first
void setup() 
{
    // initialize digital led pins as an output.
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
    // turn blue led off
    digitalWrite(LED_BLUE, HIGH);   
    // turn green led on 
    digitalWrite(LED_GREEN, LOW);   
    // wait for a second
    delay(1000);                   

    // turn blue led on
    digitalWrite(LED_BLUE, LOW);        
    // turn green led off
    digitalWrite(LED_GREEN, HIGH);  
    // wait for a second
    delay(1000);                   
}

