#define PIN_X  A0
#define PIN_Y  A1
#define PIN_SW 2

int x, y, sw;

void setup() {
  pinMode(PIN_SW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  x = analogRead(PIN_X);
  y = analogRead(PIN_Y);
  sw = digitalRead(PIN_SW);
  Serial.print("x:");
  Serial.print(x);
  Serial.print(", y:");
  Serial.print(y);
  Serial.print(", sw:");
  Serial.println(sw);
  delay(100);
}
