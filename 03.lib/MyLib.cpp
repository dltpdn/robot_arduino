#include "Arduino.h"
#include "MyLib.h"



MyLib::MyLib(String greeting){
  _greeting = greeting;
}

void MyLib::sayHello(String name){
  Serial.println(_greeting + " " + name + "!!");
} 
