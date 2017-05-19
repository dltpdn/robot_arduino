#include <MyLib.h>


MyLib mylib("Hello");
void setup() {
  Serial.begin(9600);

}

void loop() {
  mylib.sayHello("Hong gil dong");
}
