#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <DHT.h>
#include <Wire.h>

  //LCD Module Setup
  #define I2C_ADDR 0x27 // ตำแหน่งของ I2C
  #define BACKLIGHT_PIN 3
    
  //Define Pin For Relay
  #define PIN8_PumpSoil 8  //pin 8
  #define PIN9_PumpSpray 9 //pin 9
    
  LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

  unsigned long timer;
  
  DHT dht;
  
void setup(){
  Serial.begin(9600);
  
  //Setup All The Arduino Pin
  pinMode(PIN8_PumpSoil, OUTPUT);
  pinMode(PIN9_PumpSpray, OUTPUT);

  dht.setup(4);

  //Turn OFF any power to the Relay channels
  digitalWrite(BACKLIGHT_PIN, HIGH);
  digitalWrite(PIN8_PumpSoil,HIGH);
  digitalWrite(PIN9_PumpSpray,HIGH);
  delay(1000); //Wait 1 seconds before starting sequence

  timer = 0;

  lcd.begin (16,2);
  lcd.setCursor(0,0);
  lcd.print("  System Begin");
  delay(2000);
  lcd.clear();
} 

void loop() {
  //Begin Module Humidty, Temperature
  float humid_1 = analogRead(A0);
  float humid_2 = analogRead(A1);
  float temperature_air = dht.getTemperature();
      
  if(percentage() <= 2.25 && percentage() >= 0){
    for(int wait=0; wait<1000; wait++){
      float temperature_air = dht.getTemperature();
      if((millis() - timer ) >= 1000){
        lcd.clear();
        print_humid("Dry : ", percentage(), "%");
        print_temp("Temp : ", temperature_air, "C");
        timer = millis();
      }
      digitalWrite(PIN8_PumpSoil,LOW);
      Serial.println(wait);
    }
    
    for(int wait=0; wait<1000; wait++){
      float temperature_air = dht.getTemperature();
      if((millis() - timer ) >= 1000){
        lcd.clear();
        print_humid("Dry : ", percentage(), "%");
        print_temp("Temp : ", temperature_air, "C");
        timer = millis();
      }
      digitalWrite(PIN8_PumpSoil,HIGH);
      Serial.println(wait);
    }
  }
  
  else if (percentage() <= 41.25 && percentage() >= 2.35){
    for(int wait=0; wait<1000; wait++){
      float temperature_air = dht.getTemperature();
      if((millis() - timer ) >= 1000){
        lcd.clear();
        print_humid("Low : ", percentage(), "%");
        print_temp("Temp : ", temperature_air, "C");
        timer = millis();
      }
      digitalWrite(PIN8_PumpSoil,LOW);
      Serial.println(wait);
    }
    for(int wait=0; wait<1000; wait++){
      float temperature_air = dht.getTemperature();
      if((millis() - timer ) >= 1000){
        lcd.clear();
        print_humid("Low : ", percentage(), "%");
        print_temp("Temp : ", temperature_air, "C");
        timer = millis();
      }
      digitalWrite(PIN8_PumpSoil,HIGH);
      Serial.println(wait);
    }
  }
  else if (percentage() <= 50.05 && percentage() >= 41.35){
    for(int wait=0; wait<1000; wait++){
      float temperature_air = dht.getTemperature();
      if((millis() - timer ) >= 1000){
        lcd.clear();
        print_humid("Normal : ", percentage(), "%");
        print_temp("Temp : ", temperature_air, "C");
        timer = millis();
      }
      digitalWrite(PIN8_PumpSoil,LOW);
      Serial.println(wait);
      
    }
    for(int wait=0; wait<1000; wait++){
      float temperature_air = dht.getTemperature();
      if((millis() - timer ) >= 1000){
        lcd.clear();
        print_humid("Normal : ", percentage(), "%");
        print_temp("Temp : ", temperature_air, "C");
        timer = millis();
      }
      digitalWrite(PIN8_PumpSoil,HIGH);
      Serial.println(wait);
    }
  }
  else if (percentage() <= 56.01 && percentage() >= 50.15){
    if((millis() - timer ) >= 1000){
      lcd.clear();
      print_humid("Good : ", percentage(), "%");
      print_temp("Temp : ", temperature_air, "C");
      timer = millis();
    }
    digitalWrite(PIN8_PumpSoil,HIGH);
  }
  else{
    if((millis() - timer ) >= 1000){
      lcd.clear();
      print_humid("Over : ", percentage(), "%");
      print_temp("Temp : ", temperature_air, "C");
      timer = millis();
    }
    digitalWrite(PIN8_PumpSoil,HIGH);
  }
delay(1000);
}

int print_humid(String sta, float h, String sign) {
  lcd.setCursor(0,0);
  lcd.print(sta + h + sign);
  Serial.println(sta + h + sign);
}

int print_temp(String temp, float t, String sign){
  lcd.setCursor(0,1);
  lcd.print(temp + t + ((char)223) + sign);
  Serial.println(temp + t + sign);
}

float percentage(){
  float humid_1 = analogRead(A0);
  float humid_2 = analogRead(A1);
  float average = ((humid_1 + humid_2) / 2);
  float percent = (abs(abs(((average / 1023) * 100) - 100)));
  return percent;
}
