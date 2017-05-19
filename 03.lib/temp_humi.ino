#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600);
	Serial.println("DHTxx test!");
	dht.begin();
}

void loop() {
	delay(2000);
	float h = dht.readHumidity(); // 습도
	float t = dht.readTemperature(); // 섭씨온도
	float f = dht.readTemperature(true);// 화씨온도
	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}
	float hi = dht.computeHeatIndex(f, h); //열파지수
	Serial.print("Humidity: "); 
	Serial.print(h);
	Serial.print(" %\t");
	Serial.print("Temperature: "); 
	Serial.print(t);
	Serial.print(" *C ");
	Serial.print(f);
	Serial.print(" *F\t");
	Serial.print("Heat index: ");
	Serial.print(hi);
	Serial.println(" *F");
}

