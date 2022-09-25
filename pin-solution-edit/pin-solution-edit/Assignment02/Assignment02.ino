// define pins
const int SW0 = 4;        // pin number of the push button 0
const int SW1 = 5;        // pin number of the push button 1
const int LED_BLUE = 13;  // pin number of the blue led

int buttonState0 = 0;     // variable to store the button 0 status
int buttonState1 = 0;     // variable to store the button 1 status

void setup() 
{
    // initialize the led pins as an output
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, HIGH); // force turn off
  
    // initialize the push button pin as an input
    pinMode(SW0, INPUT);
    pinMode(SW1, INPUT);
}
void loop() 
{
    // read the state of the pushbutton value:
    buttonState0 = digitalRead(SW0);
    buttonState1 = digitalRead(SW1);
  
    if (buttonState0 == LOW) 
    {
        // turn blue led on
        digitalWrite(LED_BLUE,LOW);
    } 
    
    if (buttonState1 == LOW) 
    {
        // turn blue led off
        digitalWrite(LED_BLUE,HIGH);
    } 
}

