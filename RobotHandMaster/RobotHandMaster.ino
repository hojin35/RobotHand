//송신부 프로그램
#define ZERO 0 // flex 센서 10k옴 초기값
#define MAX 1023


int handZero[5] = {220, 412, 750, 550, 270};
int handMax[5]  = {850, 1023, 0, 0, 1023};
int analogpins[5] = {A0, A1, A2, A3, A4};

void setup() {
  Serial.begin(9600);   //통신속도 9600
}

void loop() {
  String sendVal = "";
  
  for (int i = 0; i < 5; i++)
  {
    int val = analogRead(analogpins[i]);
    int vmap = map(val, handZero[i], handMax[i], 0, 180);
    //if (vmap > 179) vmap = 179;
    sendVal += vmap;
    sendVal += "_";
  }
  Serial.println(sendVal);
  delay(100);
}
