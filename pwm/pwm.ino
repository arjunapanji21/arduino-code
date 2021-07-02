//inisialisasi pin
int r1 = 9;
int r2 = 10;
 
int pwm = 255; //ubah nilai pwm dari -255 sampai 255 untuk mengatur kecepatan
 
void setup() {
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
}
 
void loop() {
  if (pwm >= 0 && pwm <= 255) {
     analogWrite(r1, pwm);
     analogWrite(r1, 0);
     //apabila nilai pwm positif maka motor berputar misal ke kanan
  }
  else if (pwm < 0 && pwm >= -255) {
     analogWrite(r1, 0);
     analogWrite(r2, -1*pwm);
     //maka selain kondisi di atas maka motor berputar lawannya
  }
}
