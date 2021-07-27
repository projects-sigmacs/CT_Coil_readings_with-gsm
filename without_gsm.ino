#include "EmonLib.h"
#include<TimerOne.h>
#define led  5
#define led1  6
#define led2  7
#define led3  8
#define led4  9
#define pb 4
#define green 11

#define waitled 12
#define linevoltage A2
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;
int valu = 0;
double x = 15.02;
int y = 0;
unsigned long time;
double adc1 = 0;
double adc2 = 0;
double adc3 = 0;
double adcd1 = 0;
double adcd2 = 0;
double adcd3 = 0;
int buttonstate = 0;
unsigned int cnt = 0;
float ad1;
float ad2;
float ad3;
float line;
float linevolt;
float r;
int f = 0;

double ct1;
double ct2;
double ct3;
unsigned long current = 0, current3 = 0, current2 = 0, prev = 0, current1 = 0;

extern volatile unsigned long timer0_millis;
void(* resetFunc) (void) = 0;

float chart[5] = {1.8, 4.2, 8.0, 8.5, 15};
//float chart[5] = {2.4, 5.6, 10, 11, 20};
//float chart[5] = {3, 7, 13, 14, 25};
//float chart[5] = {3.6, 8.4, 16, 17, 30};
//float chart[5] = {4.2, 9.8, 18, 20, 35};
//float chart[5] = {4.5, 10.5, 20, 21, 38};
//float chart[5] = {6.2, 14, 26, 28, 50};
//float chart[5] = {7.5, 18, 33, 35, 63};
//float chart[5] = {9, 21, 39, 42, 75};
//float chart[5] = {11, 25, 46, 49, 88};
//float chart[5] = {12, 35, 52, 56, 100};
//float chart[5] = {15, 44, 65, 70, 125};
//float chart[5] = {18, 53, 78, 90, 150};
//float chart[5] = {32, 61, 81, 98, 175};

void setup()
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  Serial.print("AT+CMGF=1\r");
  Serial.println("AT+CNMI=2,2,0,0,0");
  pinMode(green, OUTPUT);
  //analogReference(INTERNAL);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(pb, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  emon1.current(A3, 30);
  emon2.current(A4, 30);
  emon3.current(A5, 30);
  pinMode(A1, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(A2, INPUT);

}

void loop()
{
  digitalWrite(2, HIGH);
  loadon();
}

