// contains the code for running through the maze
#ifndef PINS_H
#include "pins.h"
#endif

void followLine(){
  int l = digitalRead(left_s);
  int r = digitalRead(right_s);
  int r_corner = digitalRead(rightCorner);
  int l_corner = digitalRead(leftCorner);
  
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
