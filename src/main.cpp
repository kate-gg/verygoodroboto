#include <Arduino.h>

const int L1 = 2;
const int L2 = 3;
const int R1 = 4;
const int R2 = 5;
const int ENA = A0;
const int ENB = A1;
const int IR1 = 6;
const int IR2 = 7;
const int IR3 = 8;
const int UR1 = 9;

const int SPEED = 255;
const int SSPEED = 150;
int slowmode = 0;
void setup() {
  Serial.begin(9600);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(UR1,INPUT);
}
void controlx(int A, int B){
  analogWrite(ENA, abs(A));
  analogWrite(ENB, abs(B));
  digitalWrite(L1, A>0?HIGH:LOW);
  digitalWrite(L2, A<0?HIGH:LOW);
  digitalWrite(R1, B>0?HIGH:LOW);
  digitalWrite(R2, B<0?HIGH:LOW);
}
void printmap(){
  Serial.print(digitalRead(IR1));
  Serial.print(digitalRead(IR2));
  Serial.print(digitalRead(IR3));
  Serial.print(' ');
  Serial.print(digitalRead(UR1));
  Serial.print('\n');
}

void loop() {
  printmap();
  if(digitalRead(IR2)){
    if(digitalRead(IR1) && digitalRead(IR3)){
      if(slowmode){ controlx(0,0);slowmode=0; delay(300); }
      controlx(SPEED,SPEED);
    } else if(digitalRead(IR1) && !digitalRead(IR3)){
      if(!slowmode){ controlx(0,0);slowmode=1; delay(300);}
      controlx(0,SSPEED);
    } else if(!digitalRead(IR1) && digitalRead(IR3)){
      if(!slowmode){ controlx(0,0);slowmode=1; delay(300);}
      controlx(SSPEED,0);
    } else if(!digitalRead(IR1) && !digitalRead(IR3)){
      if(slowmode){ controlx(0,0);slowmode=0; delay(300); }
      controlx(SPEED,SPEED);
    }
  } else {
    if(digitalRead(IR1) && digitalRead(IR3)){
      controlx(0,0);
    } else if(digitalRead(IR1) && !digitalRead(IR3)){
      if(!slowmode){ controlx(0,0);slowmode=1; delay(300);}
      controlx(SSPEED,0);
    } else if(!digitalRead(IR1) && digitalRead(IR3)){
      if(!slowmode){ controlx(0,0);slowmode=1; delay(300);}
      controlx(0,SSPEED);
    } else if(!digitalRead(IR1) && !digitalRead(IR3)){
      controlx(0,0);
    }
  }
}