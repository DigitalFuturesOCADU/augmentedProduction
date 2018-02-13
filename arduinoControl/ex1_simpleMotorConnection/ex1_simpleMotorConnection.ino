/*
 * Basic DC motor test using the Motor shield
 * 
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
 * 
 */

#include <AFMotor.h>
int motorNumber = 2;  //set which motor is connected 1-4
int motorSpeed = 255; //set the speed



AF_DCMotor motor1(motorNumber);
 



void setup() 

{
  motor1.setSpeed(motorSpeed);
  
}

void loop() 
{

  
motor1.run(FORWARD);

  

}
