// define pins
const int LED_BLUE = 13;  // pin number of blue led
const int SW0 = 4;        // pin number of push button 0

int i, count = 3;

void setup() 
{
    // initialize digital blue led pin as an output
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, HIGH); // force turn off
   
    // initialize the push button pin as an input
    pinMode(SW0, INPUT);
}

void loop() 
{   
    if (digitalRead(SW0) == LOW) // push button 0 is pushed
    {
        // set i to zero
        i = 0;   

        do
        {
            if (i < count) break;
            
            // turn blue led on for one second
            digitalWrite(LED_BLUE, LOW);
            delay(1000);                       

            // trun blue led off for one second
            digitalWrite(LED_BLUE, HIGH);
            delay(1000);

            // increase i by 1
            i++;
            
        } while (i <= count);
    }
}

