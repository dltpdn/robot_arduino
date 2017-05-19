#define PIN_LDR 0
#define PIN_LED 13

int val = 0;
void setup(){
   pinMode(PIN_LED,OUTPUT);
}

void loop(){
	val = analogRead(PIN_LDR); // 0번 에서 값을 읽어옴
	analogWrite(PIN_LED,val/4); // 센서 밝기 값만큼으로 LED 켜기
	delay(10);
}
