#include "pins.h"
#include "Gyroscope.h"

int counter = 0;
int flag = 0;
void setup(){
    Serial.begin(9600);
    pinMode(A7, OUTPUT);
    digitalWrite(A7, LOW);
    pinMode(en1, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(en2, OUTPUT);
    
    pinMode(leftCorner, INPUT_PULLUP);
    pinMode(left_S, INPUT_PULLUP);
    pinMode(right_S, INPUT_PULLUP);
    pinMode(rightCorner, INPUT_PULLUP);


    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT_PULLUP);

    pinMode(12, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);

    

    
}

void gotoCabin(){
  int currTime = millis();
    while ((millis()-currTime) < 6000)
    {
      followLine();

    }
  right_90();
  stop();
  delay(2000);
  right(255);
  delay(1000);
  //  while(digitalRead(rightCorner) == 0 || digitalRead(right_S) == 0){
  //     forward(255);
  //   }
  //   stop();
  //   delay(200);
  //   right(255);
  //   delay(200);
  while(true){
    distance = calculateDistance()*10; // convert to millimeters
    Serial.println(distance);
    if ((int)distance > 200){
      followLine();
    }else{
  // =================================================engine==========================
      stop();
      delay(2000); // pick engine
      break;
    }
  }
}

void gotoEngine(){
  while(true){
    distance = calculateDistance()*10; // convert to millimeters
    Serial.println(distance);
    if ((int)distance > 200){
      followLine();
    }else{
  // =================================================engine==========================
      stop();
      delay(2000); // pick engine
      break;
    }
  }

}

void gotoWheels(){
    int currTime = millis();
    while ((millis()-currTime) < 3000)
    {
      followLineBackwards();

    }
    stop();
    delay(200);
    right(255);
    delay(350);
    currTime=millis();
    while(millis()-currTime <500){
      forward(255);
    }
    while(digitalRead(rightCorner) == 0 || digitalRead(right_S) == 0){
      forward(255);
    }
    stop();
    delay(200);
    left(255);
    delay(350);
    
    
    while(true){
      distance = calculateDistance()*10; 
      if ((int)distance > 200){
          followLine();
      }else{
        stop();
        delay(3000); // pick wheels
        break;
      }
    }
}

void gotoRamp(){
    int now = millis();
    while(millis()-now < 4500){
       followLineBackwards();
   }
    right(255);
    delay(350);
    forward(255);
    delay(2000);
    
    while(digitalRead(rightCorner) == 0 || digitalRead(right_S) == 0){
      forward(255);
    }
    stop();
    delay(200);
    left(255);
    delay(350);
    
    while(true){
      distance = calculateDistance()*10; 

      if ((int)distance > 200){
          followLine();
      }
      else{
        stop();
        delay(10000);
        break;
      }
    }
}


void loop(){
  if(flag==0){
    // gotoCabin();
    gotoEngine();
    gotoWheels();
    gotoRamp();
    // setupIMU();
    // gotoCabin();
    
    flag=1;
  }
  // counter++;
  
  // followLineBackwards();
  // delay(10000);
  // int now = millis();
  // while(millis()-now <5000){runIMU();}
  // delay(5000);
  
  // left_90();
  // left_90();
  // delay(2000);

}