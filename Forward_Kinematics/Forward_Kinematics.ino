#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
//0 position
int currentpos = 0;
//Config position
int nextpos1 = 20;
int nextpos2 = 10;
int nextpos3 = 25;
int nextpos4 = 35;
//Delay servo
int delayTime = 10;

void setup() {
  Serial.begin(9600);
  servo1.attach(A0);  
  servo2.attach(A1);
  servo3.attach(A2);
  servo4.attach(A4);
  Serial.print("\n");
  Serial.println("Program Start");
  //Reset position
  servo1.write(currentpos + 90);
  servo2.write(currentpos);
  servo3.write(currentpos);
  servo4.write(currentpos);
}

void loop() {
  Forward_Kinematics();
  move_position();
  OpsiExit();
}

void Forward_Kinematics() {
  //int to float
  float pos1 = nextpos1;
  float pos2 = nextpos2;
  float pos3 = nextpos3;
  float pos4 = nextpos4;
  Serial.print("\n");
  Serial.println("Forward Kinematics");
  //convert angular degrees
  float theta1 = (pos1 * 22)/(7 * 180);
  float theta2 = (pos2 * 22)/(7 * 180);
  float theta3 = (pos3 * 22)/(7 * 180);
  float theta4 = (pos4 * 22)/(7 * 180);
  //forward kinematics
  float result1 = 5 * cos(theta1) * cos(theta2) * cos(theta3) + 
    5 * cos(theta1) * cos(theta2) - 5 * cos(theta1) * 
    sin(theta2) * sin (theta3) + 9 * cos(theta4) * (cos(theta1) * 
    cos(theta2) * cos(theta3) - cos(theta1) * sin(theta2) * sin(theta3))
    + 9 * sin(theta4) * (-cos(theta1) * cos(theta2) * sin(theta3) 
    -cos(theta1) * sin(theta2) * cos(theta3));
  float result2 = 5 * sin(theta1) * cos(theta2) * cos(theta3) + 
    5 * sin(theta1) * cos(theta2) - 5 * sin(theta1) * 
    sin(theta2) * sin (theta3) + 9 * cos(theta4) * (sin(theta1) * 
    cos(theta2) * cos(theta3) - sin(theta1) * sin(theta2) * sin(theta3))
    + 9 * sin(theta4) * (-sin(theta1) * cos(theta2) * sin(theta3)
    -sin(theta1) * sin(theta2) * cos(theta3));
  float result3 = 5 * sin(theta2) * cos(theta3) + 5 * sin(theta2) + 
    9 * cos(theta4) * (sin(theta2) * cos(theta3) + cos(theta2) * 
    sin(theta3)) + 9 * sin(theta4) * (cos(theta2) * cos(theta3) - 
    sin(theta2) * sin(theta3)) + 5 * cos(theta2) * sin(theta3);
  Serial.print("\n");
  Serial.print("Result of x: "); Serial.print(result3); Serial.println(" cm");
  Serial.print("Result of y: "); Serial.print(result2); Serial.println(" cm");
  Serial.print("Result of z: "); Serial.print(result1 + 5); Serial.println(" cm");
}

void OpsiExit() {
  Serial.print("\n");
  Serial.println("Exit menu");
  Serial.println("Input '1' to exit");
  while (Serial.available() == 0) {
  }
  String teststr = Serial.readString();
  teststr.trim();
  if (teststr == "1") {
    Serial.print("\n");
    Serial.println("Exiting Program");
    reset();
  } 
  else {
    Serial.print("\n");
    Serial.println("Back to menu exit");
    OpsiExit();
  }
}

void move_position() {
  moveServoSmoothly(servo1, currentpos + 90, nextpos1 + 90);
  delay(700);
  moveServoSmoothly(servo2, currentpos, nextpos2);
  delay(700);
  moveServoSmoothly(servo3, currentpos, nextpos3);
  delay(700);
  moveServoSmoothly(servo4, currentpos, nextpos4);
}

void reset() {
  delay(700);
  moveServoSmoothly(servo1, nextpos1 + 90, currentpos + 90);
  delay(700);
  moveServoSmoothly(servo2, nextpos2, currentpos);
  delay(700);
  moveServoSmoothly(servo3, nextpos3, currentpos);
  delay(700);
  moveServoSmoothly(servo4, nextpos4, currentpos);
  delay(700);
  exit(0);
}

void moveServoSmoothly(Servo servo, int currentPosition, int targetPosition) {
  if (currentPosition < targetPosition) {
    for (int pos = currentPosition; pos <= targetPosition; pos+=1) {
      servo.write(pos);
      delay(delayTime);
    }
  }
  else {
    for (int pos = currentPosition; pos >= targetPosition; pos-=1) {
      servo.write(pos);
      delay(delayTime);
    }
  }
}