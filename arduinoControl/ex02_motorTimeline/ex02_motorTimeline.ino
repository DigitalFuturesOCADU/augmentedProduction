/*
 * Basic DC motor test using the Motor shield
 * 
 * movement timeline using a timer/array
 * 
 * Install the Library through the Library Manager
 * 
 * Adafruit Motor Shield library
 * 
 * Using DC Motors, they are defined as either 1,2,3,4
 * .setSpeed() can be from 0 - 255
 * .run() cand be:  FORWARD 1 
 *                  BACKWARD 2
 *                  BRAKE 3
 *                  RELEASE 4
 * 
 * This simple example uses a timer move forward , pause, move backward, 
 */

#include <AFMotor.h>
int motorNumber = 2;  //set which motor is connected 1-4
int motorSpeed = 255; //set the speed

int timeSequence[] = {1000,200,3000,2000}; //array that controls the timing of the motor movement
int directionSequence[] = {1,4,2,4};  //array with the corresponding commands on direction / stop
int seqNumber = 0;  //used to control playback through our array of times/direction

unsigned long lastChange; //timer component used to store/compare timing values


AF_DCMotor motor1(motorNumber);
 



void setup() 

{
  motor1.setSpeed(motorSpeed);
  
}

void loop() 
{

  
 if(millis()-lastChange>=timeSequence[seqNumber])   //basic timer function. Subtract the value of the last sequence change from the current to see if it should switch
 {
    if((seqNumber+1)<(sizeof(timeSequence)/sizeof(int)))  //should we increment through the array or go back to the begining? uses the sizeof funcition to measure length of the array
    {
      seqNumber++;
    }
    else
    {
      seqNumber = 0;
    }

  lastChange = millis(); //save this time into the lastChange variable
 }


motor1.run(directionSequence[seqNumber]);

  

}