void loadon()
{ linevol();
  double ct1 = emon1.calcIrms(1480);
  double ct2 = emon2.calcIrms(1480);
  double ct3 = emon3.calcIrms(1480);
  Serial.print("CT1:");
  Serial.print(ct1);
  Serial.print("   ");
  Serial.print("CT2:");
  Serial.print(ct2);
  Serial.print("   ");
  Serial.print("CT3 :");
  Serial.println(ct3);
  adc1 = ct1 / 1.2;
  adc2 = ct2 / 1.2;
  adc3 = ct3 / 1.2 ;
  float  a = chart[0];
  float A = a;
  //  Serial.print("a= ");
  //  Serial.println(a, 5);
  float b = chart[1];
  float B = b  ;
  //  Serial.print("b= ");
  //  Serial.println(b, 5);
  float c = chart[2];
  float C = c  ;
  //  Serial.print("c= ");
  //  Serial.println(c, 5);
  float d = chart[3];
  float D = d  ;
  //  Serial.print("d= ");
  //  Serial.println(d, 5);
  float e = chart[4];
  float E = e  ;
  //  Serial.print("e= ");
  //  Serial.println(e,   5);

  /*  if ((adc1 == 0)  || (adc2 == 0)  || (adc3 == 0 ) )
    {
      digitalWrite(led, LOW);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }
    if ((adc1 > 175) && (adc2 > 175)  && (adc3 > 175) )
    {
      digitalWrite(led, LOW);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }*/
  if ((adc1 > A)  && (adc2 > A)  && (adc3 > A ) )
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  if (adc1 > B  && adc2 > B  && adc3 > B )
  {
    digitalWrite(led1, LOW);
  }
  else
  {
    digitalWrite(led1, HIGH);
  }
  if (adc1 > C  && adc2 > C && adc3 > C  )
  {
    digitalWrite(led2, HIGH);
  }
  else
  {
    digitalWrite(led2, LOW);
  }
  if (adc1 > D  && adc2 > D && adc3 > D  )
  {
    digitalWrite(led3, HIGH);
  }
  else
  {
    digitalWrite(led3, LOW);
  }
  if (adc1 > E  && adc2 > E  && adc3 > E )
  {
    digitalWrite(led4, HIGH);
  }
  else
  {
    digitalWrite(led4, LOW);
  }

  if (digitalRead(13) == LOW )
  {
    digitalWrite(10, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(led, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    while (1) {}

  }
}

void linevol()
{
  line = analogRead(A2);
  Serial.print("linevoltage:: ");
  linevolt = line * (5 / 1023.0);
  Serial.println(linevolt);
  if (linevolt >= 3.000 && linevolt <= 4.500)
  {
    digitalWrite(10, HIGH);
    digitalWrite(12, HIGH);
    current = millis();
    Serial.println(current);
    if (current >= 22000)
    {
      digitalWrite(12, LOW);
    }
    if (current >= 32000)
    {
      if (digitalRead(pb) == LOW)
      {
        digitalWrite(10, HIGH);
      }
      else
      {
        Serial.println("waited for 32 sec no ip");
        digitalWrite(10, LOW);
        down();
      }
    }
  }
  else
  {
    digitalWrite(10, LOW);
  }
}


void down()
{
  if (analogRead(A1) == LOW)
  {
    int z = 0;
    timer0_millis = 0;
    current3 = millis();
    if (current3 >= 600000)
    {
      linevol();
      z = z++;
      if (z <= 3)
      {
        while (1)
        {
          digitalWrite(10, LOW);
        }
      }
    }
  }
  if (digitalRead(3) == LOW)
  {
    int z = 0;
    timer0_millis = 0;
    current2 = millis();
    if (current2 >= 1200000)
    {
      linevol();
      z = z++;
      if (z <= 3)
      {
        while (1)
        {
          digitalWrite(10, LOW);
        }
      }
    }
  }
}









































String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void serialevent()
{
  String str, a = "", x = "" , y = "", phone = "", data_str = "";
  a = Serial.readStringUntil("\n");
  a.toLowerCase();
  //  SerialMon.println(a);
  Serial.flush();
  phone = getValue(a, '"', 1);
  Serial.print(" the sms received from: ");
  Serial.println(phone);
  if (a.indexOf("on") > 0)
  {
    Serial.println("AT+CMGF=1\r");
    Serial.println("AT+CMGS=\"+917893041111\"\r");
    delay(1000);
    Serial.print("load on");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
    Serial.println("AT+CMGD=6");
    linevol();
  }
  if (a.indexOf("off") > 0)
  {
    digitalWrite(10, 0);
    Serial.println("AT+CMGF=1\r");
    Serial.println("AT+CMGS=\"+917893041111\"\r");
    delay(1000);
    Serial.print("load off");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
    Serial.println("AT+CMGD=6");
  }
  if (a.indexOf("gemini") > 0)
  {
    if (digitalRead(10) == 1)
    {
      Serial.println("AT+CMGF=1\r");
      Serial.println("AT+CMGS=\"+917893041111\"\r");
      delay(1000);
      Serial.print("load on");
      delay(1000);
      Serial.write(0x1A);
      delay(1000);
      Serial.println("AT+CMGD=6");
    }
    else
    {
      Serial.println("AT+CMGF=1\r");

      Serial.println("AT+CMGS=\"+917893041111\"\r");
      delay(1000);
      Serial.print("load off");
      delay(1000);
      Serial.write(0x1A);
      delay(1000);
      Serial.println("AT+CMGD=6");
    }
  }
}
