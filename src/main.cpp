#include "AdvancedLine.h"

void setup(){
    Serial.begin(9600);
    line::initialize();
    
}


void loop(){
  Serial.print(digitalRead(left_S));
  Serial.print(" ");
  Serial.print(digitalRead(right_S));
  Serial.print(" ");
  Serial.print(digitalRead(leftCorner));
  Serial.print(" ");
  Serial.print(digitalRead(rightCorner));
  Serial.print("  | ");
  Serial.print(analogRead(left_S));
  Serial.print(" ");
  Serial.print(analogRead(right_S));
  Serial.print(" ");
  Serial.print(analogRead(leftCorner));
  Serial.print(" ");
  Serial.print(analogRead(rightCorner));
  Serial.println();
  delay(1500);

}