/*

*/
#include <Servo.h>
Servo Servo1;

int servoPinMaster = 6;
int potPin = A0;

int currentPos, difference = 0;


void setup() {
  Servo1.attach(servoPinMaster);

  Serial.begin(9600);
}

void loop() {
  
  int read = analogRead(potPin);
  int newPosition = map(read,0,1023,0,180); //this bascially maps the servos 180 degrees to the potentionmeters 1023 degrees
  Servo1.write(newPosition);
  Serial.print(newPosition);
  Serial.print('\n');

}

void move(int x, int y, int z){
  int base = atan(y/x);
  int l = sqrt((x*x+y*y));
  int h = sqrt((z*z+l*l));
  int phi = atan(z/l);
  int alpha = acos((h/2)/8);
  
  int angle1 = alpha + phi;
  int angle2 = phi - alpha;
  
  //Servo1.write(base);
  //Servo2.write(angle2);
  //Servo3.write(angle1);
  
}