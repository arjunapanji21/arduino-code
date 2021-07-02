#define WF_SENSOR D3

long currMs = 0, prevMs = 0;
int interval = 1000;
float calibrationFactor = 4.5, flowRate = 0, flowLiter = 0, totalLiter = 0;
volatile byte pulseCount = 0;
byte pulse1Sec = 0;
unsigned long ml;
unsigned int total_ml;

void IRAM_ATTR pulseCounter(){
  pulseCount++;
}

void setup(){
  Serial.begin(9600);
  pinMode(WF_SENSOR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WF_SENSOR), pulseCounter, FALLING);
}

void loop(){
  currMs = millis();
  if(currMs - prevMs > interval){
    pulse1Sec = pulseCount;
    pulseCount = 0;
    flowRate = ((1000.0 / (millis() - prevMs)) * pulse1Sec) / calibrationFactor;
    prevMs = millis();

    ml = (flowRate / 60)*1000;
    flowLiter = (flowRate / 60);

    total_ml += ml;
    totalLiter += flowLiter;

    Serial.print("Flow Rate: ");
    Serial.print(float(flowRate));
    Serial.print("L/min");
    Serial.print("\t");

    Serial.print("Total Liter: ");
    Serial.print(total_ml);
    Serial.print("ml / ");
    Serial.print(totalLiter);
    Serial.println("L");

    Serial.print("Harga: ");
    Serial.print(totalLiter * 4);
    Serial.print("\t");
  }
}
