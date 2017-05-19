#include <SoftwareSerial.h>
#define RX 2
#define TX 3 

SoftwareSerial bt(RX, TX);
 
void setup(){
  Serial.begin(9600);
  bt.begin(9600);
}
void loop(){
  if (bt.available()) {       
    Serial.write(bt.read());
  }
  if (Serial.available()) {         
    bt.write(Serial.read()); 
  }
}
