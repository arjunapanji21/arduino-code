#define ENA 10  // Motor 1 PWM
#define EN1 8  // Motor 1 forward
#define EN2 11   // Motor 1 backward
#define EN3 6   // Motor 2 forward
#define EN4 7   // Motor 2 backward
#define ENB 9   // Motor 2 PWM

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  maju(75);

}

void maju(int spd) {
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);

  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
}
