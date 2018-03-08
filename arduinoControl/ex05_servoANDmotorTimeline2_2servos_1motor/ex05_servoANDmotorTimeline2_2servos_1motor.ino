/*
 * Servo movement using the keyframe model ***2 servos + 1 dc motor
 * 
 * 
 * Each servo has 2 arrays
 * s1TimeSequence - holds the time values for the keyframe in milliseconds
 * s1AngleSequence - holds the angle values for the keyframe
 * 
 * s2TimeSequence - holds the time values for the keyframe in milliseconds
 * s2AngleSequence - holds the angle values for the keyframe
 * 
 * 
 *  * Adafruit Motor Shield library
 * 
 * Using DC Motors, they are defined as either 1,2,3,4
 * .setSpeed() can be from 0 - 255
 * .run() cand be:  FORWARD 1 
 *                  BACKWARD 2
 *                  BRAKE 3
 *                  RELEASE 4
 * 
 * You can add as many different time/angle keys as needed

 */

#include <Servo.h>
#include <AFMotor.h>

Servo servo1;
//***These arrays are the only thing that needs to be adjusted in the code
int s1TimeSequence[] = {  0, 2000, 4000, 6000}; //array that controls the timing of the servo movement
int s1AngleSequence[] = {10,  140,  140, 10};  //array with the corresponding angles
int s1SeqNumber = 1;  //used to control playback through our array of times/direction
int s1Angle;
unsigned long s1SeqStart; //used for timing this servo


Servo servo2;
int s2TimeSequence[] = {  0, 2000, 2400, 2700, 6000}; //array that controls the timing of the motor movement
int s2AngleSequence[] = { 0,    0,  60,  0,    0};  //array with the corresponding commands on direction / stop
int s2SeqNumber = 1;  //used to control playback through our array of times/direction
int s2Angle;
unsigned long s2SeqStart;



int dc1MotorNumber = 2;  //set which motor is connected 1-4
int dc1MotorSpeed = 255; //set the speed

int dc1TimeSequence[] =      {0, 2000,  2500, 5000, 6000}; //array that controls the timing of the motor movement
int dc1DirectionSequence[] = {1,    4,     2,     4,   4};  //array with the corresponding commands on direction / stop
int dc1SeqNumber = 0;  //used to control playback through our array of times/direction
int dc1Direction;
unsigned long dc1SeqStart; //timer component used to store/compare timing values
AF_DCMotor motor1(dc1MotorNumber);

int startupDelay;

void setup() 
{
  
  //attach the servos to the correct pins
  servo1.attach(10);
  servo1.write(s1AngleSequence[0]);

  servo2.attach(9);
  servo2.write(s2AngleSequence[0]);
  

  delay(1000);//delay to allow the motor to reset to the start position
  
  startupDelay = millis(); //used to adjust to timing to account for startup delay
}

void loop() 
{
    /////timer for controlling Servo 1
  if((millis()-startupDelay)-s1SeqStart>=(s1TimeSequence[s1SeqNumber]-s1TimeSequence[s1SeqNumber-1]))
  {
      if((s1SeqNumber+1)<(sizeof(s1TimeSequence)/sizeof(int)))
      {
        s1SeqNumber++;
      }
  
      else
      {
        s1SeqNumber=1;
      }
  
    s1SeqStart = (millis()-startupDelay);
  }

  /////timer for controlling Servo 2
  if((millis()-startupDelay)-s2SeqStart>=(s2TimeSequence[s2SeqNumber]-s2TimeSequence[s2SeqNumber-1]))
  {
    if((s2SeqNumber+1)<(sizeof(s2TimeSequence)/sizeof(int)))
    {
      s2SeqNumber++;
    }

    else
    {
      s2SeqNumber=1;
    }

  s2SeqStart = (millis()-startupDelay);
  }

//timer for controlling the DC motor
if((millis()-startupDelay)-dc1SeqStart>=(dc1TimeSequence[dc1SeqNumber]-dc1TimeSequence[dc1SeqNumber-1]))
{
    if((dc1SeqNumber+1)<(sizeof(dc1TimeSequence)/sizeof(int)))
    {
      dc1SeqNumber++;
    }

    else
    {
      dc1SeqNumber=1;
    }

  dc1SeqStart = (millis()-startupDelay);
}
  

//calculate the value for Servo 1 and write it
s1Angle = constrain(map((millis()-startupDelay),s1SeqStart,s1SeqStart+(s1TimeSequence[s1SeqNumber]-s1TimeSequence[s1SeqNumber-1]),s1AngleSequence[s1SeqNumber-1],s1AngleSequence[s1SeqNumber]),0,180);
servo1.write(s1Angle);

//calculate the value for Servo 2 and write it
s2Angle = constrain(map((millis()-startupDelay),s2SeqStart,s2SeqStart+(s2TimeSequence[s2SeqNumber]-s2TimeSequence[s2SeqNumber-1]),s2AngleSequence[s2SeqNumber-1],s2AngleSequence[s2SeqNumber]),0,180);
servo2.write(s2Angle);

//apply the correct value to the DC motor
motor1.setSpeed(dc1MotorSpeed);
motor1.run(dc1DirectionSequence[dc1SeqNumber-1]);

}
