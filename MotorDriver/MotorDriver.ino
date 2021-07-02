// deklarasi PIN Motor Driver
#define ENA 11
#define IN1 8 // roda kanan mundur
#define IN2 7 // roda kanan maju
#define IN3 6 // roda kiri mundur
#define IN4 5 // roda kiri maju
#define ENB 10

void setup(){
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop(){
  
}

void maju(int spd_maju){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, spd_maju);
  analogWrite(ENB, spd_maju);
}

void mundur(int spd_maju){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, spd_maju);
  analogWrite(ENB, spd_maju);
}

void kanan(int spd_belok){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, spd_belok);
  analogWrite(ENB, spd_belok);
}

void kiri(int spd_belok){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, spd_belok);
  analogWrite(ENB, spd_belok);
}

void berhenti(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
