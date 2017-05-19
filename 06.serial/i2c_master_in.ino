#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(9600);
}

void loop(){
  Wire.requestFrom(2, 6);  // slave 주소는 2
  while(Wire.available()){
    char c = Wire.read(); 
    Serial.print(c);      
  }
  Serial.println();
  delay(500);
}
