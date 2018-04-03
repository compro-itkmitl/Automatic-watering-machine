#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <Wire.h>

  //LCD Module Setup
  #define I2C_ADDR 0x27 // ตำแหน่งของ I2C
  #define BACKLIGHT_PIN 3
    
  //Define Pin For Relay
  #define PIN8_PumpSoil 8  //pin 8
  #define PIN9_PumpSpray 9 //pin 9
    
  LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
  DHT dht;
  
void setup(){
  Serial.begin(9600);
  
  //Setup All The Arduino Pin
  pinMode(PIN8_PumpSoil, OUTPUT);
  pinMode(PIN9_PumpSpray, OUTPUT);
  dht.setup(2);

  //Turn OFF any power to the Relay channels
  digitalWrite(BACKLIGHT_PIN, HIGH);
  digitalWrite(PIN8_PumpSoil,HIGH);
  digitalWrite(PIN9_PumpSpray,HIGH);
  delay(2000); //Wait 2 seconds before starting sequence

  lcd.begin (16,2);
  lcd.setCursor(0,0);
  lcd.print("System Begin");
  delay(2000);
  lcd.clear();
} 

void loop() {
  //Begin Module Humidty, Temperature
  float humidity_soil = analogRead(A0);
  float temperature_air = dht.getTemperature();
  
  //float percentage = percent;
  float percentage = (abs(abs(((humidity_soil / 1023) * 100) - 100)));
  
  if (percentage <= 2.25 && percentage >= 0){
    if (percentage <= 2.25 && percentage >= 0){
      print_humi("Dry : ", percentage, "%");
      print_temp("Temperature : ", temperature_air, "C");
    }
    if (percentage <= 2.25 && percentage >= 0){
      digitalWrite(PIN8_PumpSoil,HIGH);
      Serial.println("Working");
      delay(5000);
      digitalWrite(PIN8_PumpSoil,LOW);
      Serial.println("Stop");
      //delay(10000);
      Serial.println("..........");
    }
  }
  else if (percentage <= 41.25 && percentage >= 2.35){
    if (percentage <= 41.25 && percentage >= 2.35){
      lcd.clear();
      print_humi("Low : ", percentage, "%");
      print_temp("Temperature : ", temperature_air, "C");
    }
    if (percentage <= 41.25 && percentage >= 2.35){
      digitalWrite(PIN8_PumpSoil,HIGH);
      Serial.println("Working");
      delay(5000);
      digitalWrite(PIN8_PumpSoil,LOW);
      Serial.println("Stop");
      //delay(10000);
      Serial.println("..........");
    }
  }
  else if (percentage <= 50.05 && percentage >= 41.35){
    lcd.clear();
    print_humi("Normal : ", percentage, "%");
    print_temp("Temperature : ", temperature_air, "C");
    digitalWrite(PIN8_PumpSoil,HIGH);
    Serial.println("Working");
    delay(5000);
    digitalWrite(PIN8_PumpSoil,LOW);
    Serial.println("Stop");
    //delay(10000);
    Serial.println("..........");
  }
  else if (percentage <= 56.01 && percentage >= 50.15){
    lcd.clear();
    print_humi("Good : ", percentage, "%");
    print_temp("Temperature : ", temperature_air, "C");
    digitalWrite(PIN8_PumpSoil,LOW);
    Serial.println("No Working");
    Serial.println("..........");
  }
  else{
    lcd.clear();
    print_humi("Good : ", percentage, "%");
    print_temp("Temperature : ", temperature_air, "C");
    digitalWrite(PIN8_PumpSoil,LOW);
    Serial.println("No Working");
    Serial.println("..........");
  }
delay(1000);
}

int print_humi(String sta, float h, String sign) {
  //lcd.setCursor(0,0);
  //lcd.print(sta + h + sign);
  Serial.println(sta + h + sign);
}

int print_temp(String temp, float t, String sign){
  //lcd.setCursor(0,1);
  //lcd.print(temp + t + sign);
  Serial.println(temp + t + sign);
}

