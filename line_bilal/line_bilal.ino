#define ENA 9
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENB 10

#define IR_Kanan 11
#define IR_Kiri 12

int spd = 150;

void setup (){
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IR_Kanan, INPUT);
  pinMode (IR_Kiri, INPUT);
  
  Serial.begin (9600);
}

void loop (){
  int Kanan = digitalRead(IR_Kanan);
  int Kiri = digitalRead(IR_Kiri);
  
  if(Kanan == 1 && Kiri == 0)
  {
    kanan();
  }
  else if (Kanan == 0 && Kiri == 1)
  {
    kiri();
  }
  else if (Kanan == 0 && Kiri == 0)
  {
    maju();
  }
  else if (Kanan == 1 && Kiri == 1)
  {
    berhenti();
  }
  
  Serial.print(Kiri);
  Serial.print(" ");
  Serial.println(Kanan);
  delay (500);
}

void maju (){
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,HIGH);
  digitalWrite (IN4,LOW);
  analogWrite (ENA,65);
  analogWrite (ENB,65);
}

void kanan (){
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,LOW);
  digitalWrite (IN4,HIGH);
  analogWrite (ENA,spd);
  analogWrite (ENB,spd);
}

void kiri (){
  digitalWrite (IN1,LOW);
  digitalWrite (IN2,HIGH);
  digitalWrite (IN3,HIGH);
  digitalWrite (IN4,LOW);
  analogWrite (ENA,spd);
  analogWrite (ENB,spd);
}

void berhenti (){
  digitalWrite (IN1,LOW);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,LOW);
  digitalWrite (IN4,LOW);
  analogWrite (ENA,spd);
  analogWrite (ENB,spd);
}
