#define IN1 13
#define IN2 12
#define IN3 8
#define IN4 7
#define PIN_ECHO 2
#define PIN_TRIG 3

char val = '0';
int distance, old_distance;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
}

void forward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void backward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void turn_left(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turn_right(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

int getDistance(){
  long duration;
  int distance;
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2); //Wait for being ready
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH); 
  distance = 17160 * duration/1000000 ;  
  return distance;  
}

void loop() {
   if(Serial.available()){
    val = Serial.read();
    if(val == '0')     stop();
    else if(val == '8')    forward();
    else if(val == '2')   backward();
    else if(val == '4')   turn_left();
    else if(val == '6')   turn_right();
  }

  if(getDistance() < 10){
    distance = getDistance();
    if( distance < 10 && val != '2'){
      if(distance != old_distance){
        Serial.print(val);
        Serial.print(" ");
        Serial.println(distance);
        old_distance = distance;
      }
      stop();
    }
  }
}
