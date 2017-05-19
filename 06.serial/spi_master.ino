#include <SPI.h>
void setup() {
  SPI.begin();
  digitalWrite(SS, HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop() {
  const char *p = "Hello World\n";
  digitalWrite(SS, LOW);
  for(int i=0; i<strlen(p); i++){
    SPI.transfer(p[i]);
  }
  digitalWrite(SS, HIGH);
  delay(1000);
}
