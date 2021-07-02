int sizeOf = 6;
int i = 0;
int offset = 0;

char charArr[1600];

String msg = "123456";


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  while ((i < sizeOf) && (charArr[i + offset] != '\0') && (msg[i] != '\0'))
  {
    charArr[i + offset] = msg[i];

    i++;
  }
  Serial.println(charArr);

}
