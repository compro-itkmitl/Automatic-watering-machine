#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <DHT.h>
#include <Wire.h>
#include <SoftwareSerial.h>


  //LCD Module Setup
  #define BACKLIGHT_PIN 3
    
  //Define Pin For Relay
  #define PIN8_PumpSoil 8  //pin 8
  #define PIN9_PumpSpray 9 //pin 9

  SoftwareSerial ArduinoSerial(6,10); //(RX,TX)
  LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

  int wait;


  unsigned long timer;
  unsigned long timer2;
  
  DHT dht;
  
void setup(){
  Serial.begin(115200);
  ArduinoSerial.begin(4800);
  
  //Setup All The Arduino Pin
  pinMode(PIN8_PumpSoil, OUTPUT);
  pinMode(PIN9_PumpSpray, OUTPUT);
  pinMode(6, INPUT);
  pinMode(10, OUTPUT);

  dht.setup(5);

  //Turn OFF any power to the Relay channels
  digitalWrite(BACKLIGHT_PIN, HIGH);
  digitalWrite(PIN8_PumpSoil,HIGH);
  digitalWrite(PIN9_PumpSpray,HIGH);
  delay(1000);

  timer = 0;
  timer2 = 0;

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

  ArduinoSerial.print(humid_1);
  ArduinoSerial.print('\n');
  ArduinoSerial.print(humid_2);
  ArduinoSerial.print('\n');
  ArduinoSerial.print(percentage());
  ArduinoSerial.print('\n');
  ArduinoSerial.print(temperature_air);
  ArduinoSerial.print('\n');
  
  if(percentage() <= 2.25 && percentage() >= 0){
    for(wait=0; wait<800; wait++){
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
    
    for(wait=0; wait<3000; wait++){
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
    for(wait=0; wait<800; wait++){
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
    for(wait=0; wait<3000; wait++){
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
    for(wait=0; wait<800; wait++){
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
    
    for(wait=0; wait<3000; wait++){
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
  } //End Algo Watering Soil

  //Algo Watering Spray
  if((millis() - timer2 ) >= 3000){
    if(temperature_air > 36){
      for(wait=0; wait<10000; wait++){
        temperature_air = dht.getTemperature();
        if((millis() - timer ) >= 1000){
          lcd.clear();
          print_humid("Normal : ", percentage(), "%");
          print_temp("Temp : ", temperature_air, "C");
          timer = millis();
        }
        digitalWrite(PIN9_PumpSpray,LOW);
        Serial.println(wait);
      }
      digitalWrite(PIN9_PumpSpray,HIGH);
    }
    timer2 = millis();
  } //End Algo Watering Spray
  delay(500);
}

int print_humid(String sta, int h, String sign) {
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
