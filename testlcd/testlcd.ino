#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

#define BACKLIGHT_PIN     13
void setup() {
  //put your setup code here, to run once:
  pinMode( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  lcd.begin(16,2);
  lcd.home();
  lcd.print("HELLO");
  lcd.setCursor(0,1);
  lcd.print("Analog");
}

void loop() {
  // put your main code here, to run repeatedly:

}
