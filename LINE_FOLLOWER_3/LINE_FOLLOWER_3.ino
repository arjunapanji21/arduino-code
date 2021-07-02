#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Sensor garis
#define jKiri A1 // ini Sensor kiri
#define jKanan A0 // ini sensor kanan

//motor a
#define mtrKanan_Maju 12
#define mtrKanan_Mundur 11
#define mtrKanan_PWM 10

//motor b
#define mtrKiri_Maju 4
#define mtrKiri_Mundur 5
#define mtrKiri_PWM 9

bool finish = false;

void setup () {
  pinMode(mtrKanan_Maju, OUTPUT);
  pinMode(mtrKanan_Mundur, OUTPUT);
  pinMode(mtrKanan_PWM, OUTPUT);
  pinMode(mtrKiri_Maju, OUTPUT);
  pinMode(mtrKiri_Mundur, OUTPUT);
  pinMode(mtrKiri_PWM, OUTPUT);

  pinMode(jKanan, INPUT);
  pinMode(jKiri, INPUT);

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Memulai Perintah...");
    delay (300);

    finish = false;
}

void maju (int cpt) {
  
  analogWrite(mtrKiri_PWM, cpt);
  analogWrite(mtrKanan_PWM, cpt);

  digitalWrite(mtrKiri_Maju, HIGH);
  digitalWrite(mtrKiri_Mundur, LOW);

  digitalWrite(mtrKanan_Maju, HIGH);
  digitalWrite(mtrKanan_Mundur, LOW);

}

void mundur (int cpt) {
  
  analogWrite(mtrKiri_PWM, cpt);
  analogWrite(mtrKanan_PWM, cpt);

  digitalWrite(mtrKiri_Maju, LOW);
  digitalWrite(mtrKiri_Mundur, HIGH);

  digitalWrite(mtrKanan_Maju, LOW);
  digitalWrite(mtrKanan_Mundur, HIGH);
  
}

void kiri (int cpt1,int cpt2){
  
  analogWrite(mtrKiri_PWM, cpt1);
  analogWrite(mtrKanan_PWM, cpt2);

  digitalWrite(mtrKiri_Maju, LOW);
  digitalWrite(mtrKiri_Mundur, HIGH);

  digitalWrite(mtrKanan_Maju, HIGH);
  digitalWrite(mtrKanan_Mundur, LOW);
}
void kanan (int cpt1,int cpt2){
  
  analogWrite(mtrKiri_PWM, cpt1);
  analogWrite(mtrKanan_PWM, cpt2);

  digitalWrite(mtrKiri_Maju, HIGH);
  digitalWrite(mtrKiri_Mundur, LOW);

  digitalWrite(mtrKanan_Maju, LOW);
  digitalWrite(mtrKanan_Mundur, HIGH);
}

void berhenti(){
  analogWrite(mtrKiri_PWM, 0);
  analogWrite(mtrKanan_PWM, 0);

  digitalWrite(mtrKiri_Maju, LOW);
  digitalWrite(mtrKiri_Mundur, LOW);

  digitalWrite(mtrKanan_Maju, LOW);
  digitalWrite(mtrKanan_Mundur, LOW);
}

void loop (){
  int jKi = analogRead(jKiri);
  int jKa = analogRead(jKanan);
  lcd.clear ();
  lcd.setCursor(0,0);
  lcd.print("JKa ");
  lcd.print(jKa);
  lcd.print(" ");
  lcd.print("JKi ");
  lcd.print(jKi);
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.print("STATUS = ");

  if (jKi > 100 && jKa > 100)
  {
    berhenti();
    finish = true;
  }

  if (jKi > 100 && finish == false)
  {
    lcd.print("KIRI");
    kiri(150, 100);
    delay (100);
  }

  else if (jKa > 100 && finish == false)
  {
    lcd.print("KANAN");
    kanan(150,100);
    delay (100);
  }

  else if (jKa < 100 && jKi < 100 && finish == false)
  {
    maju (60);
  }
  delay (10);
  Serial.println(jKi);
}
