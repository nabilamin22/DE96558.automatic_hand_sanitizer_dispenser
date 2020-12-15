//MICROCONTROLLER & INTERFACING LAB
//EEED253
//UNITEN
//AUTOMATIC HAND SANITIZER DISPENSER
//MUHAMMAD NABIL BIN SAIFUL AMIN (DE96558)
//THIS PROJECT AIMS TO USED THE ARDUINO UNO, ULTRASONIC DISTANCE SENSOR,
//AND SERVO MOTOR TO TAKE OUT THE SANITIZER'S FLUID WITHOUT NEED
//TO TOUCH THE APPLIANCES.
//A STRING WIRE WILL BE ATTACHED TO HAND SANITIZER CAP AND
//IT WILL BE PULLED BY THE SERVO

// include the library code
#include <LiquidCrystal.h>
#include<Servo.h>
#define pinServo 7

// INITIALIZE THE VARIABLES
LiquidCrystal lcd(12, 11, 3, 2, 1, 0);// initialize the library 
                                      //with the numbers of the 
                                      //interface pins
Servo S1;
int degree = 0;
long cm = 0;

//sensor to detect volume of hand sanitizers fluids
long sensordistance2 (int triggerMotion2, int echoMotion2)
{
 //CONFIGURE THE PIN
 pinMode (triggerMotion2, OUTPUT);//sets the trigger pin as output
 digitalWrite (triggerMotion2, LOW);//sets the trigger pin off
 delayMicroseconds (2);
 digitalWrite (triggerMotion2, HIGH);
 delayMicroseconds (10);
 digitalWrite (triggerMotion2, LOW);
 pinMode (echoMotion2, INPUT);//sets the echo pin as input
 return (pulseIn(echoMotion2, HIGH)*0.01723);
}

//sensor to detect the distance of the motion
long sensordistance (int triggerMotion, int echoMotion)
{
 //CONFIGURE THE PIN
 pinMode (triggerMotion, OUTPUT);//sets the trigger pin as output
 digitalWrite (triggerMotion, LOW);//sets the trigger pin off
 delayMicroseconds (2);
 digitalWrite (triggerMotion, HIGH);
 delayMicroseconds (10);
 digitalWrite (triggerMotion, LOW);
 pinMode (echoMotion, INPUT);//sets the echo pin as input
 return (pulseIn(echoMotion, HIGH)*0.01723);
}

//BEFORE PROJECT START
void setup() {
 lcd.begin(16, 2); // set up the LCD's number of columns and rows
 lcd.print("beware, CORONA!");// Display a message to the LCD.
 delay (4000);//delay 4 second
 lcd.clear();//clear any diplay
 lcd.print("stay safe!");
 delay (4000);
 lcd.clear();
 lcd.print("clean your hand!");
 delay (4000);
 lcd.clear();
 S1.attach(pinServo);
 Serial.begin (9600);//Sets the data rate in bits per second for 
                     //serial data 
 S1.write (0);//set servo to 0 degree
 delay (2000);
 pinMode (7, OUTPUT);
}

void loop() 
{
 cm = sensordistance ( 9, 8);//for sanitizers fluids
 if (cm > 20)
 {
  
  cm = sensordistance ( 5, 4);//for motion distance
  Serial.print(cm);
  Serial.println ("cm"); 
 //IF NO MOTION
  if (cm > 180) 
  {
   digitalWrite (7, LOW);//Servo motor will be turned off
   S1.write(0);
  }
  if (cm < 180)
  {
   //IF ANY MOTION IS DETECTED
   digitalWrite (7, HIGH);//Servo motor will be turned on
   S1.write(60);
   delay (500);
   S1.write(0);
   delay (3000);//Delay before next motion

  }
  delay (100);
  }
 else ;//if sanitizers fluids has run out
 {
 digitalWrite (7, LOW);
 S1.write(0);
 }
}

  
