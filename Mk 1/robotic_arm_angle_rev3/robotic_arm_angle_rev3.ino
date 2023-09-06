/*
July 21st 2023 Revision 3 
*/
#include <Servo.h>
#include <Ramp.h>
Servo Servo1,Servo2,Servo3,Servo4;

int servo1 = 6;
int servo2 = 9;
int servo3 = 10;
int servo4 = 11;


rampFloat baseramp;
rampFloat bottomarm;
rampFloat toparm;
rampFloat claw;

float angles[3];

void setup() {
  Servo1.attach(servo1);
  Servo2.attach(servo2);
  Servo3.attach(servo3);
  Servo4.attach(servo4);

  Serial.begin(9600);

  calculate(1,1,4,angles);

  move(angles[0],angles[1],angles[2],false);
  move(45,145,-4,true);
  move(0,0,80,true);
  move(0,160,15,true);
  move(0,160,-40,true);
  move(0,160,-40,false);
  move(0,0,80,false);

}

void loop() {
  

}

void calculate(int x, int y, int z, float (&angles)[3]){
  
  angles[0] = atan(y/x)*180/3.14;
  float l = sqrt((x*x+y*y));
  float h = sqrt((z*z+l*l));
  float phi = atan(z/l);
  float alpha = acos((h/2)/8);
  
  angles[1] = (alpha + phi)*180/3.14;
  angles[2] = (phi - alpha)*180/3.14;


  //Servo4.write(angle1);
  //Servo2.write(base);
  //Servo3.write(angle2);
  Serial.print('\n');
  Serial.println((String)angles[0] + ' ' + angles[1] + ' ' + angles[2]);
  
}

void move(float base, float angle1, float angle2, bool grab){
  if(grab){
    claw.go(20,2000,LINEAR,ONCEFORWARD);
  }else{
    claw.go(100,2000,LINEAR,ONCEFORWARD);
  }

  baseramp.go(base,3000,LINEAR,ONCEFORWARD);
  bottomarm.go(angle1,3000,LINEAR,ONCEFORWARD);
  toparm.go(angle2,3000,LINEAR,ONCEFORWARD);

  while(baseramp.isRunning() || bottomarm.isRunning() || toparm.isRunning()){
  Servo1.write(claw.update());
  Servo2.write(baseramp.update());
  Servo3.write(toparm.update());
  Servo4.write(bottomarm.update());
  }

}
