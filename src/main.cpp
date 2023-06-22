#include "pins.h"
// #include "Gyroscope.h"
#include "ikarm.h"

int counter = 0;
int flag = 0;
unsigned long currTime=0;

void moveToCabin(){
  int offset;
  while(true){
    offset = calculateDistance(trig2, echo2)*10;
    // Serial.println(offset);
    if(offset<300){
      stop();
      delay(10000);
    }else{
      followLine();
    }
  }
}

void gotoCabin(){
  currTime=millis();
  while(millis()-currTime < 5000){
    forward(255);
  }
  right(255);
  delay(500);
  stop();
  delay(2000);//
  right(255); //turning left 
  delay(600);
  stop();
  delay(100);

  //find line

   while(digitalRead(right_S) == 0 || digitalRead(left_S) == 0 ){

      forward(255);
      if (digitalRead(right_S) == 1 || digitalRead(left_S) == 1){break;}

    }

    stop();
    delay(200);

    //back to line correction
    right(255);
    delay(120);

  while(true){
    distance = calculateDistance()*10; // convert to millimeters
    // Serial.println(distance);
    if ((int)distance > 200)
    {
      followLine();
    }
    else{
  // =================================================engine==========================
      stop();
      delay(3000); //drop cabin
      break;
    }
  }

  currTime = millis();

    while (true){
      if ((millis()-currTime) < 3000)
          {
            followLineBackwards();
          }
          else{
            break;
            }      
    }

 

}

void gotoEngine(){
     //turning right to move to engine line
    stop();
    delay(100);
    left(255);
    delay(250);
    stop();
    delay(120);

  //find engine line
   while( digitalRead(right_S) == 0 || digitalRead(left_S) == 0 ){
      forward(255);
      if (digitalRead(right_S) == 1 || digitalRead(left_S) == 1){break;}
    }

    stop();
    delay(200);
    right(255);
    delay(120);//back to line correction
    
    //move to engine position
    while(true){
      distance = calculateDistance()*10; 
      if ((int)distance > 200)
      {
          followLine();
      }
      else{
        stop();
        delay(3000); //pick up engine
        currTime = millis();
        while(true){
        if (millis()-currTime< 3000)
        {
          followLineBackwards();

        }
        else{break;}

        }        
        break;
      } 
    }
}

void gotoWheels(){
  //turn to face the wheel line
    stop();
    delay(220);
    right(255);
    delay(350);

  //find wheel line
    while(digitalRead(right_S) == 0|| digitalRead(right_S) == 0){
      forward(255);
      if (digitalRead(right_S) == 1 || digitalRead(right_S) == 1){break;}
    }
    stop();
    delay(200);
    left(255);
    delay(200);
  
    //move to wheel position
    while(true){
      distance = calculateDistance()*10; 
      if ((int)distance > 200)
      {
          followLine();
      }
      else{
        stop();
        delay(3000); // pick wheels
        break;
      }
    }
    

}

void gotoRamp(){
    currTime = millis();
    while(millis()-currTime < 5500)
    {
       followLineBackwards();
   }
    right(255);
    delay(350);
    //skip the forthcoming line and reach the ramp line for trailer pick up
    //a counter can also be implemented here
    forward(255);
    delay(2000);
    
    while( digitalRead(left_S) == 0 || digitalRead(right_S) == 0)
    {
      forward(255);
      if (digitalRead(left_S) == 1 || digitalRead(right_S) == 1){break;}

    }
    stop();
    delay(200);
    left(255);//turn to face ramp line
    delay(200);

    //move to trailer position
    while(true){
      distance = calculateDistance()*10; 
      if ((int)distance > 200){
          followLine();
      }
      else{
        stop();
        delay(2000);//pick up the trailer
        currTime = millis();
        while(digitalRead(7)==0 || digitalRead(11)==0)
        {
          followLineBackwards();
          if(digitalRead(7)==1 || digitalRead(11)==1){
            break;
          }
        }
        stop();
        delay(100);
        forward(255);
        delay(350);
        left(255);
        delay(500);
        while(true){
          distance = calculateDistance()*10; 
          if ((int)distance > 200){
              followLine();
          }
          else{
            break;
          }
        }
        stop();

        break;
      }
    }

    // move down the ramp

}


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

    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT_PULLUP);

    pinMode(3, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);
    // gotoCabin();
    // gotoEngine();
    // gotoWheels();
    // gotoRamp();
    // moveToCabin();
    setupArm();
    pickWheels();


    
}

void loop()
{
  runArm();

}