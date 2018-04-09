#include <DHT.h>

unsigned long timer1;

DHT dht;

void setup() {
  Serial.begin(9600);

  timer1 = 0;

  dht.setup(4);
}

void loop() {
  float humid_1 = analogRead(A0);
  float humid_2 = analogRead(A1);
  float temperature_air = dht.getTemperature();

  if(percentage() <= 2.25 && percentage() >= 0){
    for(int wait=0; wait<600; wait++){
      float temperature_air = dht.getTemperature();
      if((millis() - timer1) >= 1000){
      print_humid("Dry : ", percentage(), "%");
      print_temp("Temperature : ", temperature_air, "C");
      timer1 = millis();
      }
      Serial.println(wait);
    }
  }
}

int print_humid(String sta, float h, String sign) {
  //lcd.setCursor(0,0);
  //lcd.print(sta + h + sign);
  Serial.println(sta + h + sign);
}

int print_temp(String temp, float t, String sign){
  //lcd.setCursor(0,1);
  //lcd.print(temp + t + sign);
  Serial.println(temp + t + sign);
}

float percentage(){
  float humid_1 = analogRead(A0);
  float humid_2 = analogRead(A1);
  float average = ((humid_1 + humid_2) / 2);
  float percent = (abs(abs(((average / 1023) * 100) - 100)));
  return percent;
}
