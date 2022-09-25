// define pins
const int SW0 = 4;        // pin number of push button
const int LED_BLUE = 13;  // pin number of blue led

int buttonState = 0;      // variable to store the button status

void setup() 
{
    // initialize blue led pin as an output
    pinMode(LED_BLUE, OUTPUT);
    
    // initialize the push button pin as an input
    pinMode(SW0, INPUT);
}

void loop() 
{
    // read the status of the push button
    buttonState = digitalRead(SW0);
  
    if (buttonState == LOW) // button is pushed 
    {
        // turn blue led on
        digitalWrite(LED_BLUE, LOW);
    } 
    else // button is released 
    {
        // turn blue led off
        digitalWrite(LED_BLUE, HIGH);
    }
}
