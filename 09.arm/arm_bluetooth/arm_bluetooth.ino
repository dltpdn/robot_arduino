#include <Servo.h>
#include <SoftwareSerial.h>

#define SERVO_CNT 4
#define STEP 1
#define MAX_IDLE_TIME 5000
#define RX 2
#define TX 3

SoftwareSerial bt(RX, TX);
int d_pin[SERVO_CNT], value[SERVO_CNT], last_idle_time[SERVO_CNT], curr_angle[SERVO_CNT], min_angle[SERVO_CNT];
int max_angle[SERVO_CNT], init_angle[SERVO_CNT], prev_angle[SERVO_CNT];
Servo servos[SERVO_CNT];
char cmd ;
int target;
boolean up_down;

void setup(){
  Serial.begin(9600);
  bt.begin(9600);

  //Middle
  d_pin[0] = 11;
  min_angle[0] = 0;
  max_angle[0] = 180;
  init_angle[0] = 90;

  //left
  d_pin[1] = 10;
  min_angle[1] = 30;
  max_angle[1] = 110;
  init_angle[1] = 90;

//Right
  d_pin[2] = 9;
  min_angle[2] = 40;
  max_angle[2] = 180;
  init_angle[2] = 90;

  //claw
  d_pin[3] = 6;
  min_angle[3] = 10;
  max_angle[3] = 110;
  init_angle[3] = 90;

  for (int i = 0; i < SERVO_CNT; i++) {
    servos[i].attach(d_pin[i]);
    servos[i].write(init_angle[i]);
    value[i] = 0;
    prev_angle[i] = init_angle[i];
    last_idle_time[i] = millis();
  }
}


void loop() {
  delay(10);

  if (Serial.available() > 0) {
    cmd = Serial.read();

    if (cmd == 'm' || cmd == 'M') {
      target = 0;
      up_down = cmd == 'm' ? false : true;
    }else if (cmd == 'l' || cmd == 'L') {
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
    if(up_down){
      if( curr_angle[target] < max_angle[target] ){
            curr_angle[target] += STEP;
      }
    }else{
      if(curr_angle[target] > min_angle[target]){
            curr_angle[target] -= STEP;
      }
    }
    if(curr_angle != prev_angle){
      if (!servos[target].attached()){
        servos[target].attach(d_pin[target]);
      }
      servos[target].write(curr_angle[target]);
    }

  }// end of Serial.available

  for(int i=0; i<SERVO_CNT; i++){
    if (last_idle_time[i] - millis() > MAX_IDLE_TIME){
      servos[i].detach(); // 서보모터를 일정시간 사용하지 않으면 연결을 끊어둔다.
    }
  }
}//end of loop
