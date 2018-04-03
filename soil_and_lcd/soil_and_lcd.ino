//#include <LiquidCrystal_I2C.h>
//#include <LCD.h>
#include <Wire.h>

//#define I2C_ADDR 0x27 // กำหนดตำแหน่ง Address ของ I2C
//#define BACKLIGHT_PIN 3
#define PIN9_Analog 9
#define PIN10_Digital 10

//LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

void setup(){
  Serial.begin(9600);
  
  //pinMode(BACKLIGHT_PIN, OUTPUT);
  pinMode(PIN9_Analog, OUTPUT);
  pinMode(PIN10_Digital, OUTPUT);
  
  //digitalWrite(BACKLIGHT_PIN, HIGH);
  //digitalWrite(PIN9_Analog, HIGH);
  //digitalWrite(PIN10_Digital, HIGH);
  delay(3000);
  
  //lcd.begin(16,2);
}

void loop(){
  int analogValue = analogRead(A0);
  //int digitalValue = digitalRead(13);
  Serial.print("Analog : ");
  Serial.println(analogValue);
  //Serial.print("Digital : ");
  //Serial.println(digitalValue);
  
  //lcd.setCursor(0,0);
  //lcd.print("Analog: ");
  //lcd.print(analogValue);
  //lcd.setCursor(0,1);
  //lcd.print("Digital: ");
  //lcd.print(digitalValue);
  delay(100);
  //lcd.clear();
}
