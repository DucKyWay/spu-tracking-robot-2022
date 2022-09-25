#include "QTRSensors.h"

#define   Kp                  2         //2=100Pok   // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define   Kd                  5         //5=100Pok   // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define   sKp                 2         //2=100Pok   // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define   sKd                 5         //5=100Pok 
#define   rightMaxSpeed       100.0/100.0*255.0      // max speed of the robot
#define   leftMaxSpeed        100.0/100.0*255.0      // max speed of the robot
#define   rightBaseSpeed      70.0/100.0*255.0       // this is the speed at which the motors should spin when the robot is perfectly on the line
#define   leftBaseSpeed       70.0/100.0*255.0       // this is the speed at which the motors should spin when the robot is perfectly on the line
#define   calibrateSpeed      30.0/100.0*255.0  
#define   Speed90             70.0/100.0*255.0 
#define   rSpeed              -20 
#define   stopmotor           6.0/100.0*255.0 
#define   slowmotor           4.0/100.0*255.0 
#define   BuffrightMaxSpeed   0 
#define   BuffleftMaxSpeed    0  

#define   SrightMaxSpeed      100.0/100.0*255.0      // max speed of the robot
#define   SleftMaxSpeed       100.0/100.0*255.0      // max speed of the robot
#define   SrightBaseSpeed     100.0/100.0*255.0      // this is the speed at which the motors should spin when the robot is perfectly on the line
#define   SleftBaseSpeed      100.0/100.0*255.0      

#define NUM_SENSORS           8         // number of sensors used
#define TIMEOUT               2500      // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN           4         // emitter is controlled by digital pin 2
#define PWM_STOP              0

#define pin_pwm_R             9
#define moR_cw                10
#define moR_ccw               11

//#define DIRB 13
#define pin_pwm_L             6
#define moL_cw                7
#define moL_ccw               8

#define START                 4

#define led_Red0              30 
#define led_Blue              13 
#define led_Green             12
#define led_Red               52

#define boton_1               4  //pin para boton
#define boton_2               5  //pin para boton
#define MAXcount_ERR 30

boolean chk = false;
unsigned int count_ERR;
int sensorVal;
unsigned char RUN_STOP = 0;
#define OLED_RESET 4  

QTRSensorsRC qtrrc((unsigned char[]){22,23,24,25,26,27,28,29},NUM_SENSORS, TIMEOUT, EMITTER_PIN); // sensor connected through analog pins A0 - A5 i.e. digital pins 14-19
//QTRSensorsRC qtrrc((unsigned char[]){29,28,27,26,25,24,23,22},NUM_SENSORS, TIMEOUT, EMITTER_PIN); // sensor connected through analog pins A0 - A5 i.e. digital pins 14-19  
unsigned int sensorValues[NUM_SENSORS];

void backward(unsigned int leftSpeed, unsigned int rightSpeed)
{
    digitalWrite(moR_ccw, HIGH);
    digitalWrite(moR_cw, LOW);
    analogWrite(pin_pwm_R,rightSpeed);
    
    digitalWrite(moL_cw, HIGH);
    digitalWrite(moL_ccw, LOW);
    analogWrite(pin_pwm_L, leftSpeed);
}

void forward(unsigned int leftSpeed, unsigned int rightSpeed)
{
    digitalWrite(moR_cw, HIGH);
    digitalWrite(moR_ccw, LOW);
    analogWrite(pin_pwm_R, rightSpeed);
    
    digitalWrite(moL_ccw, HIGH);
    digitalWrite(moL_cw, LOW);
    analogWrite(pin_pwm_L, leftSpeed);
}

void turn_right(unsigned int leftSpeed, unsigned int rightSpeed)
{
    digitalWrite(moL_cw, LOW) ;
    digitalWrite(moL_ccw, HIGH) ;
    analogWrite(pin_pwm_L  , leftSpeed);
    
    digitalWrite(moR_cw, LOW) ;
    digitalWrite(moR_ccw, HIGH) ;
    analogWrite(pin_pwm_R  , rightSpeed);
}

void  turn_STOP()
{
    //digitalWrite(moL_cw, LOW);
    //digitalWrite(moL_ccw, LOW);
    //digitalWrite(moR_cw, LOW);
    //digitalWrite(moR_ccw, LOW) ;
    digitalWrite(pin_pwm_R, LOW);
    digitalWrite(pin_pwm_L, LOW);
}

void  turn_left(unsigned int leftSpeed, unsigned int rightSpeed) 
{
    digitalWrite(moL_cw, HIGH);
    digitalWrite(moL_ccw, LOW);
    analogWrite(pin_pwm_L, leftSpeed);
    
    digitalWrite(moR_cw, HIGH );
    digitalWrite(moR_ccw, LOW );
    analogWrite(pin_pwm_R, rightSpeed);
}

