// the setup function runs one time at first
void setup() 
{
    // initialize built-in led pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
    // turn built-in led off
    digitalWrite(LED_BUILTIN, HIGH);
       
    // wait for a second
    delay(500);                       
    
    // turn built-in led on by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);    

    // wait for a second
    delay(2000);                       
}

