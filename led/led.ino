#define led1 D5
#define led2 D6
#define led3 D7
#define led4 D8

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  Serial.println("LED Aktif");
//  delay(2000);
//  digitalWrite(led1, LOW);
//  digitalWrite(led2, LOW);
//  digitalWrite(led3, LOW);
//  digitalWrite(led4, LOW);
//  Serial.println("LED Mati");
//  delay(2000);
}
