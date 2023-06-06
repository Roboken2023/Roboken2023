#pragma once

#ifndef PINS_H
#define PINS_H
#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>


int current_step=0; // variable to hold the stepper values

Servo s1; // shoulder  // 39 blue n white
Servo s2; // elbow    // 35 black
Servo s3; // left claw  // 29 orange
Servo s4; // rightclaw 28, orange
Servo s5; //wrist  //37 blue

// IR sensors
#define leftCorner 8
#define left_s 9
#define right_s 10
#define rightCorner 11

// pwm
#define pwm 200
#define pwm2 255

// stepper
Stepper stepper(200, 45, 47, 49, 51);

// motor
#define en1 52
#define in1 50
#define in2 48
#define in3 46
#define in4 44
#define en2 42 

// initializer function
void setup2(){
  Serial.begin(9600);
  stepper.setSpeed(30);
  pinMode(en1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(53, OUTPUT);

  digitalWrite(43, HIGH);
  digitalWrite(53, HIGH);

// servos 
  s1.attach(39);  
  s2.attach(35);
  s3.attach(29);
  s4.attach(28);
  s5.attach(37);
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

// tester function
void followLine(){
  int l = digitalRead(left_s);
  int r = digitalRead(right_s);
  if(l == 0 && r ==0){
    forward(pwm);
  }else if(l==1 && r ==0 ){
    left(pwm2);
  }else if(l ==0 && r ==1){
    right(pwm2);
  }else{
    forward(pwm);
  }
}



#endif