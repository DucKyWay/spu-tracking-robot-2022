// define pins
const int LED_BLUE = 13;  // pin number of blue led
const int SW0 = 4;        // pin number of push button 0
const int SW1 = 5;        // pin number of push button 1

int i,count=3;

void setup() 
{
    // initialize digital blue led pin as an output
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, HIGH); // force turn off
   
    // initialize the push button pin as an input
    pinMode(SW0, INPUT);
    pinMode(SW1, INPUT);
}

void loop() 
{   
    if (digitalRead(SW0) == LOW) // push button 0 is pushed
    {
        // set blink to 3 times
        count = 3; 
        for(i = 0; i < count; i++) 
        {
            // turn blue led on for half second
            digitalWrite(LED_BLUE, LOW);
            delay(500);                       
            
            // turn off blue led for half second
            digitalWrite(LED_BLUE, HIGH);
            delay(500);
        }
    }
   
    if (digitalRead(SW1) == LOW) // push button 1 is pushed
    {
        // set blink count to 5 times
        count = 5; 
        i = 0;
        
        //for(i = 0; i < count; i++) 
        while (i < count)
        {
            // turn blue led on for half second
            digitalWrite(LED_BLUE, LOW);   
            delay(500);
            
            // turn off blue led for half second
            digitalWrite(LED_BLUE, HIGH);    
            delay(500);

            i ++;
        }
    }
}
