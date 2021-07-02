const int nguras = 9, ngisi = 8;
void setup() {
  // put your setup code here, to run once:
  pinMode(nguras, OUTPUT);
  pinMode(ngisi, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(nguras, LOW);
  digitalWrite(ngisi, HIGH);
  delay(2000);
  digitalWrite(nguras, HIGH);
  digitalWrite(ngisi, HIGH);
  delay(2000); 
}
