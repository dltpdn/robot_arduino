#include <SPI.h>
char buff[100];

volatile byte pos;
volatile boolean process_it;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
 
  SPCR |= 1<<(SPE);
  SPCR &= ~(1<<(MSTR));
  SPCR |= 1<<(SPIE);
  pos = 0;
  process_it = false;

}

ISR(SPI_STC_vect){
  byte c = SPDR;
  if(pos < sizeof(buff)){
    buff[pos++] = c;
    if(c =='\n'){
      process_it = true;
    }
  }
}
void loop() {
 if(process_it){
   buff[pos] = 0;
   Serial.print(buff);
   pos=0;
   process_it = false;
 }
}
