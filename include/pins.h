#pragma once

#ifndef PINS_H
#define PINS_H
#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>

#define LEFT 1
#define RIGHT 2
#define FORWARD 3

int mode = FORWARD;
int timeSpentGoingForward=0;

int trig = 9;
int echo = 8;

int trig2 = 10;
int echo2 = 11;
float distance =1;

Servo s1; // shoulder  // 39 blue n white
Servo s2; // elbow    // 35 black
Servo s3; // left claw  // 29 orange
Servo s4; // rightclaw 28, orange
Servo s5; //wrist  //37 blue

// stepper
Stepper stepper(200, 45, 47, 49, 51);

#define en1 44 // left motor
#define in1 50
#define in2 48

#define in3 42 // right motor
#define in4 40
#define en2 46

// IR SENSOR
#define leftCorner A3 //interrupt
#define left_S A2
#define right_S A1
#define rightCorner A0  // interrupt

int pwm=255;
int pwm2=180;


                                                                                                 
void forward(int _pwm){    
  // int pwmForward = _pwm;
  // if(mode!=FORWARD){
  //   mode = FORWARD;
  //   timeSpentGoingForward=millis();
  // }else{   
  //   if((millis()-timeSpentGoingForward > 1000) && (millis()-timeSpentGoingForward<2000)){
  //     pwmForward = _pwm-(_pwm-170)*((millis()-timeSpentGoingForward )/2000);
  //   }else{
  //     pwmForward=170;
  //   }
  // }          // forward
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
void stop();

void left_90(){  \
  //  forward(255);
  // delay(300);
  stop();
  delay(100);           // left 90 degrees
  analogWrite(en1, 255);
  analogWrite(en2, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500);
  analogWrite(en1, 255);
  analogWrite(en2,255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(100);
}

void right_90(){ 
  // forward(255);
  // delay(300);
  stop();
  delay(100);            // left 90 degrees
  analogWrite(en1, 255);
  analogWrite(en2, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(600);
  analogWrite(en1, 255);
  analogWrite(en2,255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(100);
  // stop();
  // delay(1000);
}

void delay_ms(int ms){
  int _t = millis();
  while(true){
    if(millis()-_t < 5000){
      ;
    }else{
      break;
    }
  }

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

void stop(){
  analogWrite(en1, 0);
  analogWrite(en2, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

float calculateDistance(){ 
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  float d= duration*0.034/2;
  return d;
}

float calculateDistance(int trigger, int echoPin){ 
  digitalWrite(trigger, LOW); 
  delayMicroseconds(2);  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  float d= duration*0.034/2;
  return d;
}

void followLine(){

  int l = digitalRead(left_S);
  int r = digitalRead(right_S);
  if(l == 0 && r ==0){
    forward(pwm);
  }else if(l==1 && r ==0 ){
    right(pwm2);
  }else if(l ==0 && r ==1){
    left(pwm2);
  }else{
    forward(pwm);
  }
}

void followLineBackwards(){

  int l = digitalRead(3);
  int r = digitalRead(2);
  if(l == 0 && r ==0){
    back(pwm);
  }else if(l==1 && r ==0 ){
    Serial.println("left");
    right(pwm2);
  }else if(l ==0 && r ==1){
    Serial.println("right");
    left(pwm2);
  }else{
    back(pwm);
  }
}


#endif