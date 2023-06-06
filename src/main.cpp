#include "ikarm.h"

void setup(){
    Serial.begin(9600);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    
}


void loop(){
    // this loop should run once?
  Serial.println(digitalRead(9));
  Serial.println(digitalRead(10));
  Serial.println("""""""""""""""""""""""""""""""""");
  followLine();
}