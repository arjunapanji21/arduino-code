// deklarasi pin motor driver
#define ENA 9
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 10

// deklarasi pin sensor infrared
#define sensor_kanan A0
#define sensor_kiri A1

// membuat variable spd_belok untuk menampung nilai PWM
int spd_belok = 255;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(sensor_kanan, INPUT);
  pinMode(sensor_kiri, INPUT);
  Serial.begin(9600);
}

void loop() {
  // membuat variable lokal untuk menyimpan nilai sensor kiri dan kanan
  int sKanan = analogRead(sensor_kanan);
  int sKiri = analogRead(sensor_kiri);

  // menampilkan nilai sensor ke serial monitor
  Serial.print("Kiri = ");
  Serial.print(sKiri);
  Serial.print("  ");
  Serial.print("Kanan = ");
  Serial.println(sKanan);

  // robot belok kiri jika nilai sensor kanan lebih kecil 
  // dari 50 dan nilai sensor kiri lebih besar dari 50
  if (sKanan <= 50 && sKiri >= 50) {
    kiri();
  }

  // robot belok kanan jika nilai sensor kanan lebih besar 
  // dari 50 dan nilai sensor kiri lebih kecil dari 50
  else if (sKanan >= 50 && sKiri <= 50) {
    kanan();
  }

  // robot akan berhenti jika nilai kedua sensor lebih dari 50
  else if (sKanan >= 50 && sKiri >= 50) {
    berhenti();
  }

  // robot maju jika nilai kedua sensor lebih kecil dari 50
  else {
    // memanggil method maju dengan nilai parameter PWM 65
    maju(65);
  }
}

// method maju
void maju(int spd_maju) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, spd_maju);
  analogWrite(ENB, spd_maju);
}

// method belok kiri
void kiri() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, spd_belok);
  analogWrite(ENB, spd_belok);
}

// method belok kanan
void kanan() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, spd_belok);
  analogWrite(ENB, spd_belok);
}

// method berhenti
void berhenti() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
