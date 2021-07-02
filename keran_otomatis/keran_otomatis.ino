//Library
#include <Wire.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

#define pompa1 10
#define pompa2 11

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 4);

//Sensor Berat(LoadCell)
HX711 scale;
uint8_t LC_data = A1;
uint8_t LC_clock = A0;
float calibration_factor = -415000;
float berat = 0;

//Keypad
const byte baris = 4;
const byte kolom = 4;
char tombol[baris][kolom] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinBaris[baris] = {5, 4, 3, 2};
byte pinKolom[kolom] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(tombol), pinBaris, pinKolom, baris, kolom);

String state = "MENU AWAL";
int slide = 0, count = 0;

void testKeypad() {
  lcd.setCursor(0, 0);
  for (int i = 0; i < 20; i++) {
    lcd.print("=");
  }
  lcd.setCursor(0, 1);
  lcd.print("SILAHKAN TEKAN");
  lcd.setCursor(0, 2);
  lcd.print("TOMBOL KEYPAD: ");
  lcd.setCursor(0, 3);
  for (int i = 0; i < 20; i++) {
    lcd.print("=");
  }
  char key = keypad.getKey();
  if (key) {
    //lcd.clear();
    lcd.setCursor(16, 2);
    lcd.print(key);
  }
  delay(100);
}

void bacaBerat() {
  scale.set_scale(calibration_factor);
  berat = scale.get_units();
  if (berat < 0) {
    berat = -berat;
    delay(10);
  }
  lcd.setCursor(0, 2);
  lcd.print("Berat= ");
  lcd.print(berat, 1);
  lcd.setCursor(16, 2);
  lcd.print(" Kg");

  //Serial.print("Berat = ");
  //Serial.print(berat, 1);
  //Serial.println(" Kg");

  delay(50);
}

void setup() {
  pinMode(pompa1, OUTPUT);
  pinMode(pompa2, OUTPUT);
  digitalWrite(pompa1, HIGH);
  digitalWrite(pompa2, HIGH);
  lcd.init();
  lcd.backlight();
  delay(300);
  lcd.clear();
  //=============DISPLAY LCD================//
  lcd.setCursor(0, 0);
  lcd.print("PROGRAM STARTING...");
  delay(50);
  lcd.setCursor(0, 1);
  for (int i = 0; i < 20; i++) {
    lcd.print("=");
    delay(5);
  }
  lcd.setCursor(0, 2);
  for (int i = 0; i < 20; i++) {
    lcd.print("=");
    delay(5);
  }
  lcd.setCursor(0, 3);
  for (int i = 0; i < 20; i++) {
    lcd.print("=");
    delay(5);
  }
  //=======================================//
  Serial.begin(9600);
  scale.begin(LC_data, LC_clock);
  scale.tare();
  long zero_factor = scale.read_average();
  //keypad.addEventListener(keypadEvent);
  lcd.clear();
}

void loop() {
  if (state == "MENU AWAL") {
    if (slide == 0) {
      lcd.setCursor(0, 1); lcd.print("[A] INPUT BERAT");
      lcd.setCursor(0, 2); lcd.print("[B] MODE TIMBANGAN");
      lcd.setCursor(0, 3); lcd.print("[C] MENGURAS");
      lcd.setCursor(0, 0); lcd.print("TEKAN TOMBOL:");
      char key = keypad.getKey();
      if (key == 'A') {
        state = "INPUT BERAT";
        lcd.clear();
      }
      else if (key == 'B') {
        state = "MENIMBANG";
        lcd.clear();
      }
      else if (key == 'C') {
        state = "MENGURAS";
        count = 100;
        lcd.clear();
      }
      else if (key == 'D') {
        slide == 1;
        lcd.clear();
      }
    }
    else if (slide == 1) {
      lcd.setCursor(0, 0); lcd.print("[A] ---");
      lcd.setCursor(0, 1); lcd.print("[B] ---");
      lcd.setCursor(0, 2); lcd.print("[C] ---");
      lcd.setCursor(0, 3); lcd.print("[D] NEXT >>");
      char key = keypad.getKey();
      if (key == 'A') {
        //state = "INPUT BERAT";
        //lcd.clear();
      }
      else if (key == 'B') {
        //state = "INPUT HARGA";
        //lcd.clear();
      }
      else if (key == 'C') {
        //state = "POMPA"
        //lcd.clear();
      }
      else if (key == 'D') {
        slide == 0;
        lcd.clear();
      }
    }
  }
  else if (state == "INPUT BERAT") {
    if (slide == 0) {
      lcd.setCursor(0, 0); lcd.print("[1] 0.5 KG");
      //lcd.setCursor(0, 1); lcd.print("[2]  1 KG");
      //lcd.setCursor(0, 2); lcd.print("[3]1.5 KG");
      lcd.setCursor(0, 3); lcd.print("[D] KE MENU AWAL");

      lcd.setCursor(12, 0); lcd.print("[2] 1 KG");
      //lcd.setCursor(11, 0); lcd.print("[5]  2 KG");
      //lcd.setCursor(11, 1); lcd.print("[6]2.5 KG");
      //lcd.setCursor(11, 2); lcd.print("[7]  3 KG");
      char key = keypad.getKey();
      if (key == '1') {
        state = "0.5 KG";
        lcd.clear();
      }
      else if (key == '2') {
        state = "1 KG";
        lcd.clear();
      }
    }
  }
  else if (state == "MENIMBANG") {
    scale.set_scale(calibration_factor);
    berat = scale.get_units();
    if (berat < 0) {
      berat = -berat;
      delay(10);
    }
    lcd.setCursor(0, 0);
    lcd.print("MENIMBANG: ");
    lcd.setCursor(0, 2);
    lcd.print("Berat = ");
    lcd.print(berat, 1);
    lcd.setCursor(17, 2);
    lcd.print(" Kg");
    lcd.setCursor(0, 3);
    lcd.print("[D] KE MENU AWAL");
    char key = keypad.getKey();
    if (key == 'D') {
      state = "MENU AWAL";
      lcd.clear();
    }
  }
  else if (state == "MENGURAS") {
    bacaBerat();
    lcd.setCursor(0, 0);
    lcd.print("SEDANG PROSES...");
    //lcd.print(count);
    if (berat > 0) {
      digitalWrite(pompa2, LOW);
      if (count > 0) {
        count = count - 1;
        if(count == 99 || count == 9){
          lcd.clear();
        }
      }
      else {
        digitalWrite(pompa2, HIGH);
        state = "MENU AWAL";
        lcd.clear();
      }
    }
    else if (berat <= 0 || count <= 0) {
      digitalWrite(pompa2, HIGH);
      state = "MENU AWAL";
      lcd.clear();
    }
  }
  else if (state == "0.5 KG") {
    bacaBerat();
    lcd.setCursor(0, 0);
    lcd.print("SEDANG PROSES...");
    if (berat < 0.4) {
      digitalWrite(pompa1, LOW);
    }
    else {
      digitalWrite(pompa1, HIGH);
      delay(1000);
      state = "MENGURAS";
      count = 50;
      lcd.clear();
    }
  }
  else if (state == "1 KG") {
    bacaBerat();
    lcd.setCursor(0, 0);
    lcd.print("SEDANG PROSES...");
    if (berat < 0.868) {
      digitalWrite(pompa1, LOW);
    }
    else {
      digitalWrite(pompa1, HIGH);
      delay(1000);
      state = "MENGURAS";
      count = 90;
      lcd.clear();
    }
  }
  Serial.println(count);
  delay(100);
}
