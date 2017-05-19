#define PIN_RES 0
#define PIN_LED 11

int v;
void setup() {
 	Serial.begin(9600);
 	pinMode(PIN_LED, OUTPUT);
}

void loop() {
	v = analogRead(PIN_RES);
	analogWrite(PIN_LED, v/4)
 	Serial.println(v);
 	delay(500);
}
