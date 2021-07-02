#define sensorAsap A5
#define kipas 7
#define sound 6

int batasWajar = 600; // batas wajar asap

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorAsap, INPUT);
  pinMode(kipas, OUTPUT);
  pinMode(sound, OUTPUT);
  digitalWrite(kipas, HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int asap = analogRead(sensorAsap);

  Serial.print("Nilai Pada Sensor: ");
  Serial.println(asap);

  // Checks if it has reached the threshold value
  if (asap > batasWajar)
  {
    digitalWrite(sound, HIGH);
    Serial.println("ASAP TERDETEKSI");
    digitalWrite(kipas, LOW); // mengaktifkan kipas
  }
  else {
    digitalWrite(kipas, HIGH); // kipas di non-aktifkan
    digitalWrite(sound, LOW);
  }
  delay(100);
}
