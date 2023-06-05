#pragma once

#ifndef PINS_H
#define PINS_H

#include <Servo.h>
#include <Stepper.h>


Servo s1; // shoulder
Servo s2; // elbow
Servo s3; //claw
Servo s4; // claw 2
Servo s5; //wrist


// stepper
Stepper stepper(stepsPerRevolution, 45, 47, 49, 51);

// motor
#define enA 52
#define in1 20
#define in2 48
#define in3 46
#define in4 44
#define enB 42 

// initializer function
void setup2(){
  Serial.begin(9600);
  stepper.setSpeed(30);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(53, OUTPUT);

  digitalWrite(43, HIGH);
  digitalWrite(53, HIGH);

// servos 
  s1.attach();  
  s2.attach();
  s3.attach();
  s4.attach();
  s5.attach();
}

// line follower functions
                                                                                                 
void forward(int _pwm){             // forward
  analogWrite(en1, _pwm);
  analogWrite(en2, _pwm);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void back(int _pwm){             // back
  analogWrite(en1, _pwm);
  analogWrite(en2, _pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left_90(){             // left 90 degrees
  analogWrite(en1, 200);
  analogWrite(en2, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(50);
}

void right_90(){             // left 90 degrees
  analogWrite(en1, 200);
  analogWrite(en2, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(50);
}

void right(int _pwm){
  analogWrite(en1, _pwm);
  analogWrite(en2, _pwm);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left(int _pwm){
  analogWrite(en1, _pwm);
  analogWrite(en2, _pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}




#endif
