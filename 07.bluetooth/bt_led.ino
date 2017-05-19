#include <SoftwareSerial.h>
#define RX 2
#define TX 3 
#define PIN_LED 13

SoftwareSerial bt(RX, TX);
char val;
 
void setup(){
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop(){
  if (bt.available()) {       
    val = bt.read();
    if(val == '1'){
      digitalWrite(PIN_LED, HIGH);
      bt.println("LED ON");
      Serial.println("LED ON");
    }else if(val == '0'){
      digitalWrite(PIN_LED, LOW);
      bt.println("LED Off");
      Serial.println("LED Off");
    }
  }
}
