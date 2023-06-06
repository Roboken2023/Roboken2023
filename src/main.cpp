#include "ikarm.h"

void setup(){
    Serial.begin(9600);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    
}


void loop(){
    Serial.print(" 8 ");
    Serial.println(digitalRead(8));
    Serial.print(" 9 ");
    Serial.println(digitalRead(9));
    Serial.print(" 10 ");
    Serial.println(digitalRead(10));
    Serial.print(" 11 ");
    Serial.println(digitalRead(11));
    Serial.println("===================");
    delay(2000);
}