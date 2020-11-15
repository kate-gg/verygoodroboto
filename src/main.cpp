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

const int SPEED = 200;
const int T_DELAY = 200;
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
const void controlx(int A, int B){
  analogWrite(ENA, abs(A));
  analogWrite(ENB, abs(B));
  digitalWrite(L1, A>0?HIGH:LOW);
  digitalWrite(L2, A<0?HIGH:LOW);
  digitalWrite(R1, B>0?HIGH:LOW);
  digitalWrite(R2, B<0?HIGH:LOW);
}
const void printmap(){
  Serial.print(digitalRead(IR1));
  Serial.print(digitalRead(IR2));
  Serial.print(digitalRead(IR3));
  Serial.print(' ');
  Serial.print(digitalRead(UR1));
  Serial.print('\n');
}
const void modeSW(const int X){ controlx(0,0);slowmode=X; delay(T_DELAY); }

void loop() {
  if(digitalRead(IR2)){
    if(digitalRead(IR1) && digitalRead(IR3)){
      if(slowmode){modeSW(0);} controlx(SPEED,SPEED);
    } else if(digitalRead(IR1) && !digitalRead(IR3)){
      if(!slowmode){modeSW(1);} controlx(0,SPEED);
    } else if(!digitalRead(IR1) && digitalRead(IR3)){
      if(!slowmode){modeSW(1);} controlx(SPEED,0);
    } else if(!digitalRead(IR1) && !digitalRead(IR3)){
      if(slowmode){modeSW(0);} controlx(SPEED,SPEED);
    }
  } else {
    if(digitalRead(IR1) && digitalRead(IR3)){
      controlx(0,0);
    } else if(digitalRead(IR1) && !digitalRead(IR3)){
      if(!slowmode){modeSW(1);} controlx(SPEED,0);
    } else if(!digitalRead(IR1) && digitalRead(IR3)){
      if(!slowmode){modeSW(1);} controlx(0,SPEED);
    } else if(!digitalRead(IR1) && !digitalRead(IR3)){
      if(slowmode){modeSW(0);} controlx(SPEED,SPEED);
    }
  }
  delay(T_DELAY);
  controlx(0,0);
  delay(T_DELAY);
}