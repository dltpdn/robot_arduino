#include <Servo.h>

#include <Arduino.h>
#include <SoftwareSerial.h>

#define SERVO_CNT 4
#define STEP 5
#define MAX_IDLE_TIME 1000

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


int d_ping[SERVO_CNT], value[SERVO_CNT],  curr_angle[SERVO_CNT], min_angle[SERVO_CNT];
int max_analge[SERVO_CNT], init_angle[SERVO_CNT], prev_angle[SERVO_CNT];
unsigned long last_idle_time[SERVO_CNT];

char cmd ;
int target;
boolean up_down;

Servo servos[SERVO_CNT];
SoftwareSerial bt(2, 3);

void init_servo(int idx, int pin, int min, int max, int init) {
  d_ping[idx] = pin;
  min_angle[idx] = min;
  max_analge[idx] = max;
  init_angle[idx] = init;
  servos[idx].attach(pin);
  servos[idx].write(init);
  value[idx] = 0;
  prev_angle[idx] = init;
  last_idle_time[idx] = millis();
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
    if(cmd =='0' || cmd == '8' || cmd =='2' || cmd =='4' || cmd =='6' ){
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
    }else if(cmd =='m' || cmd=='M' || cmd =='l' || cmd == 'L' || cmd =='r' || cmd == 'R' || cmd =="c" || cmd=='C'){
      if (cmd == 'm' || cmd == 'M') {
        target = 0;
        up_down = cmd == 'm' ? false : true;
      } else if (cmd == 'l' || cmd == 'L') {
        target = 1;
        up_down = cmd == 'l' ? false : true;
      } else if (cmd == 'r' || cmd == 'R') {
        target = 2;
        up_down = cmd == 'r' ? false : true;
      } else if (cmd == 'c' || cmd == 'C') {
        target = 3;
        up_down = cmd == 'c' ? false : true;
      }
      curr_angle[target] = prev_angle[target] = servos[target].read();
      if (up_down) {
        if (curr_angle[target] < max_analge[target]) curr_angle[target] += STEP;
      }else{
        if (curr_angle[target] > min_angle[target]) curr_angle[target] -= STEP; 
      }
      if (prev_angle[target] != curr_angle[target]) { //ignore the same angle with prev
        if (!servos[target].attached()) {
          servos[target].attach(d_ping[target]);
        }
        servos[target].write(curr_angle[target]);
        last_idle_time[target] = millis();
      }
      Serial.println(curr_angle[target]);
    }
  }// end of bt.available()
  
  for(int j=0; j<SERVO_CNT; j++){
    if( (millis() - last_idle_time[j]) > MAX_IDLE_TIME && servos[j].attached()){
      servos[j].detach();
    }
  }
}

