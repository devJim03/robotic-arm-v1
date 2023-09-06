/*

*/
#include <Servo.h>
#include <Ramp.h>
Servo Servo1,Servo2,Servo3,Servo4;

int servo1 = 6;
int servo2 = 9;
int servo3 = 10;
int servo4 = 11;
//int potPin = A0;

int currentPos, difference = 0;

void setup() {
  Servo1.attach(servo1);
  Servo2.attach(servo2);
  Servo3.attach(servo3);
  Servo4.attach(servo4);

  Serial.begin(9600);

  move(1,1,4);
}

void loop() {
  
  //int read = analogRead(potPin);
  //int newPosition = map(read,0,1023,0,180); //this bascially maps the servos 180 degrees to the potentionmeters 1023 degrees
  

}

void move(int x, int y, int z){
  rampFloat baseramp;
  rampFloat bottomarm;
  rampFloat toparm;
  rampFloat claw;
  

  float base = atan(y/x);
  base = base*180/3.14;
  float l = sqrt((x*x+y*y));
  float h = sqrt((z*z+l*l));
  float phi = atan(z/l);
  float alpha = acos((h/2)/8);
  
  float angle1 = (alpha + phi)*180/3.14;
  float angle2 = (phi - alpha)*180/3.14;


  //Servo4.write(angle1);
  //Servo2.write(base);
  //Servo3.write(angle2);
  Serial.print('\n');
  Serial.println((String)base + ' ' + angle1 + ' ' + angle2);
  
  //move to desired spot


  baseramp.go(base,5000,LINEAR,ONCEFORWARD);
  bottomarm.go(angle1,5000,LINEAR,ONCEFORWARD);
  toparm.go(angle2,5000,LINEAR,ONCEFORWARD);
  //claw.go(25,5000,LINEAR,ONCEFORWARD);
  
  while(baseramp.isRunning() || bottomarm.isRunning() || toparm.isRunning()){
    Servo2.write(baseramp.update());
    Servo3.write(toparm.update());
    Servo4.write(bottomarm.update());

    //claw
    //Servo1.write(claw.update());
  }


  //move back to start
  claw.go(25,5000,LINEAR,ONCEFORWARD); //actually close the claw now to grab the toothpick
  baseramp.go(0,5000,LINEAR,ONCEFORWARD);
  bottomarm.go(0,5000,LINEAR,ONCEFORWARD);
  toparm.go(80,5000,LINEAR,ONCEFORWARD);

  while(baseramp.isRunning() || bottomarm.isRunning() || toparm.isRunning()){
  Servo2.write(baseramp.update());
  Servo3.write(toparm.update());
  Servo4.write(bottomarm.update());

  //claw
  Servo1.write(claw.update());
  }

}