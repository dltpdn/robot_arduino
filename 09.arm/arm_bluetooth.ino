#include <Servo.h>
const int SERVOS = 4;
const int GAP = 1;
int PIN[SERVOS], value[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS];
int MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS];
Servo myservo[SERVOS];
char cmd ;
int target;
int up_down;

void setup()   {
  Serial.begin(9600);
  //Middle
  PIN[0] = 11;
  MIN[0] = 0;
  MAX[0] = 180;
  INITANGLE[0] = 90;
  //left
  PIN[1] = 10;
  MIN[1] = 30;
  MAX[1] = 110;
  INITANGLE[1] = 90;
//Right
  PIN[2] = 9;
  MIN[2] = 40;
  MAX[2] = 180;
  INITANGLE[2] = 90;

  //claw
  PIN[3] = 6;
  MIN[3] = 10;
  MAX[3] = 110;
  INITANGLE[3] = 90;

  for (int i = 0; i < SERVOS; i++) {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    value[i] = 0;
    idle[i] = 0;
    previousAngle[i] = INITANGLE[i];
  }
}
void loop() {
delay(10);
  if (Serial.available() > 0) {
    cmd = Serial.read();
    if (cmd == 'm' || cmd == 'M') {
      target = 0;
      if (cmd == 'm') up_down = 0;
      else up_down = 1;
    } else if (cmd == 'l' || cmd == 'L') {
      target = 1;
      if (cmd == 'l') up_down = 0;
      else up_down = 1;
    } else if (cmd == 'r' || cmd == 'R') {
      target = 2;
      if (cmd == 'r') up_down = 0;
      else up_down = 1;
    } else if (cmd == 'c' || cmd == 'C') {
      target = 3;
      if (cmd == 'c') up_down = 0;
      else up_down = 1;
    }
 if (up_down) {
      if (currentAngle[target] < MAX[target]) currentAngle[target] += GAP;
      if (!myservo[target].attached()) {
        myservo[target].attach(PIN[target]);
      }
      myservo[target].write(currentAngle[target]);
    } else {
      if (currentAngle[target] > MIN[target]) currentAngle[target] -= GAP;
      if (!myservo[target].attached()) {
        myservo[target].attach(PIN[target]);
      }
      myservo[target].write(currentAngle[target]);
    }
  }

}
