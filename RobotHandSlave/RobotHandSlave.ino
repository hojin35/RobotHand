//수신부 프로그램
#include<stdlib.h>
#define SIZE 6
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
  DDRD |= (0x01 << 2 | 0x01 << 3 | 0x01<<4 | 0x01 << 5 | 0x01 << 6 || 0x01 << 7);
}

void loop()
{
  curMicros = micros();
//-----------------------모터 실행부 ---------------------
if(check == 0)
{
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
  
}
void serialEvent()
{
  while(Serial.available())
  {
     String data = Serial.readStringUntil('\n');
     check = 1;
     Split(data,' ');
     check = 0;
  }
}
void Split(String sData, char cSeparator)
{	
  int location = 0;
	int nCount = 0;
	int nGetIndex = 0 ;

	//임시저장
	String sTemp = "";

	//원본 복사
	String sCopy = sData;

	while(true)
	{
		//구분자 찾기
		nGetIndex = sCopy.indexOf(cSeparator);

		//리턴된 인덱스가 있나?
		if(-1 != nGetIndex)
		{
			//있다.

			//데이터 넣고
			sTemp = sCopy.substring(0, nGetIndex);
      char temp[100];
      strcpy(temp,sTemp.c_str());
      degree[nCount] = atoi(temp);
			//Serial.println(sTemp);
		
			//뺀 데이터 만큼 잘라낸다.
			sCopy = sCopy.substring(nGetIndex + 1);
		}
		else
		{
			//없으면 마무리 한다.
			//Serial.println( sCopy );
			break;
		}

		//다음 문자로~
		++nCount;
	}

}
