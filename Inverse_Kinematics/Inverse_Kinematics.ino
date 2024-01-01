#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
//0 position
float currentpos = 0;
//robot length
float link1 = 5;
float link2 = 5;
float link3 = 5;
float link4 = 9;
//Config position
float x = 10;
float y = 8;
float z = 10;
//Delay servo
float delayTime = 10;

void setup() {
  Serial.begin(9600);
  servo1.attach(A0);  
  servo2.attach(A1);
  servo3.attach(A2);
  servo4.attach(A4);
  Serial.print("\n");
  Serial.println("Program Start");
  //Position reset
  servo1.write(currentpos + 90);
  servo2.write(currentpos);
  servo3.write(currentpos);
  servo4.write(currentpos);
}

void loop() {
  Inverse_Kinematics();
}

void Inverse_Kinematics() {
  //Input the value from x,y,z
  float coorx = x;
  float coory = y;
  float coorz = z;
  //float theta (except base)
  float theta1 = atan(coory/coorx);
  float t1 = (theta1*180)/3.14; //Theta parameter1
  float theta2 = 0;
  float theta3 = 0;
  float theta4 = 0;
  //End effector range
  float totalE = sqrt(sq(coorx)+sq(coory));
  //end effector coordinates (z3) with base (r)
  float r3 = totalE;
  float z3 = link2 + link3 + link4;
  //inverse kinematics
  float totalTheta = theta2 + theta3 + theta4; //total angle theta 2-4
  float r2 = r3 - link4 * cos(totalTheta);
  float z2 = z3 - link4 * sin(totalTheta);
  //theta 3 
  float cosT3 = (sq(r2) + sq(z2) - (sq(link2) + sq(link3))) / (2 * link2 * link3);
  float rad3 = (cosT3 * 3.14)/(180);
  theta3 = acos(rad3);
  float t3 = cosT3; //Theta parameters 3
  //r2 z2 for theta 2 and 4
  r2 = (cos(theta2) * (link2 + link3 * cos(theta3)) - sin(theta2) * 
    (link3 * sin(theta3)));
  z2 = (cos(theta2) * (link3 * sin(theta3))) + (sin(theta2) * 
    (link2 + link3 * cos(theta3)));
  //sin cos theta2
  float cosT2 = ((link2 + link3 * cos(theta3)) * r2) + ((link3 * sin(theta3)) * z2) /
    sq(r2) + sq(z2);
  float sinT2 = ((link2 + link3 * cos(theta3)) * z2) + ((link3 * sin(theta3)) * r2) /
    sq(r2) + sq(z2);
  //theta 2 and 4
  theta2 = atan((sinT2 * 3.14)/(cosT2 * 3.14));
  float t2 = (theta2*180)/3.14; //Theta parameter 2
  theta4 = 130 - (t2 + t3);
  float t4 = theta4; //Theta parameter 4
  //Output theta
  Serial.print("\n");
  Serial.print("Theta 1: ");
  Serial.println(t1);
  Serial.print("Theta 2: ");
  Serial.println(t2);
  Serial.print("Theta 3: ");
  Serial.println(t3);
  Serial.print("Theta 4: ");
  Serial.println(t4);
  //move position
  moveServoSmoothly(servo1, currentpos + 90, t1 + 90);
  delay(700);
  moveServoSmoothly(servo2, currentpos, t2);
  delay(700);
  moveServoSmoothly(servo3, currentpos, t3);
  delay(700);
  moveServoSmoothly(servo4, currentpos, t4);
  OpsiExit(t1 ,t2, t3, t4);
}

void OpsiExit(float posT1, float posT2, float posT3, float posT4) {
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
    reset(posT1, posT2, posT3, posT4);
  } 
  else {
    Serial.print("\n");
    Serial.println("Back to menu exit");
    OpsiExit(posT1, posT2, posT3, posT4);
  }
}

void reset(float pos1, float pos2, float pos3, float pos4) {
  delay(700);
  moveServoSmoothly(servo1, pos1 + 90, currentpos + 90);
  delay(700);
  moveServoSmoothly(servo2, pos2, currentpos);
  delay(700);
  moveServoSmoothly(servo3, pos3, currentpos);
  delay(700);
  moveServoSmoothly(servo4, pos4, currentpos);
  delay(700);
  exit(0);
}

void moveServoSmoothly(Servo servo, float currentPosition, float targetPosition) {
  if (currentPosition < targetPosition) {
    for (float pos = currentPosition; pos <= targetPosition; pos+=1) {
      servo.write(pos);
      delay(delayTime);
    }
  }
  else {
    for (float pos = currentPosition; pos >= targetPosition; pos-=1) {
      servo.write(pos);
      delay(delayTime);
    }
  }
}