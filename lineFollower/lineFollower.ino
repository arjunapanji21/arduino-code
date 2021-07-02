//VARIABEL PIN SENSOR PHOTODIODA
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int s5 = A4;
int s6 = A5;
int s7 = A6;
int s8 = A7;

//VARIABEL NILAI SENSOR PHOTODIODA
int ns1 = 0;
int ns2 = 0;
int ns3 = 0;
int ns4 = 0;
int ns5 = 0;
int ns6 = 0;
int ns7 = 0;
int ns8 = 0;

void bacaSensor(){
  ns1 = analogRead(s1);
  ns2 = analogRead(s2);
  ns3 = analogRead(s3);
  ns4 = analogRead(s4);
  ns5 = analogRead(s5);
  ns6 = analogRead(s6);
  ns7 = analogRead(s7);
  ns8 = analogRead(s8);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);


  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(s7, INPUT);
  pinMode(s8, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bacaSensor();
 //Serial.println(ns4);
 //Serial.println(ns5);
 
 //berhenti
  if(ns3 >895)
 { 
  digitalWrite(ns4 &&ns5, LOW);
  Serial.println("Berhenti");
 }
 else if(ns6 >895)
 { 
  Serial.println("Berhenti");
 }
 //kanan
 else if(ns1 && ns2 >895)
 { 
  Serial.println("Belok Kanan Lur");
 }
 //kiri
 else if(ns7 && ns8>895)
 {
  Serial.println("Belok Kiri Lur");
 }
 else if(ns4 && ns5 > 895)
 {
  Serial.println("JalanLurus");
 }
/*else if(ns1 && ns2 && ns && > 850)
 {
  Serial.println("Belok kanan" // "Belok kiri");
 }*/
 
 else
 {
  Serial.println("STOP!"); 
 }
  delay(150);
}
