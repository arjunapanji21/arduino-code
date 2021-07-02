#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int wait = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Starting.."); delay(500);
  Serial.println("Ready");
}

void loop() {
  if (Serial.available() > 0) {
    wait = 10;
    String data = Serial.readStringUntil('\n');
    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("PENGECEKAN");
//    lcd.setCursor(0, 1);
//    lcd.print("SUHU: ");
    lcd.print(data);
//    lcd.print(" C");
    //Serial.print("Suhu: ");
    //Serial.println(data);
    delay(150);
  }
  else {
    if (wait <= 0) {
//      lcd.clear();
//      lcd.setCursor(5, 0);
//      lcd.print("STATUS");
//      lcd.setCursor(6, 1);
//      lcd.print("IDLE");
//      delay(100);
    }
    else {
      wait--;
    }
  }
}
