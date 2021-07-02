int s1 = A0;    // select the input pin for the potentiometer
int led1 = 13;      // select the pin for the LED
int ns1 = 0;  // variable to store the value coming from the sensor
int a;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(led1, OUTPUT);
  pinMode(s1, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  ns1 = analogRead(s1);
  if(ns1 < 930){
    a = 0;
  }
  else if (ns1 >= 930){
    a = 1;
  }
  Serial.println(a);
  delay(100);
}
