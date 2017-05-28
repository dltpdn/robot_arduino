#include <Servo.h>
#define SERVO_CNT  4
#define STEP  1
#define UP_THESHOLD 700
#define DN_THESHOLD 400
#define MAX_IDLE_TIME 5000 //ms, 0:infinity

int d_pin[SERVO_CNT], a_pin[SERVO_CNT], init_angle[SERVO_CNT], min_angle[SERVO_CNT], max_angle[SERVO_CNT];
int value[SERVO_CNT], curr_angle[SERVO_CNT], prev_angle[SERVO_CNT];
unsigned long last_running_time;

Servo servos[SERVO_CNT];

void setup(){
	Serial.begin(9600);

	// Middle
	d_pin[0] = 11;
	a_pin[0] = 0;
	min_angle[0] = 0;
	max_angle[0] = 180;
	init_angle[0] = 90;
	

	// left
	d_pin[1] = 10;
	min_angle[1] = 30;
	max_angle[1] = 110;
	init_angle[1] = 90;
	a_pin[1] = 1;
	
	// Right
	d_pin[2] = 9;
	min_angle[2] = 40;
	max_angle[2] = 180;
	init_angle[2] = 90;
	a_pin[2] = 2;
	
	// claw
	d_pin[3] = 6;
	min_angle[3] = 10;
	max_angle[3] = 110;
	init_angle[3] = 90;
	a_pin[3] = 3;
	
	for (int i = 0; i < SERVO_CNT; i++){
		servos[i].attach(d_pin[i]);
		servos[i].write( init_angle[i]);
		value[i] = 0;
		prev_angle[i] =  init_angle[i];
	}
	last_running_time = millis();
}

void loop(){
	delay(10); // 로봇팔 속도조정을 위한 딜레이

	for (int i = 0; i < SERVO_CNT; i++){
		value[i] = analogRead(a_pin[i]);
		curr_angle[i] = prev_angle[i] = servos[i].read();

		if(value[i] > UP_THESHOLD){
			if(curr_angle[i] <  max_angle[i])
				curr_angle[i] += STEP;
		}else if (value[i] < DN_THESHOLD){
			if (curr_angle[i] > min_angle[i])
					curr_angle[i] -= STEP;
		}
		
		if(prev_angle[i] != curr_angle[i]){
			Serial.print(i);
			Serial.print(":");
			Serial.println(curr_angle[i]);

			if(!servos[i].attached()){
				servos[i].attach(d_pin[i]);
			}
			servos[i].write(curr_angle[i]);
			last_running_time = millis();
		}
		if (MAX_IDLE_TIME != 0 && (millis() - last_running_time) > MAX_IDLE_TIME && servos[i].attached()){
			servos[i].detach(); // 서보모터를 일정시간 사용하지 않으면 연결을 끊어둔다.
		}
	}
}