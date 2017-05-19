#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

const int SERVOS = 4;
const int GAP = 5;
const int IDLE_TIME = 1*1000;
int PIN[SERVOS], value[SERVOS],  currentAngle[SERVOS], MIN[SERVOS];
int MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS];
unsigned long last_time[SERVOS];
Servo myservo[SERVOS];

#define PIN_MOTOR1 13
#define PIN_MOTOR2 12
#define PIN_MOTOR3 8
#define PIN_MOTOR4 7

#define PIN_MID 11
#define PIN_LEFT 10
#define PIN_RIGHT 9
#define PIN_CLAW 6

#define PIN_ECHO 5
#define PIN_TRIG 4

#define PIN_RX 3
#define PIN_TX 2

SoftwareSerial bt(2, 3);
char val = '0';
char cmd ;
int target;
int up_down;

void init_servo(int idx, int pin, int min, int max, int init) {
  PIN[idx] = pin;
  MIN[idx] = min;
  MAX[idx] = max;
  INITANGLE[idx] = init;
  myservo[idx].attach(pin);
  myservo[idx].write(init);
  value[idx] = 0;
  previousAngle[idx] = init;
  last_time[idx] = millis();
}

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(PIN_MOTOR1, OUTPUT);
  pinMode(PIN_MOTOR2, OUTPUT);
  pinMode(PIN_MOTOR3, OUTPUT);
  pinMode(PIN_MOTOR4, OUTPUT);

  init_servo(0, PIN_MID, 0, 180, 90); //Middle
  init_servo(1, PIN_LEFT, 30, 110, 90);//left
  init_servo(2, PIN_RIGHT, 40, 180, 90);//Right
  init_servo(3, PIN_CLAW, 10, 110, 90); //claw
}

void forward() {
  digitalWrite(PIN_MOTOR1, HIGH);
  digitalWrite(PIN_MOTOR2, LOW);
  digitalWrite(PIN_MOTOR3, HIGH);
  digitalWrite(PIN_MOTOR4, LOW);
}
void backward() {
  digitalWrite(PIN_MOTOR1, LOW);
  digitalWrite(PIN_MOTOR2, HIGH);
  digitalWrite(PIN_MOTOR3, LOW);
  digitalWrite(PIN_MOTOR4, HIGH);
}
void turn_left() {
  digitalWrite(PIN_MOTOR1, LOW);
  digitalWrite(PIN_MOTOR2, LOW);
  digitalWrite(PIN_MOTOR3, HIGH);
  digitalWrite(PIN_MOTOR4, LOW);
}
void turn_right() {
  digitalWrite(PIN_MOTOR1, HIGH);
  digitalWrite(PIN_MOTOR2, LOW);
  digitalWrite(PIN_MOTOR3, LOW);
  digitalWrite(PIN_MOTOR4, LOW);
}
void stop() {
  digitalWrite(PIN_MOTOR1, LOW);
  digitalWrite(PIN_MOTOR2, LOW);
  digitalWrite(PIN_MOTOR3, LOW);
  digitalWrite(PIN_MOTOR4, LOW);
}

void loop() {
  if (bt.available()) {
    cmd = bt.read();
    Serial.println(cmd);
    if (cmd == '0') { //Stop
      stop();
    } else if (cmd == '8') {
      forward();
    } else if (cmd == '2') {
      backward();
    } else if (cmd == '4') {
      turn_left();
    } else if (cmd == '6') {
      turn_right();
    }

    //    cmd = bt.read();
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
    currentAngle[target] = myservo[target].read();
    previousAngle[target] = myservo[target].read();
    if (up_down) {
      if (currentAngle[target] < MAX[target]) currentAngle[target] += GAP;
    } else {
      if (currentAngle[target] > MIN[target]) currentAngle[target] -= GAP;
    }
    if (!myservo[target].attached()) {
      myservo[target].attach(PIN[target]);
    }

    if (previousAngle[target] != currentAngle[target]) {
      myservo[target].write(currentAngle[target]);
      last_time[target] = millis();
    }
    Serial.println(currentAngle[target]);
  }// end of bt.available()
  
  for(int j=0; j<SERVOS; j++){
    if( (millis() - last_time[j]) > IDLE_TIME && myservo[j].attached()){
      myservo[j].detach();
    }
  }
}

