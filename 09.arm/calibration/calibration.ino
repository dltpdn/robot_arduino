#include <Servo.h>

Servo middle, left, right, claw;

void setup() {
  Serial.begin(9600);
  middle.attach(11);
  left.attach(10);
  right.attach(9);
  claw.attach(6);

}

void loop() {
  middle.write(90);
  left.write(90);
  right.write(90);
  claw.write(90);
  delay(300);
}
