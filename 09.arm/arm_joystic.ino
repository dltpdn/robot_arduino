#include <Servo.h>

const int SERVOS = 4;
const int GAP = 1;
int PIN[SERVOS], value[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS];
int MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS], ANA[SERVOS];
Servo myservo[SERVOS];

void setup()
{
	Serial.begin(9600);
	// Middle
	PIN[0] = 11;
	MIN[0] = 0;
	MAX[0] = 180;
	INITANGLE[0] = 90;
	ANA[0] = 0;
	// left
	PIN[1] = 10;
	MIN[1] = 30;
	MAX[1] = 110;
	INITANGLE[1] = 90;
	ANA[1] = 1;
	// Right
	PIN[2] = 9;
	MIN[2] = 40;
	MAX[2] = 180;
	INITANGLE[2] = 90;
	ANA[2] = 2;
	// claw
	PIN[3] = 6;
	MIN[3] = 10;
	MAX[3] = 110;
	INITANGLE[3] = 90;
	ANA[3] = 3;
	for (int i = 0; i < SERVOS; i++)
	{
		myservo[i].attach(PIN[i]);
		myservo[i].write(INITANGLE[i]);
		value[i] = 0;
		idle[i] = 0;
		previousAngle[i] = INITANGLE[i];
	}
}

void loop()
{
	delay(10); // 로봇팔 속도조정을 위한 딜레이
	for (int i = 0; i < SERVOS; i++)
	{
		value[i] = analogRead(ANA[i]);
		currentAngle[i] = myservo[i].read();
		if (value[i] > 612)
		{
			idle[i] = 0;
			if (currentAngle[i] < MAX[i])
				currentAngle[i] += GAP;
			if (!myservo[i].attached())
			{
				myservo[i].attach(PIN[i]);
			}
			myservo[i].write(currentAngle[i]);
		}
		else
			if (value[i] < 412)
			{
				idle[i] = 0;
				if (currentAngle[i] > MIN[i])
					currentAngle[i] -= GAP;
				if (!myservo[i].attached())
				{
					myservo[i].attach(PIN[i]);
				}
				myservo[i].write(currentAngle[i]);
			}
		else
		{
			++idle[i];
		}
		if (idle[i] > 100)
		{
			myservo[i].detach(); // 서보모터를 일정시간 사용하지 않으면 연결을 끊어둔다.
			idle[i] = 0;
		}
	}
}
