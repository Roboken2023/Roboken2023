#include "ikarm.h"

void setup(){
    Serial.begin(9600);
    setupArm();
}


void loop(){
    runArm();
}