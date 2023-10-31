//TODO: finish servo code
#include <Servo.h>

  // Servo pin intialization
int baseServoPin = A0; // Analog0
int lowerServoPin1 = 5; //Analog1
int lowerServoPin2 = 6;
int upperServoPin1 = A1; // Analog2
int upperServoPin2 = A2;
int rightSticksPin = A3; // Analog3
int leftSticksPin = A4; // Analog4
int stabilizingServoPin = A5; // Analog3
// Motor initialization
int leftMotorsPin1 = 13;
int leftMotorsPin2 = 12;
int rightMotorsPin1 = 8;
int rightMotorsPin2 = 7;
// Pulse width
int pulseWidth = 11;
//light pins
int ledSpotlight = 1;
int lights = 2;
//other variables
char key;
int speed = 255; // half the max signal
int state; //driving = 0, rescuing = 1
int armState = 0;
int additionalAngle;

// Servo initialization
Servo upperArmServo1;
Servo upperArmServo2;
Servo lowerArmServo1;
Servo lowerArmServo2;
Servo rightStickServo;
Servo leftStickServo;
Servo stabilizingServo;
Servo baseServoRotate;

//Servo locations;
int currPosUpArm;
int currPosLowArm;
int currPosStableServo;
int currPosRightStick;
int currPosLeftStick;
int currPosBase;

void setup() {
  Serial1.begin(115200);

  //setup pins for lights and motors
  pinMode(leftMotorsPin1, OUTPUT);
  pinMode(rightMotorsPin1, OUTPUT);
  pinMode(leftMotorsPin2, OUTPUT);
  pinMode(rightMotorsPin2, OUTPUT);
  pinMode(ledSpotlight, OUTPUT);
  pinMode(lights, OUTPUT);
  pinMode(pulseWidth, OUTPUT);

  // setup Servos
  baseServoRotate.attach(baseServoPin);
  upperArmServo1.attach(upperServoPin1);
  upperArmServo2.attach(upperServoPin2);
  lowerArmServo1.attach(lowerServoPin1);
  lowerArmServo2.attach(lowerServoPin2);
  rightStickServo.attach(rightSticksPin);
  leftStickServo.attach(leftSticksPin);
  stabilizingServo.attach(stabilizingServoPin);

  //test the outputs
  initServo();
//  test();

  //final setup
  digitalWrite(ledSpotlight, HIGH);
  state = 1; //set default state to driving

}

void loop() {
    
    // read input
    if (Serial1.available() > 0) {
      key = Serial1.read();
      //maintainServos();
      
      if (state == 0) { // check whether the machine is in driving state
        // driving
        digitalWrite(lights, HIGH); // turn on all LEDs
        // branch to the corresponding method if a key is pressed
        if (key == 'w') {
          forward();
        }else if (key == 'x'){
          stop();
        } else if (key == 's') {
          back();
        } else if (key == 'a') {
          left();
        } else if (key == 'd') {
          right();
        } else if (key == 'q') {
          sharpLeft();
        } else if (key == 'e') {
          sharpRight();
        } else if (key == 'z') {
          backLeft();
        } else if (key == 'c') {
          backLeft();
        } else if (key == '1') {
          setSpeed(64);
        } else if (key == '2') {
          setSpeed(127);
        } else if (key == '3') {
          setSpeed(191);
        } else if (key == '4') {
          setSpeed(255);
        } else { // if no key is pressed stop all motors
          stop();
        }

        if (key == "p") { // if spacebar is pressed change the state of the machine to move the arm
          changeState(1);
        }
      }

      if (state == 1) { // check whether the machine is in the rescuing state
        // saving
        // check which key is pressed and call the corresponding method
        int slowServoDelay = 100;
        int standardServoDelay = 75;
        int fastServoDelay = 25;
        if (key == 't') {
          lowerArmUp(standardServoDelay);
        } else if (key == 'g') {
          lowerArmDown(standardServoDelay);
        }else if (key == 'x'){
          stop();
        }else if (key == 'h') {
          baseRotateRight(standardServoDelay);
        } else if (key == 'f') {
          baseRotateLeft(standardServoDelay);
        } else if (key == 'u') {
          upperArmUp(standardServoDelay);
        } else if (key == 'j') {
          upperArmDown(standardServoDelay);
        } else if (key == 'KP_END') {
          stabilizingServoUp(standardServoDelay);
        } else if (key == 'KP_3') {
          stabilizingServoDown(standardServoDelay);
        } else if (key == 'KP_HOME') {
          leftStickRight(standardServoDelay);
        } else if (key == 'KP_LEFTARROW') {
          leftStickLeft(standardServoDelay);
        } else if (key == 'KP_PGUP') {
          rightStickLeft(standardServoDelay);
        } else if (key == 'KP_RIGHTARROW') {
          rightStickRight(standardServoDelay);
        } else { // if no key is pressed stop all servos
          initServo();
        }

        if (key == "p") { // if spacebar is pressed change to the moving state
          state = 0;
        }
        if (key == 'r') {
          if (armState == 1) {
            armState = 0;
          } else {
            armState = 1;
          }
        }
      }

    }
  }
  // tests all the moving features of the machine
