#include <SoftwareSerial.h>
SoftwareSerial sms(3, 2); // Tx | Rx

#define pintu 4 // PIN Relay Pintu
#define buzzer 13 // PIN Buzzer

int state;

void setup() {
  // put your setup code here, to run once:
  pinMode(pintu, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);

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

  state = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  cekKoneksi();
  cekPintu();
}

// fungsi untuk mengirimkan pesan melalui sms gateaway
void kirim_pesan() {
  //Mengirim SMS
  sms.println("AT+CMGF=1"); // Configuring TEXT mode
  cekKoneksi();
  sms.println("AT+CMGS=\"+62895621833463\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  //sms.println("AT+CMGS=\"+6282279288898\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  cekKoneksi();
  sms.print("Ada seseorang memasuki ruangan sarang walet tanpa izin !!!"); //text content
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

// fungsi untuk memeriksa kondisi pada pintu
void cekPintu() {
  int bacaSensor = digitalRead(pintu);
  if (bacaSensor == HIGH) {
    if (state == 0) {
      kirim_pesan();
      state = 1;
      Serial.println("Pintu Terbuka");
    }
    alarm_on();
  }
  else if (bacaSensor == LOW) {
    if (state == 1) {
      Serial.println("Pintu Tertutup");
      state = 0;
    }
    alarm_off();
  }
}

// fungsi untuk membuat dering pendek dengan duty cycle 50%,selama 0,8 s
void alarm_on() {
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  delay(5);
}

void alarm_off() {
  digitalWrite(buzzer, LOW);
}
