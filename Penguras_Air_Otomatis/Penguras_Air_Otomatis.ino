//DEKLARASI LIBRARY
#include <Wire.h>
#include <LiquidCrystal.h>

//DEKLARASI LCD
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//PIN POMPA
const int ngisi = 8, nguras = 9;

int state = 0; // state 0 = pompa mati, state 1 = pompa nguras aktif, state 2 = pompa ngisi aktif.

void setup() {
  pinMode(ngisi, OUTPUT);
  pinMode(nguras, OUTPUT);
  digitalWrite(ngisi, HIGH); // Pompa Mati (Aktif Low)
  digitalWrite(nguras, HIGH); // Pompa Mati (Aktif Low)
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Program Starting..");
}

void loop() {
  int turbiditySensor = analogRead(A1); // nilai analog 0 sampai 1024
  int waterSensor = analogRead(A0); // nilai analog 0 sampai 1024

  // rumus mencari nilai tegangan
  float tegangan = turbiditySensor * (5.0 / 1024);

  // rumus mencari nilai kekeruhan
  float kekeruhan = 100.0 - (tegangan / 3.16) * 100.0;
  int hasil = kekeruhan; // hasil = NTU

  if (kekeruhan < 0) {
    hasil = 0; // supaya nilai tidak minus
  }

  // KONDISI MENGURAS AIR
  if (hasil > 30 && waterSensor > 400) {
    //aktifkan pompa untuk menguras
    state = 1;
    digitalWrite(nguras, LOW); //POMPA ON (AKTIF LOW)
    delay(100);
  }
  else if (waterSensor < 400) {
    //matikan pompa penguras
    state = 0;
    digitalWrite(nguras, HIGH); //POMPA OFF
    delay(100);
  }

  // KONDISI MENGISI AIR
  if (waterSensor < 500) {
    state = 2;
    digitalWrite(ngisi, LOW); //POMPA ON
    delay(100);
  }
  else if (hasil < 22 && waterSensor >= 580) {
    state = 0;
    digitalWrite(ngisi, HIGH); //POMPA OFF
    delay(100);
  }

  //DISPLAY LCD
  if (hasil < 22 && state == 0) { // Tampil LCD untuk status jernih
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WL=");
    lcd.print(waterSensor);
    lcd.setCursor(8, 0);
    lcd.print("NTU=");
    lcd.print(hasil);
    lcd.setCursor(0, 1);
    lcd.print("STATUS: JERNIH");
  }
  else if (hasil > 22 && state == 0) { // Tampil LCD untuk status keruh
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WL=");
    lcd.print(waterSensor);
    lcd.setCursor(8, 0);
    lcd.print("NTU=");
    lcd.print(hasil);
    lcd.setCursor(0, 1);
    lcd.print("STATUS: KERUH");
  }
  else if (state == 1) { // Tampil LCD untuk status menguras
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WL=");
    lcd.print(waterSensor);
    lcd.setCursor(8, 0);
    lcd.print("NTU=");
    lcd.print(hasil);
    lcd.setCursor(0, 1);
    lcd.print("=> MENGURAS...");
  }
  else if (state == 2) { // Tampil LCD untuk status mengisi
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WL=");
    lcd.print(waterSensor);
    lcd.setCursor(8, 0);
    lcd.print("NTU=");
    lcd.print(hasil);
    lcd.setCursor(0, 1);
    lcd.print("=> MENGISI...");
  }


  delay(500);
}
