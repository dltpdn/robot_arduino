#define PIN_LED 13

unsigned long lastMillis = 0;
const long INTERVAL = 1000;
int state = LOW;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if(millis() - lastMillis > INTERVAL){
    lastMillis = millis();
    if(state == LOW){
      state = HIGH;
    }else{
      state = LOW;
    }
    digitalWrite(PIN_LED, state);
  }
}
