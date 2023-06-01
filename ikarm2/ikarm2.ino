#include <AFMotor.h>

AF_Stepper stepper(200,1);

#include <Servo.h>
Servo s1;
Servo s2;

bool prevDirection = true; // true for forward, false for backward

int SHOULDER=210;
int ELBOW=100; 

double ratio = 180/3.14159265359; 

double shoulderAngleDeg=0;
double elbowAngleDeg = 0;
double shoulderAngleRadians=100000;
double elbowAngleRadians=100000;
double revAngle; // store the step angle in radians
int stepVal;

bool calculateViability(int x, int y, int z){
  
}

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
 s1.write(0);
 delay(500);
 s2.write(0);
 delay(500);
  
}

void calculateAngles(int x, int y, int z){
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
   stepVal = deg2step(_Angle);
   
   bool targetReachedS = false;
   bool targetReachedE = false;
   bool stepperReached = false;
   int stepCount = 0;
   int dir = prevDirection?FORWARD:BACKWARD;
   
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
      if(stepCount != stepVal){ // move s1
        stepper.step(1, FORWARD, SINGLE);
        stepCount +=1;
      }else{
        stepperReached = true;
      }
      delay(10);
    }
    prevDirection = !prevDirection;
}

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(10);
  s1.attach(45);
  s2.attach(49);
  Serial.println(s1.read());
  Serial.println(s2.read());
  delay(500);
//  reset();
  delay(500);
  Serial.println("setting to zero done");
  Serial.println(s1.read());
  Serial.println(s2.read());
  
}

void loop() {
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
  
  calculateAngles(x,y,z);
 
  Serial.println(shoulderAngleDeg);
  Serial.println(elbowAngleDeg);
  Serial.println(revAngle);

  moveToTarget(shoulderAngleDeg,elbowAngleDeg, revAngle);
 stepper.release();
  
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
  
}
