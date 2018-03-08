/*Stepper motor examples using the Adafruit motorshiel
 * 
 * uses a modified AccelStepper library: https://github.com/adafruit/AccelStepper
 * Libray guide:  http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a4f0989d0ae264e7eadfe1fa720769fb6
 * 
 * step sequence
 * 
 * 
 * 
 */



#include <AccelStepper.h>
#include <AFMotor.h>

AF_Stepper motor2(20, 2);  //inputs: number of steps on the motor,  motornumber
float m2MaxSpeed = 200;  //this changes per motor + means clockwis - means counterclockwise
float m2accel = 100;

int stepTargets[] = {300,-500, 1000, -20}; //where to step to/from
int targetCount = 0;

//set up the Accel library to work with the motor shield
void forwardstep2() 
{  
  motor2.onestep(FORWARD, SINGLE); ///Options:  SINGLE, DOUBLE, INTERLEAVE, MICROSTEP
}
void backwardstep2() {  
  motor2.onestep(BACKWARD, SINGLE); ///Options:  SINGLE, DOUBLE, INTERLEAVE, MICROSTEP
}

AccelStepper stepper2(forwardstep2, backwardstep2);
///

void setup() 
{
stepper2.setMaxSpeed(m2MaxSpeed);
stepper2.setAcceleration(m2accel);
stepper2.moveTo(stepTargets[targetCount]);
}

void loop() 
{

  if (stepper2.distanceToGo() == 0) //check how far it is from the target, if 0 changes
  {
    if(targetCount + 1 <(sizeof(stepTargets)/sizeof(int)))
    {
      targetCount++;
    }
    else
    {
      targetCount = 0;
    }
    stepper2.moveTo(stepTargets[targetCount]);  //flip the direction
    
  }



stepper2.run();
}
