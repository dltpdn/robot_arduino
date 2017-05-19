#include <Servo.h>

#define PIN_SERVO 9

Servo servo;
int val = 0;
void setup() {
  servo.attach(PIN_SERVO);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    val = Serial.read();
    if(val == '1') servo.write(0);
    else if(val == '2') servo.write(90);
    else if(val == '3') servo.write(180);
    else servo.detach();
  } 
}