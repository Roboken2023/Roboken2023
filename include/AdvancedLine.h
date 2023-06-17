#ifndef PINS_H
#include "pins.h"
#endif


int leftTurns[] {};
int rightTurns[]{0,3};

int currentTimeLeft(0);   // variable to hold the last time a left corner was registered
int currentTimeRight{0};  // variable to hold the last time a right corner was registered
int currentTimeNow=0;
 
int leftCounter=0;  // volatile as they are going to be changing wierdly
int rightCounter=0;

bool LEFT_ON = false;
bool RIGHT_ON = false;

void incrementLeft(){
    LEFT_ON=true;
    currentTimeNow = millis();
}

void incrementRight(){
    RIGHT_ON = true;
    currentTimeNow = millis();
}

bool inLeftTurns(int turn){
    for(auto &i:leftTurns){
        if(turn==i){
            return true;
        }
    }
    return false;
}
bool inRightTurns(int turn){
    for(auto &i : rightTurns){
        if(turn==i){
            return true;
        }
    }
    return false;
}

namespace line{
    void initialize(){
  
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

        // // attach to interrupt pins to make sure that we get all the counters at the required time
        // attachInterrupt(digitalPinToInterrupt(leftCorner), incrementLeft, RISING); 
        // attachInterrupt(digitalPinToInterrupt(rightCorner), incrementRight, RISING);
    }
    void followLine(){
        int l = digitalRead(left_S);
        int r = digitalRead(right_S);
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

        void followLine2(){
        int l = digitalRead(left_S);
        int r = digitalRead(right_S);
        int l2 = digitalRead(leftCorner);
        int r2 = digitalRead(rightCorner);
        if(l2 == 0 && r2 ==0){
            if(l == 0 && r ==0){
                forward(pwm);
            }else if(l==1 && r ==0 ){
                right(pwm);
            }else if(l ==0 && r ==1){
                left(pwm);
            }else{
                forward(pwm);
            }
        }else if(l2 == 1 && r2 ==0){
            right_90();
        }else if( l2 == 0 && r2 ==1){
            left_90();
        }else{
            stop();
        }
        }

    void run(){
        // if(currentTimeNow-currentTimeLeft>3000 && LEFT_ON){
        //     leftCounter++;
        //     currentTimeLeft=millis();
        //     LEFT_ON= false;
        // }
        // if(currentTimeNow-currentTimeRight>3000 && RIGHT_ON){
        //     rightCounter++;
        //     currentTimeRight=millis();
        //     RIGHT_ON=false;

        // }
        followLine2();
    }
}
