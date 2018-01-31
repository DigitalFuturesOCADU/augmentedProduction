/*
 * Extended Uduino firmware v1
 * 
 * This extends the Uduino system by adding support for DC motor control using the Adafruit MotorShield
 * 
 */





#include<Uduino.h>
#include <AFMotor.h>
#include <Servo.h>



Uduino uduino("motorController");

int unityInputVals[3];

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

AF_DCMotor allDCmotors[] = {motor1,motor2,motor3,motor4};
#define MAXSERVOS 2

typedef struct _servoWrapper {
  int pin = -1;
  Servo servo;
  int pos;
  int getPin() {
    if (servo.attached()) return pin;
    else return false;
  }
  bool isActive() {
    if(pin == -1) return false;
    else return true;
  }
  bool attached() {
    return servo.attached();
  }
  void disable() {
    if (attached()) servo.detach();
    pin = -1;
  }
  void enable() {
    servo.attach(pin);
  }
  void update() {
    if (attached()) servo.write(pos);
  }
  bool lastPosition() {
    return servo.read();
  }
} ServoWrapper;

static ServoWrapper Servos[MAXSERVOS];



void setup() 
{
  Serial.begin(19200);
  uduino.addCommand("um", updateMotor);
  uduino.addCommand("a", WritePinAnalog);
  uduino.addCommand("s", SetMode);
  uduino.addDisconnectedFunction(DisconnectAllServos);
  uduino.addInitFunction(DisconnectAllServos);

}

void updateMotor()
{

//////////////////////////read values from Unity and save them into an array
char *fromUnity;
  for(int i=0;i<3;i++)
  {  
   fromUnity = uduino.next();
      if(fromUnity != NULL)
      {
      unityInputVals[i] = uduino.charToInt(fromUnity);
      }
  }
//////////////////////////read values from Unity and save them into an array
//motorNumber,directiontype,speed

    if(unityInputVals[0]<=4)
    {
    allDCmotors[(unityInputVals[0]-1)].run(unityInputVals[1]);
    allDCmotors[(unityInputVals[0]-1)].setSpeed(unityInputVals[2]);  
    }


}

void WritePinAnalog() {
  int pinToMap;
  char *arg;
  arg = uduino.next();
  if (arg != NULL)
  {
    pinToMap = atoi(arg);
  }

  int value;
  arg = uduino.next();
  if (arg != NULL)
  {
    value = atoi(arg);
    struct _servoWrapper* servo = getServoAttachedTo(pinToMap);
    if (servo != false && servo->isActive()) {
      servo->pos = value;
      servo->update();
    } else {
      analogWrite(pinToMap, value);
    }
  }
}



/* SERVO CODE */

ServoWrapper *getServoAttachedTo(int pin) {
  for (int i = 0; i < MAXSERVOS; i++) { // Check if it was already defined
    if (Servos[i].getPin() == pin) return &Servos[i];
  }
  return getAvailableServo();
}



ServoWrapper *getAvailableServo() {
  for (int i = 0; i < MAXSERVOS; i++) { // If it's not defined, get the first not active
    if (!Servos[i].isActive()) {
         return &Servos[i];
    }
  }
  // else overide the first one
  return false;
}



ServoWrapper *firstServoAttached() {
  unsigned int lastAttached = 0;
  for (int i = 0; i < MAXSERVOS; i++) {
    if (Servos[i].attached())
    lastAttached = i;
  }
  return &Servos[lastAttached];
}

void startServo(int pin) {
  struct _servoWrapper* servo = getServoAttachedTo(pin);
  servo->pin = pin;
  servo->enable();
}

void setServoPosition(struct _servoWrapper* servo, int pos) {
  servo->pos = pos;
}

int getServoPosition(struct _servoWrapper* servo, int pos) {
  return servo->lastPosition();
}

void DisconnectAllServos() {
  for (int i = 0; i < MAXSERVOS; i++) {
    Servos[i].disable();
  }
}

//
void SetMode() {
  int pinToMap;
  char *arg;
  arg = uduino.next();
  if (arg != NULL)
  {
    pinToMap = atoi(arg);
  }

  int type;
  arg = uduino.next();
  if (arg != NULL)
  {
    type = atoi(arg);
    PinSetMode(pinToMap, type);
  }
}
//
void PinSetMode(int pin, int type) {
  if (type != 4) getServoAttachedTo(pin)->disable();
  switch (type) {
    case 0: // Output
      pinMode(pin, OUTPUT);
      break;
    case 1: // PWM
      pinMode(pin, OUTPUT);
      break;
    case 2: // Analog
      pinMode(pin, INPUT);
      break;
    case 3: // Input_Pullup
      pinMode(pin, INPUT_PULLUP);
      break;
    case 4: // Servo
      startServo(pin);
      break;
  }
}
//

void loop() 
{
  // put your main code here, to run repeatedly:
  uduino.readSerial();
}





