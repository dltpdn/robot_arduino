#define PIN_LED 13    //LED는 디지털 핀 13번에 있음
#define PIN_BTN 7 //버튼은 디지털 핀 7번에 있음

int val = 0;

void setup(){
   pinMode(PIN_LED, OUTPUT);  //LED있는 핀을 출력으로 설정
   pinMode(PIN_BTN, INPUT); //BUTTON있는 핀을 입력으로 설정
}


void loop(){
   val = digitalRead(PIN_BTN);  // 버튼의 입력 값을 저장
   if(val == HIGH){                   // 버튼이 눌림 상태인가?
    digitalWrite(PIN_LED, HIGH);   //LED를 켠다 
    
  }else{
    digitalWrite(PIN_LED, LOW);    // LED를 끈다
  }
}
