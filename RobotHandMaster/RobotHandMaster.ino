//송신부 프로그램
#define ZERO 0 // flex 센서 10k옴 초기값
#define MAX 1023
#define SIZE 6

// int handZero[SIZE] = {220, 412, 750, 550, 270,0};
// int handMax[SIZE]  = {850, 1023, 0, 0, 1023,180};

void setup() {
  Serial.begin(9600);   //통신속도 9600
}

void loop() {
  String sendVal = "";
  
  for (int i = 0; i < 6; i++)
  {
    int val = analogRead(A0 + i);
    // int vmap = map(val, handZero[i], handMax[i], 0, 180);
    //if (vmap > 179) vmap = 179;
    sendVal += val;
    sendVal += "_";
  }
  Serial.println(sendVal);
  delay(100);
}
