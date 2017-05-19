#define PIN_ECHO 2
#define PIN_TRIG 3

void setup() {
  Serial.begin(9600);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
}

void loop() {
  long duration;
  int distance;
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2); //Wait for being ready
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
 duration = pulseIn(PIN_ECHO, HIGH); 
 distance = 17160 * duration/1000000;  
  
  Serial.print(distance);
  Serial.println("cm");
delay(500);
}