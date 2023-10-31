int leftMotorsPin1 = 3;
int leftMotorsPin2 = 5;
int rightMotorsPin1 = 6;
int rightMotorsPin2 = 9;

char key;
int speed = 127;

void setup(){
	pinmode(leftMotorsPin1, OUTPUT);
	pinmode(rightMotorsPin1, OUTPUT);
	pinmode(leftMotorsPin2, OUTPUT);
	pinmode(rightMotorsPin2, OUTPUT);
	Serial.begin(9600); //begin serial communication at 9600bps
}

void loop(){

	if(Serial.available()){
		key = Serial.read();

		if(key == 'w'){
				forward();
			}else if(key == 's'){
				back();
			}else if(key == 'a'){
				left();
			}else if(key == 'd'){
				right();
			}else if(key == 'q'){
				sharpLeft();
			}else if(key == 'e'){
				sharpRight();
			}else if(key == 'z'){
				backLeft();
			}else if(key == 'c'){
				backLeft();
			}else{// if no key is pressed stop all motors
				stop();
			}

	}
}

void forward(){
 	analogWrite(leftMotorsPin1, speed);
 	analogWrite(leftMotorsPin2, 0);
 	analogWrite(rightMotorsPin1, speed);
 	analogWrite(rightMotorsPin2, 0);
 	delay(10);
 	resetChar();
}

// move backwards by turning on the reverse motors and assigning them the set speed
void back(){
 	analogWrite(leftMotorsPin1, 0);
 	analogWrite(leftMotorsPin2, speed);
 	analogWrite(rightMotorsPin1, 0);
 	analogWrite(rightMotorsPin2, speed);
 	delay(10);
 	resetChar();
}
// move to the left by turning on the right motors and assigning them the set speed
void left(){
 	analogWrite(leftMotorsPin1, 0);
 	analogWrite(leftMotorsPin2, 0);
 	analogWrite(rightMotorsPin1, speed);
 	analogWrite(rightMotorsPin2, 0);
 	delay(10);
 	resetChar();
 }
// move to the right by turning on the left motors and assigning them the set speed
void right(){
  	analogWrite(leftMotorsPin1, speed);
 	analogWrite(leftMotorsPin2, 0);
 	analogWrite(rightMotorsPin1, 0);
 	analogWrite(rightMotorsPin2, 0);
 	delay(10);
 	resetChar();
}

// take a sharp left by turning on the right forward motors and the left reverse motors and assigning them the set speed
void sharpLeft(){
 	analogWrite(leftMotorsPin1, 0);
 	analogWrite(leftMotorsPin2, speed);
 	analogWrite(rightMotorsPin1, speed);
 	analogWrite(rightMotorsPin2, 0);
 	delay(10);
 	resetChar();
}

// take a sharp right by turning on the left forward motors and the right reverse motors and assigning them the set speed
void sharpRight(){
 	analogWrite(leftMotorsPin1, speed);
 	analogWrite(leftMotorsPin2, 0);
 	analogWrite(rightMotorsPin1, 0);
 	analogWrite(rightMotorsPin2, speed);
 	delay(10);
 	resetChar();
}

// move to the left in reverse by turning on the right reverse motors and assigning them the set speed
void backLeft(){
	analogWrite(leftMotorsPin1, 0);
 	analogWrite(leftMotorsPin2, 0);
 	analogWrite(rightMotorsPin1, 0);
 	analogWrite(rightMotorsPin2, speed);
 	delay(10);
 	resetChar();
}

// move to the right in reverse by turning on the left reverse motors and assigning them the set speed
void backRight(){
 	analogWrite(leftMotorsPin1, 0);
 	analogWrite(leftMotorsPin2, speed);
 	analogWrite(rightMotorsPin1, 0);
 	analogWrite(rightMotorsPin2, 0);
 	delay(10);
 	resetChar();
}

// stop all motors by turning them all off
void stop(){
   	analogWrite(leftMotorsPin1, 0);
 	analogWrite(leftMotorsPin2, 0);
 	analogWrite(rightMotorsPin1, 0);
 	analogWrite(rightMotorsPin2, 0);
}

void resetChar(){
 	key = "m";
}