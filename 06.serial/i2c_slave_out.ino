#include <Wire.h>

void setup(){
  Wire.begin(2); // slave 주소는 2
  Wire.onRequest(requestEvent); 
}

void loop(){
  delay(100);
}

void requestEvent(){
  Wire.write("hello!"); 

}