void test() {
  //testMotor();
}

void testMotor(){
  forward();
  delay(5000);
  right();
  delay(3000);
  left();
  delay(3000);
  left();
  delay(3000);
  sharpLeft();
  delay(3000);
  stop();
}

// tests the different movements on the arm individually for 150ms each
void testArm() {
  int slowServoDelay = 100;
  int standardServoDelay = 75;
  int fastServoDelay = 25;

  initServo();

  for (int i = currPosBase; i < 135; i++) {
    maintainServos();
    baseRotateRight(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosBase; i < 135; i++) {
    maintainServos();
    baseRotateLeft(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosLowArm; i < 135; i++) {
    maintainServos();
    lowerArmUp(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosLowArm; i < 135; i++) {
    maintainServos();
    lowerArmDown(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosUpArm; i < 135; i++) {
    maintainServos();
    upperArmUp(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosUpArm; i < 135; i++) {
    maintainServos();
    upperArmDown(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosStableServo; i < 135; i++) {
    maintainServos();
    stabilizingServoUp(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosStableServo; i < 45; i++) {
    maintainServos();
    stabilizingServoDown(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosRightStick; i < 45; i++) {
    maintainServos();
    rightStickRight(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosRightStick; i < 45; i++) {
    maintainServos();
    rightStickLeft(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosLeftStick; i < 45; i++) {
    maintainServos();
    leftStickRight(standardServoDelay);
    delay(150);
  }
  initServo();

  for (int i = currPosLeftStick; i < 45; i++) {
    maintainServos();
    leftStickLeft(standardServoDelay);
    delay(150);
  }
  initServo();
}

// move forwards by turning on the forward motors and assigning them the set speed
void forward() {
  digitalWrite(leftMotorsPin1, HIGH);
  digitalWrite(leftMotorsPin2, LOW);
  digitalWrite(rightMotorsPin1, HIGH);
  digitalWrite(rightMotorsPin2, LOW);
  analogWrite(pulseWidth, speed);
  delay(10);
  resetChar();
}

// move backwards by turning on the reverse motors and assigning them the set speed
void back() {
    digitalWrite(leftMotorsPin1, LOW);
    digitalWrite(leftMotorsPin2, HIGH);
    digitalWrite(rightMotorsPin1, LOW);
    digitalWrite(rightMotorsPin2, HIGH);
    analogWrite(pulseWidth, speed);
    delay(10);
    resetChar();
  }
  // move to the left by turning on the right motors and assigning them the set speed
void left() {
    digitalWrite(leftMotorsPin1, LOW);
    digitalWrite(leftMotorsPin2, LOW);
    digitalWrite(rightMotorsPin1, HIGH);
    digitalWrite(rightMotorsPin2, LOW);
    analogWrite(pulseWidth, speed);
    delay(10);
    resetChar();
  }
  // move to the right by turning on the left motors and assigning them the set speed
void right() {
  digitalWrite(leftMotorsPin1, HIGH);
  digitalWrite(leftMotorsPin2, LOW);
  digitalWrite(rightMotorsPin1, LOW);
  digitalWrite(rightMotorsPin2, LOW);
  analogWrite(pulseWidth, speed);
  delay(10);
  resetChar();
}

// take a sharp left by turning on the right forward motors and the left reverse motors and assigning them the set speed
void sharpLeft() {
  digitalWrite(leftMotorsPin1, LOW);
  digitalWrite(leftMotorsPin2, HIGH);
  digitalWrite(rightMotorsPin1, HIGH);
  digitalWrite(rightMotorsPin2, LOW);
  analogWrite(pulseWidth, speed);
  delay(10);
  resetChar();
}

// take a sharp right by turning on the left forward motors and the right reverse motors and assigning them the set speed
void sharpRight() {
  digitalWrite(leftMotorsPin1, HIGH);
  digitalWrite(leftMotorsPin2, LOW);
  digitalWrite(rightMotorsPin1, LOW);
  digitalWrite(rightMotorsPin2, HIGH);
  analogWrite(pulseWidth, speed);
  delay(10);
  resetChar();
}

// move to the left in reverse by turning on the right reverse motors and assigning them the set speed
void backLeft() {
  digitalWrite(leftMotorsPin1, LOW);
  digitalWrite(leftMotorsPin2, LOW);
  digitalWrite(rightMotorsPin1, LOW);
  digitalWrite(rightMotorsPin2, HIGH);
  analogWrite(pulseWidth, speed);
  delay(10);
  resetChar();
}

// move to the right in reverse by turning on the left reverse motors and assigning them the set speed
void backRight() {
  digitalWrite(leftMotorsPin1, LOW);
  digitalWrite(leftMotorsPin2, HIGH);
  digitalWrite(rightMotorsPin1, LOW);
  digitalWrite(rightMotorsPin2, LOW);
  analogWrite(pulseWidth, speed);
  delay(10);
  resetChar();
}

// stop all motors by turning them all off
void stop() {
  digitalWrite(leftMotorsPin1, LOW);
  digitalWrite(leftMotorsPin2, LOW);
  digitalWrite(rightMotorsPin1, LOW);
  digitalWrite(rightMotorsPin2, LOW);
  upperArmServo1.write(currPosUpArm);
  upperArmServo2.write(currPosUpArm);
  lowerArmServo1.write(currPosLowArm);
  lowerArmServo2.write(currPosLowArm);
  baseServoRotate.write(currPosBase);
  stabilizingServo.write(currPosStableServo);
  leftStickServo.write(currPosLeftStick);
  rightStickServo.write(currPosRightStick);
}

// SERVOS 

void initServo() {

  currPosUpArm = 90;
  currPosLowArm = 90;
  currPosStableServo = 90;
  currPosRightStick = 90;
  currPosLeftStick = 90;
  currPosBase = 90;

  upperArmServo1.write(currPosUpArm);
  upperArmServo2.write(currPosUpArm);
  lowerArmServo1.write(currPosLowArm);
  lowerArmServo2.write(currPosLowArm);
  baseServoRotate.write(currPosBase);
  stabilizingServo.write(currPosStableServo);
  leftStickServo.write(currPosLeftStick);
  rightStickServo.write(currPosRightStick);

}

void findAngle(String position) {
  double angleX;

  double lengthLower = 15;
  double lengthUpper = 15;
  double lengthHypo = sqrt(pow(lengthLower, 2) + pow(lengthUpper, 2));
  double angleUppLow = currPosUpArm + additionalAngle;
  double angleLowHypo = cos(angleUppLow) / lengthHypo;
  double angleUppHypo = 180 - (angleUppLow + angleLowHypo);
  double angleLowGround = currPosLowArm;
  double angleGroundHypo = angleLowGround - angleLowHypo;

  if (position == 'Over') {
    double angleHypoPerp = 180 - (angleGroundHypo + 90);
    double angleUppPerp = 180 - (angleHypoPerp + angleUppHypo);
    angleX = 90 - angleUppPerp;
  } else {
    angleX = 90 - angleGroundHypo;
  }
  currPosStableServo = angleX;
  stabilizingServo.write(angleX);

}

// Keep the upper and stabilizing servo up to keep them at their position.
void maintainServos() {
  /*
  upperArmServo1.write(currPosUpArm);
  upperArmServo2.write(currPosUpArm);
  */
  
  stabilizingServo.write(currPosStableServo);

  /*
  lowerArmServo1.write(currPosUpArm);       
  lowerArmServo2.write(currPosUpArm);
  */
}

// move the upper arm up
void upperArmUp(int servoDelay) {

  int pos = currPosUpArm;
  if (pos < 180) {
    upperArmServo1.write(pos); // tell servo to go to position in variable 'pos'
    upperArmServo2.write(pos);
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosUpArm = pos; // save the current location of the servo
  resetChar();
}

// move the upper arm down
void upperArmDown(int servoDelay) {
  int pos = currPosUpArm;
  if (pos > 0) {
    upperArmServo1.write(pos); // tell servo to go to position in variable 'pos'
    upperArmServo2.write(pos);
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosUpArm = pos; // save the current location of the servo
  resetChar();
}

// move the lower arm up
void lowerArmDown(int servoDelay) {
  int pos = currPosLowArm;
  if (pos < 180) {
    lowerArmServo1.write(180 - pos); // tell servo to go to position in variable 'pos'
    lowerArmServo2.write(pos);
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosLowArm = pos; // save the current location of the servo
  resetChar();
}

// move the lower arm down
void lowerArmUp(int servoDelay) {
  int pos = currPosLowArm;
  if (pos > 0) {
    lowerArmServo1.write(pos); // tell servo to go to position in variable 'pos'
    lowerArmServo2.write(180 - pos);
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosLowArm = pos; // save the current location of the servo
  resetChar();
}

// move the stabiling Servo up
void stabilizingServoUp(int servoDelay) {
  int pos = currPosStableServo;
  if (pos < 180) {
    stabilizingServo.write(pos); // tell servo to go to position in variable 'pos'
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosStableServo = pos; // save the current location of the servo
  resetChar();
}

// move the stabilizing servo down
void stabilizingServoDown(int servoDelay) {
  int pos = currPosStableServo;
  if (pos > 0) {
    stabilizingServo.write(pos); // tell servo to go to position in variable 'pos'
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosStableServo = pos; // save the current location of the servo
  resetChar();
}

// move the right sticks to the right
void rightStickRight(int servoDelay) {
  int pos = currPosRightStick;
  if (pos < 180) {
    rightStickServo.write(pos); // tell servo to go to position in variable 'pos'
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosRightStick = pos; // save the current location of the servo
  resetChar();
}

// move the right sticks to the left
void rightStickLeft(int servoDelay) {
  int pos = currPosRightStick;
  if (pos > 0) {
    rightStickServo.write(pos); // tell servo to go to position in variable 'pos'
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosRightStick = pos; // save the current location of the servo
  resetChar();
}

// move the left sticks to the right
void leftStickRight(int servoDelay) {
  int pos = currPosLeftStick;
  if (pos < 180) {
    leftStickServo.write(pos); // tell servo to go to position in variable 'pos'
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosLeftStick = pos; // save the current location of the servo
  resetChar();
}

// move the left sticks to the left
void leftStickLeft(int servoDelay) {
  int pos = currPosLeftStick;
  if (pos > 0) {
    leftStickServo.write(pos); // tell servo to go to position in variable 'pos'
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosLeftStick = pos; // save the current location of the servo
  resetChar();
}

// move the base servo to the right
void baseRotateRight(int servoDelay) {
    int pos = currPosBase;
    if (pos > 0) {
      baseServoRotate.write(pos); // tell servo to go to position in variable 'pos'
      delay(servoDelay);
      pos++;
    }
    if (armState == 1 && currPosStableServo > 90) {
      findAngle("Over"); //TO BE DETERMINED
    } else if (armState == 1 && currPosStableServo <= 90) {
      findAngle("Under"); //TO BE DETERMINED
    }
    currPosBase = pos; // save the current location of the servo
    resetChar();
  }
  // move the base servo to the left
void baseRotateLeft(int servoDelay) {
  int pos = currPosBase;
  if (pos < 180) {
    baseServoRotate.write(pos); // tell servo to go to position in variable 'pos'
    delay(servoDelay);
    pos++;
  }
  if (armState == 1 && currPosStableServo > 90) {
    findAngle("Over"); //TO BE DETERMINED
  } else if (armState == 1 && currPosStableServo <= 90) {
    findAngle("Under"); //TO BE DETERMINED
  }
  currPosBase = pos; // save the current location of the servo
  resetChar();
}

// reset the character in order to avoid a movement to continue when the key is unpressed
void resetChar() {
  key = "m";
}

// changes the initial speed to a new speed
void setSpeed(int newSpeed) {
  speed = newSpeed;
}

void changeState(int newstate){
  state = newstate;
}
