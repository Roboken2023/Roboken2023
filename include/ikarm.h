#include "pins.h"

int SHOULDER=210;
int ELBOW=100; 
bool clockwise=true;
double ratio = 180/PI; 

double shoulderAngleDeg=0;
double elbowAngleDeg = 0;
double shoulderAngleRadians=100000;
double elbowAngleRadians=100000;
double revAngle; // store the step angle in radians
int stepVal;
int current_step=0;
#define CLOSE 0
#define OPEN 1

inline double rad2deg(double _rad){
  return _rad*ratio;
}

inline double deg2rad(double _rad){
  return _rad/ratio;
}

inline int deg2step(int angle){
  return floor(angle/1.8);
}
void reset(){
 for(int i = s2.read(); i>0;i--){
    s2.write(i);
    delay(10);
  }
  for(int i = s1.read(); i>0;i--){
    s1.write(i);
    delay(10);
  }
  s2.write(0);
  s1.write(0);
 
  
}

void moveClaws(int dir, int angle){
  if(dir){
    s3.write(angle);
    s4.write(100 - angle);
  }else{
    s4.write(angle);
    s3.write(100 - angle);
  }
}

void calculateAngles(int x, int y, int z){
  if(y<0){
    clockwise = false;
  }else{
    clockwise = true;
  }
  revAngle = (x==0?0:atan(y/x));
  
  revAngle =rad2deg(revAngle); // done with calculating the first angle
  float hyp0 = pow(x,2)+pow(y,2);

  // calculate elbow angle
  float  hyp = hyp0+pow(z,2); // use hyp0 as new x^2
  double elbow = ((pow(SHOULDER,2)+pow(ELBOW,2)-hyp)/(2*SHOULDER))/ELBOW;
  shoulderAngleRadians = -pow(ELBOW,2)+pow(SHOULDER,2)+hyp;
  double shoulder = shoulderAngleRadians/(2*210*sqrt(hyp));
  
  if(shoulder > 1 || elbow > 1){goto END;}else{goto BEGIN;}
  
  BEGIN:
    elbowAngleRadians=acos(elbow);
    elbowAngleDeg = 180-rad2deg(elbowAngleRadians);
    shoulderAngleRadians = (sqrt(hyp0)!=0?acos(shoulder)+atan(z/sqrt(hyp0)):acos(shoulder)+deg2rad(90));
    shoulderAngleDeg = rad2deg(shoulderAngleRadians);
    return;
 END:
    Serial.println("invalid entry");
}
void moveToTarget(int _shoulder, int _elbow, int _Angle){
   reset();
   // enable steppers
   digitalWrite(43, HIGH);
   digitalWrite(53, HIGH);
   stepVal = deg2step(_Angle);
   
   bool targetReachedS = false;
   bool targetReachedE = false;
   bool stepperReached = false;
   int stepCount = 0;
   
    while(1){
      if(targetReachedE && targetReachedS && stepperReached){break;}

      /// move elbow
      if(s2.read()!=_elbow){ // move s2
        s2.write(s2.read()+1);
      }else{
        targetReachedE = true;
      }

      ///  move shoulder
      if(s1.read()!=_shoulder){ // move s1
        s1.write(s1.read()+1);
      }else{
        targetReachedS = true;
      }

      // move stepper one step
      if(abs(stepCount) != abs(stepVal)){ // move s1
        if(clockwise){
          stepper.step(1);
          stepCount++;
          current_step++;
        }else{
          stepper.step(-1);
          stepCount--;
          current_step--;
        }
      }else{
        stepperReached = true;
      }
      delay(20);
    }

    // disable stepper to conserve power
    digitalWrite(43, LOW);
    digitalWrite(53, LOW);
    digitalWrite(45, LOW);
    digitalWrite(47, LOW);
    digitalWrite(49, LOW);
    digitalWrite(51, LOW);
}

void pickObject(int x, int y, int z){
  calculateAngles(x,y,z);
 
//  Serial.println(shoulderAngleDeg);
//  Serial.println(elbowAngleDeg);
//  Serial.println(revAngle);

  moveToTarget(shoulderAngleDeg,elbowAngleDeg, revAngle);
  moveClaws(CLOSE,38);
  moveToTarget(90,0,0);
}

void setupArm() {
  stepper.setSpeed(10);
  s1.attach(39);
  s2.attach(35);
  s3.attach(29);
  s4.attach(28);
  pinMode(43, OUTPUT);
  pinMode(53, OUTPUT);


  Serial.println(s1.read());
  Serial.println(s2.read());
//   delay(500);
// //  reset();
//   delay(500);
//   Serial.println("setting to zero done");
//   Serial.println(s1.read());
//   Serial.println(s2.read());
delay(1000);
  
}

void runArm() {
  
  Serial.println("waiting for new coordinates...");
  String s ="";
  while(Serial.available()==0){
  }
  s=Serial.readString();
  int comma = s.indexOf(",");
  int x=s.substring(0,comma).toInt(); // first part
  String sub=s.substring(comma+1,s.length()-1); // second string
  comma = sub.indexOf(",");
  int y=sub.substring(0,comma).toInt(); // first part
  int z = sub.substring(comma+1,sub.length()).toInt();
  s3.write(100);
  s4.write(0);
//  pickObject(x,y,z);
calculateAngles(x,y,z);
 
  Serial.println(shoulderAngleDeg);
  Serial.println(elbowAngleDeg);
  Serial.println(revAngle);

  moveToTarget(shoulderAngleDeg,elbowAngleDeg, revAngle);
//  stepper.release();
  
  Serial.print("shoulder ");
  Serial.print(s1.read());
  Serial.print(" elbow ");
  Serial.print(s2.read());
  Serial.print(" steps ");
  Serial.println(stepVal);
  
  Serial.println("moved to Target: ");

  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);
  delay(500);
  s3.write(36);
  s4.write(64);
  delay(2000);
  for(int i = s2.read(); i>0;i--){
    s2.write(i);
    delay(20);
  }
  for(int i = s1.read(); i>0;i--){
    s1.write(i);
    delay(20);
  }
  moveToTarget(90,90,0);
  moveToTarget(shoulderAngleDeg,elbowAngleDeg, revAngle);
  
}