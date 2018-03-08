/*
 * Servo movement using the keyframe model ***2 servos
 * 
 * 
 * Each servo has 2 arrays
 * s1TimeSequence - holds the time values for the keyframe in milliseconds
 * s1AngleSequence - holds the angle values for the keyframe
 * 
 * s2TimeSequence - holds the time values for the keyframe in milliseconds
 * s2AngleSequence - holds the angle values for the keyframe
 * 
 * You can add as many different time/angle keys as needed

 */

#include <Servo.h>

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


  

//calculate the value for Servo 1 and write it
s1Angle = constrain(map((millis()-startupDelay),s1SeqStart,s1SeqStart+(s1TimeSequence[s1SeqNumber]-s1TimeSequence[s1SeqNumber-1]),s1AngleSequence[s1SeqNumber-1],s1AngleSequence[s1SeqNumber]),0,180);
servo1.write(s1Angle);

//calculate the value for Servo 2 and write it
s2Angle = constrain(map((millis()-startupDelay),s2SeqStart,s2SeqStart+(s2TimeSequence[s2SeqNumber]-s2TimeSequence[s2SeqNumber-1]),s2AngleSequence[s2SeqNumber-1],s2AngleSequence[s2SeqNumber]),0,180);
servo2.write(s2Angle);

}
