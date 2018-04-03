#include "DHT.h"

DHT dht;

void setup()
{
Serial.begin(9600);
Serial.println("DHTxx test!");

dht.setup(2);
}

void loop()
{
  float h = dht.getHumidity(); // ดึงค่าความชื้น
  float t = dht.getTemperature(); // ดึงค่าอุณหภูมิ

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed");
  }
  else{
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(t);
    Serial.println(" *C");
  }
}
