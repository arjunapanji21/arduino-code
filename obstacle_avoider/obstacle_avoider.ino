#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Driver MotorDC
// Motor A
#define mtrKanan_Maju 11    // pin driver1
#define mtrKanan_Mundur 12  // pin driver2
#define mtrKanan_PWM 10     // pin pwmA

//Motor B
#define mtrKiri_Maju 8      // pin driver3
#define mtrKiri_Mundur 7    // pin driver4
#define mtrKiri_PWM 9       // pin pwmB

// Sensor Ultrasonic
#define echo1 2 // pin echo kiri
#define trig1 3 // pin trigger kiri

#define echo2 6 // pin echo depan
#define trig2 13 // pin trigger depan

#define echo3 5 // pin echo kanan
#define trig3 4 // pin trigger kanan

long waktu1, waktu2, waktu3;
int jarak1, jarak2, jarak3, count = 0, pos = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(mtrKanan_Maju, OUTPUT);
  pinMode(mtrKanan_Mundur, OUTPUT);
  pinMode(mtrKanan_PWM, OUTPUT);
  pinMode(mtrKiri_Maju, OUTPUT);
  pinMode(mtrKiri_Mundur, OUTPUT);
  pinMode(mtrKiri_PWM, OUTPUT);

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Program Starting...");
  delay(500);
  lcd.clear();

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  bacaKiri();
  bacaDepan();
  bacaKanan();

  int left = jarak1;
  int front = jarak2;
  int right = jarak3;

  if (front > 10){
    maju(100);
    delay(100);
  }
  else if(front < 10 && right < 6){
    kiri(100,100);
    delay(100);
  }
  else if(front < 10 && left < 6){
    kanan(100,100);
    delay(100);
  }
  else if(front < 10 && left < 6 && right < 6){
    mundur(100);
    delay(100);
  }
  else{
    berhenti();
  }
  delay(50);
  lcd.clear();
}

void bacaDepan() {
  // Clears the trigPin condition
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  waktu2 = pulseIn(echo2, HIGH);

  // Calculating the distance
  jarak2 = waktu2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor
  Serial.print("Jarak Depan = ");
  Serial.print(jarak2);
  Serial.println(" cm");

  lcd.setCursor(7, 0);
  lcd.print(jarak2);
  delay(50);
}

void bacaKiri() {
  // Clears the trigPin condition
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  waktu1 = pulseIn(echo1, HIGH);

  // Calculating the distance
  jarak1 = waktu1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor
  Serial.print("Jarak Kiri = ");
  Serial.print(jarak1);
  Serial.println(" cm");

  lcd.setCursor(0, 1);
  lcd.print(jarak1);
  delay(50);
}

void bacaKanan() {
  // Clears the trigPin condition
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  waktu3 = pulseIn(echo3, HIGH);

  // Calculating the distance
  jarak3 = waktu3 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor
  Serial.print("Jarak Kanan= ");
  Serial.print(jarak3);
  Serial.println(" cm");

  lcd.setCursor(13, 1);
  lcd.print(jarak3);
  delay(50);
}

void maju(int spd) {
  analogWrite(mtrKanan_PWM, spd);
  analogWrite(mtrKiri_PWM, spd);

  digitalWrite(mtrKanan_Maju, HIGH);
  digitalWrite(mtrKanan_Mundur, LOW);

  digitalWrite(mtrKiri_Maju, HIGH);
  digitalWrite(mtrKiri_Mundur, LOW);
}

void mundur(int spd) {
  analogWrite(mtrKanan_PWM, spd);
  analogWrite(mtrKiri_PWM, spd);

  digitalWrite(mtrKanan_Maju, LOW);
  digitalWrite(mtrKanan_Mundur, HIGH);

  digitalWrite(mtrKiri_Maju, LOW);
  digitalWrite(mtrKiri_Mundur, HIGH);
}

void kiri(int spd1, int spd2) {
  analogWrite(mtrKanan_PWM, spd1);
  analogWrite(mtrKiri_PWM, spd2);

  digitalWrite(mtrKanan_Maju, HIGH);
  digitalWrite(mtrKanan_Mundur, LOW);

  digitalWrite(mtrKiri_Maju, LOW);
  digitalWrite(mtrKiri_Mundur, HIGH);
}

void kanan(int spd1, int spd2) {
  analogWrite(mtrKanan_PWM, spd1);
  analogWrite(mtrKiri_PWM, spd2);

  digitalWrite(mtrKanan_Maju, LOW);
  digitalWrite(mtrKanan_Mundur, HIGH);

  digitalWrite(mtrKiri_Maju, HIGH);
  digitalWrite(mtrKiri_Mundur, LOW);
}

void berhenti() {
  analogWrite(mtrKanan_PWM, 0);
  analogWrite(mtrKiri_PWM, 0);

  digitalWrite(mtrKanan_Maju, LOW);
  digitalWrite(mtrKanan_Mundur, LOW);

  digitalWrite(mtrKiri_Maju, LOW);
  digitalWrite(mtrKiri_Mundur, LOW);
}
