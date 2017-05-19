#define PIN_LED 13

void setup(){
	pinMode(PIN_LED, HIGH);
}

void loop(){
	digitalWrite(PIN_LED, HIGH);
	delay(500);
	digitalWrite(PIN_LED, LOW);
	delay(500);
}
