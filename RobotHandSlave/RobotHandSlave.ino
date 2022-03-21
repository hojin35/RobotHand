//수신부 프로그램
#include<stdlib.h>
#define SIZE 5
#define BUFFER_SIZE 50
char buf[BUFFER_SIZE] = {0,};
char char_degree[SIZE][4] = {0,};
int degree[SIZE] = {0,};
int state[SIZE] = {0,};

unsigned long curMicros;
unsigned long preMicros[SIZE] = {0,}; 

int check = 0;
int count = 0;
int j = 0;

void setup()
{
  Serial.begin(9600); //통신속도 9600
  DDRD |= (0x01 << 2 | 0x01 << 3 | 0x01<<4 | 0x01 << 5 | 0x01 << 6);
}

void loop()
{
  curMicros = micros();
//---------------------------- 값 읽기----------
  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    data.toCharArray(buf, BUFFER_SIZE);
    check = 0;
  }
//----------------- 값 해석 --------------------
  if (check == 0)
  {
    for(int i=0;i<SIZE;i++)
    {
      char tmp[3] = {' ',' ',' '};
      strcpy(char_degree[i], tmp);
    }
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
      if (buf[i] == '_')
      {
        count++;
        j = 0;
        if (count >= SIZE)
        {
          count = 0;
          break;
        }
      }
      else    {
        char_degree[count][j++] = buf[i];
      }
    }
    for (int i = 0; i < SIZE; i++)
    {
      //Serial.print(i);
      //Serial.print(" : ");
      //Serial.print(char_degree[i]);
      degree[i] = atoi(char_degree[i]);
      if(degree[i] == 0)
      {
        degree[i] = 1; 
      }
      if(degree[i] > 180)
      {
        degree[i] = 180;
      }
      //Serial.print(degree[i]);
    }
    check = 1;
  }
  
//-----------------------모터 실행부 ---------------------
  for (int i = 0; i < SIZE; i++)
  {
    if (curMicros - preMicros[i] > 600 + degree[i] * 10 && state[i] == 0)
    {
      state[i] = 1;
      preMicros[i] = curMicros;
      PORTD &= ~(0x01 << 2+i);
      //Serial.print("LOW");
    }
    if (curMicros - preMicros[i] > 19400 - degree[i] * 10 && state[i] == 1)
    {
      state[i] = 0;
      preMicros[i] = curMicros;
      PORTD |= (0x01 << 2+i);
      //Serial.println("HIGH");
    }
  }
}