void setup()
{
    unsigned int sensors[8];
    int positionS ; 

    //**************/
    pinMode(moL_cw, OUTPUT) ;
    pinMode(moL_ccw, OUTPUT) ;
    pinMode(pin_pwm_R, OUTPUT);
    
    pinMode(moR_cw, OUTPUT) ;
    pinMode(moR_ccw, OUTPUT) ;
    pinMode(pin_pwm_L, OUTPUT);
    
    pinMode(boton_1, INPUT);
    pinMode(boton_2, INPUT);
    
    pinMode(led_Red0, OUTPUT); //led1
    pinMode(led_Blue, OUTPUT); //led1
    pinMode(led_Green, OUTPUT); //led2
    
    Serial.begin(19200);
  
    int i;
    //====================Test LED ================
    ledRead_QTR_on();
    delay(500);
    
    ledRead_QTR_off();
    delay(500);
    
    ledRead_QTR_on();  
    //=============================================
 
    for (int i = 0; i < 50; i++)
    { 
        // calibrate for sometime by sliding the sensors across the line, 
        // or you may use auto-calibration instead
        // comment this part out for automatic calibration 

        // turn to the left and right to expose the sensors to the brightest and darkest 
        // readings that may be encountered
        if (i < 12 || i >= 38) 
            turn_left(calibrateSpeed,calibrateSpeed );   
        else
            turn_right(calibrateSpeed,calibrateSpeed); 
      
        qtrrc.calibrate();     
    }
    
    ledRead_QTR_off();
    turn_STOP();
  
    digitalWrite(led_Blue, LOW); //apagar sensores para indicar fin 
    delay(400); 
    
    digitalWrite(led_Blue,HIGH); //encender led 2 para indicar la
  
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print(qtrrc.calibratedMinimumOn[i]);
        Serial.print(' ');
    }
    
    Serial.println();
    //delay(5); 
    
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print(qtrrc.calibratedMaximumOn[i]);
        Serial.print(' ');
    }
     
    while(true) //true
    {
        int x = digitalRead(boton_2); //leemos y guardamos el valor
                                      // del boton en variable x
        delay(100);
           
        if(x==0) //si se presiona boton 
        {     
            digitalWrite(led_Blue,LOW); //indicamos que se presiono boton
            digitalWrite(led_Green,HIGH); //encendiendo led 1
            delay(100);
            break; //saltamos hacia el bucle principal
        }
    }

    ledRead_QTR_on();
    RUN_STOP = HIGH;
}

void ledRead_QTR_off()
{
    digitalWrite(led_Red0, HIGH); //apagar sensores para indicar fin  
}
void ledRead_QTR_on()
{
    digitalWrite(led_Red0, LOW); //apagar sensores para indicar fin 
}

int lastError = 0;

void loop()
{ 
    int val=1000,sensorValues0,sensorValues8;
   
    ////////////////////90 Deg////////////////     
    //===============ADD======================
    int position;
    unsigned int sensors[8];
    int position2 = qtrrc.readLine(sensors); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
    if ((position2 >= 1) && (position2 <= 7000))
    {
        position = position2;   
    }
    //===============ADD======================
  
    int error = position - 3500;
    int OUT_PWMA,OUT_PWMB;
    int motorSpeed = Kp * error + Kd * (error - lastError);
    lastError = error;
    int rightMotorSpeed = rightBaseSpeed + motorSpeed;
    int leftMotorSpeed = leftBaseSpeed - motorSpeed;

    if (rightMotorSpeed > rightMaxSpeed ) 
        rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  
    if (leftMotorSpeed > leftMaxSpeed ) 
        leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  
    if (rightMotorSpeed < 0) 
        rightMotorSpeed = rSpeed ; // keep the motor speed positive
  
    if (leftMotorSpeed < 0) 
        leftMotorSpeed = rSpeed ; // keep the motor speed positive
  
    if (position == 3500)
    {
        count_ERR++;
        //delay(1);
      
        if (count_ERR>= MAXcount_ERR)
        {
            RUN_STOP = LOW;
        }
    }
    else
    {
        count_ERR = 0;
    }

    if (RUN_STOP == HIGH)
    {
        if (rightMotorSpeed > 0)
        {
            digitalWrite(moR_cw, HIGH) ;
            digitalWrite(moR_ccw, LOW) ;
            analogWrite(pin_pwm_R,rightMotorSpeed );
        }
        else
        {
            digitalWrite(moR_cw, LOW) ;
            digitalWrite(moR_ccw, HIGH) ;
            analogWrite(pin_pwm_R,rightMotorSpeed*-1 );
        }
        
        if(leftMotorSpeed > 0)
        { 
            digitalWrite(moL_ccw, HIGH) ;
            digitalWrite(moL_cw, LOW) ;
            analogWrite(pin_pwm_L, leftMotorSpeed );
        }
        else
        {
            digitalWrite(moL_ccw, LOW) ;
            digitalWrite(moL_cw, HIGH) ;
            analogWrite(pin_pwm_L, leftMotorSpeed*-1 );
        }
    }
    else
    {
        sensorVal = digitalRead(boton_2);   
        while(sensorVal==HIGH)
        {
            sensorVal = digitalRead(boton_2);
            position = qtrrc.readLine(sensors); 
            Serial.println(position);
         
            digitalWrite(moL_cw, LOW) ;
            digitalWrite(moL_ccw, HIGH) ;
            analogWrite(pin_pwm_R, 0);
            
            digitalWrite(moR_cw, LOW) ;
            digitalWrite(moR_ccw, HIGH) ;
            analogWrite(pin_pwm_L, 0);  
        }
        RUN_STOP = HIGH;             
    }

    //================PRINT VAL====================
    //Serial.print(position);
    //Serial.print(' ');
    //Serial.print("LEFT=");
    //Serial.print(' '); 
    //Serial.print(leftMotorSpeed);
    //Serial.print(' '); 
    //Serial.print("RIGHT");
    //Serial.print(' '); 
    //Serial.print(rightMotorSpeed);
    //Serial.println(' ');
    // ================PRINT VAL====================
}
