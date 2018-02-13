/*
 * Servo movement using the keyframe model
 * 
 * Each servo has 2 arrays
 * s1TimeSequence - holds the time values for the keyframe in milliseconds
 * s1AngleSequence - holds the angle values for the keyframe
 * This works with the same logic as a timeline
 * 
 * You can add as many different time/angle keys as needed

 */

#include <Servo.h>

Servo servo1;
//***These arrays are the only thing that needs to be adjusted in the code
int s1TimeSequence[] = {  0, 1000, 3000, 6000}; //array that controls the timing of the servo movement
int s1AngleSequence[] = {10,  120,  180,   10};  //array with the corresponding angles
///These example values would set  @Time= 0Seconds,Angle=10 / @Time= 2seconds,Angle=120 / @Time= 4seconds,Angle=10  ,,The sequence loops when it reaches the end

int s1SeqNumber = 1;  //used to control playback through our array of times/direction
int s1Angle;
unsigned long s1SeqStart; //used for timing this servo


int startupDelay;

void setup() 
{
  servo1.attach(10);
  servo1.write(s1AngleSequence[0]);

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

//calculate the value for Servo 1 and write it
s1Angle = constrain(map((millis()-startupDelay),s1SeqStart,s1SeqStart+(s1TimeSequence[s1SeqNumber]-s1TimeSequence[s1SeqNumber-1]),s1AngleSequence[s1SeqNumber-1],s1AngleSequence[s1SeqNumber]),0,180);
servo1.write(s1Angle);


}
