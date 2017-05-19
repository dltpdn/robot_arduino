#define PIN_SERVO 9

int val = 0;
void setup() {
  pinMode(PIN_SERVO, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    val = Serial.read();
    if(val == '1') 
		analogWrite(PIN_SERVO, 64);
    else if(val == '2') 
		analogWrite(PIN_SERVO, 127);
    else if(val == '3') 
		analogWrite(PIN_SERVO, 191);
    else 
		analogWrite(PIN_SERVO, 0);
  } 
}