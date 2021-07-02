#include <SoftwareSerial.h>
SoftwareSerial sms(2, 3); // Tx | Rx

#define echo 4        // echo ultrasonic
#define trig 5        // trigger ultrasonic
#define btn_merah 7   // tombol lampu merah
#define btn_hijau 8   // tombol lampu hijau
#define led_merah 10  // lampu merah
#define led_hijau 11  // lampu hijau

// defines variables
long waktu; // variable for the duration of sound wave travel
int jarak, timer, limit = 30;
String state = "merah";

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(led_merah, OUTPUT);
  pinMode(led_hijau, OUTPUT);

  pinMode(btn_merah, INPUT);
  pinMode(btn_hijau, INPUT);

  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800L
  sms.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  sms.println("AT"); //Once the handshake test is successful, it will back to OK
  cekKoneksi();
  sms.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  cekKoneksi();
  sms.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  cekKoneksi();
  sms.println("AT+CREG?"); //Check whether it has registered in the network
  cekKoneksi();

  //Membaca Pesan Masuk
  sms.println("AT+CMGF=1"); // Configuring TEXT mode
  cekKoneksi();
  sms.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  cekKoneksi();
}

void loop() {
  // put your main code here, to run repeatedly:
  cekKoneksi();
  cekLampu();
  if (state == "merah") {
    cekJarak();
    if (jarak < 10) {
      kirim_pesan();
    }
  }
  else {

  }
  //Serial.println(timer);
}

void cekLampu() {
  if (timer <= 0 && state == "hijau") {
    state = "merah";
    digitalWrite(led_merah, HIGH);
    digitalWrite(led_hijau, LOW);
  }
  else if (timer <= 0 && state == "merah") {
    state = "hijau";
    digitalWrite(led_merah, LOW);
    digitalWrite(led_hijau, HIGH);
  }

  if (timer > 0) {
    timer -= 1;
  }
  else {
    timer = limit;
  }
}

// fungsi untuk mengirimkan pesan melalui sms gateaway
void kirim_pesan() {
  //Mengirim SMS
  sms.println("AT+CMGF=1"); // Configuring TEXT mode
  cekKoneksi();
  //sms.println("AT+CMGS=\"+6282279288898\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  sms.println("AT+CMGS=\"+6285281620164\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  cekKoneksi();
  sms.print("Ada pengendara yang melewati batas RHK dan memasuki Zebra-cross !!"); //text content
  cekKoneksi();
  sms.write(26);
  delay(1000);
  Serial.println("");
  Serial.println("Pesan Terkirim!");
}

// fungsi untuk memeriksa koneksi dari modul SIM800l ke Arduino
void cekKoneksi() {
  delay(250);
  while (Serial.available())
  {
    sms.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (sms.available())
  {
    Serial.write(sms.read());//Forward what Software Serial received to Serial Port
  }
}

void cekJarak() {
  // Clears the trigPin condition
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  waktu = pulseIn(echo, HIGH);

  // Calculating the distance
  jarak = waktu * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
}
