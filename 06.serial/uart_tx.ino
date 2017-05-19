#include <SoftwareSerial.h>

#define RX  2
#define TX  3

SoftwareSerial serial(RX, TX);
int count=0;
void setup() {
  Serial.begin(9600);
  serial.begin(9600);
  Serial.println("ready to send.");
}

void loop() {
  serial.println("Hello there!" + String(count++));
  Serial.println("sending " + String(count));
  delay(1000);
}