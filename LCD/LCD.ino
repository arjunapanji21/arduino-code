#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // initialize lcd
  lcd.init();
  // turn on lcd backlight
  lcd.backlight();
}

void loop() {
  // print "Hello" and move it from left to the right of the lcd display
  for (int x = 0; x < 20; x++) {
    lcd.clear();
    lcd.setCursor(x, 0);
    lcd.print("Hello");
    delay(300);
  }

  // print "World" and move it from right to the left of the lcd display
  for (int x = 16; x >= 0; x--) {
    lcd.clear();
    lcd.setCursor(x, 0);
    lcd.print("World");
    delay(300);
  }
}
