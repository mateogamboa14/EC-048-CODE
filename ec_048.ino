#include <SoftwareSerial.h>
#define TX 1
#define RX 0
#define sum A4
#define rac A5
#define desp A6
#define s1 8
#define s2 7
#define trig 12
#define echo 11
#define enc 4
#define m01 3
#define m11 5 
#define m02 9
#define m12 6
SoftwareSerial BT(RX,TX);
int distancia,t1,t2;
void setup() {
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(enc,OUTPUT);
  pinMode(m01,OUTPUT);
  pinMode(m11,OUTPUT);
  pinMode(m02,OUTPUT);
  pinMode(m12,OUTPUT);
  Serial.begin(9600);
  TCCR0A=0;
  TCCR0B=3;
  TCNT0=6;
}
void loop() {
  if(digitalRead(rac)==1){
    timer();
    do{
      race();
    }while(analogRead(rac)>1000);
  }
  if(analogRead(desp)>1000){
    timer();
    do{
      despeje();   
    }while(analogRead(desp)>1000);
  }
  if(analogRead(sum)>1000){
    timer();
    do{
      sumo();
    }while(analogRead(sum)>1000);
  }
}
void timer(){
  for(t1=0;t1<5;t1++){
    Serial.println("Tiempo: ");
    Serial.println(t1);
    for(t2=0;t2<50;t2++){
      Serial.println("Tiempo en ms: ");
      Serial.println(t2);
    }
    if(t1==2||t1==3||t1==4){
      digitalWrite(enc,HIGH);
      delay(20);
      digitalWrite(enc,LOW);
      delay(20);
    }
  }
}
//negro =1;
//blanco =0;
void race(){
  if((digitalRead(s1)&&digitalRead(s2))==1){
    do{
        digitalWrite(m01,HIGH);
        digitalWrite(m02,HIGH);
        digitalWrite(m11,LOW);
        digitalWrite(m12,LOW);
    }while((digitalRead(s1)&&digitalRead(s2))==1);
  }
  if(digitalRead(s1)==0 && digitalRead(s2)==1){
    do{
      
    derecha();
    delay(100);
    }while(digitalRead(s1)==0 && digitalRead(s2)==1);
  }
  if(digitalRead(s2)==0 && digitalRead(s1)==1){
    do{
      izquierda();
      delay(100);
    }while(digitalRead(s2)==0 && digitalRead(s1)==1);
  }
  if((digitalRead(s1)&&digitalRead(s2))==0){
    do{
      digitalWrite(m01,LOW);
      digitalWrite(m02,LOW);
      digitalWrite(m11,HIGH);
      digitalWrite(m12,HIGH);
      delay(100);
    }while((digitalRead(s1)&&digitalRead(s2))==0);
  }
}
void despeje(){
  //45 de largo,m0ide
  //35 para objetos chicos
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  distancia=pulseIn(echo,HIGH)/59;
  if(distancia<45){
    do{
        digitalWrite(m01,HIGH);
        digitalWrite(m02,HIGH);
        digitalWrite(m11,LOW);
        digitalWrite(m12,LOW);
    }while((digitalRead(s1)&&digitalRead(s2))==1);
  }
  if((digitalRead(s1)&&digitalRead(s2))==0){
    digitalWrite(m01,LOW);
    digitalWrite(m02,LOW);
    digitalWrite(m11,HIGH);
    digitalWrite(m12,HIGH);
    delay(1000);
    izquierda();
    delay(500);
    adelante();
    delay(100);
  }
  
  if(((digitalRead(s1)&&digitalRead(s2))==0)&&(distancia>45)){
    adelante();
    izquierda();
    delay(500);
  }
}
void sumo(){
  if(BT.available()){
    char dat=BT.read();
    if(dat=='W'||dat=='w'){
        digitalWrite(m01,HIGH);
        digitalWrite(m02,HIGH);
        digitalWrite(m11,LOW);
        digitalWrite(m12,LOW);
    }
    if(dat=='S'||dat=='s'){
     digitalWrite(m01,LOW);
      digitalWrite(m02,LOW);
      digitalWrite(m11,HIGH);
      digitalWrite(m12,HIGH);
    }
    if(dat=='A'||dat=='a'){
      izquierda();
    }
    if(dat=='D'||dat=='d'){
      derecha();
    }
  }
}
void adelante(){
  digitalWrite(m01,HIGH);
  digitalWrite(m02,HIGH);
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
}
void atras(){
  digitalWrite(m01,LOW);
  digitalWrite(m02,LOW);
  digitalWrite(m11,HIGH);
  digitalWrite(m12,HIGH);
}
void izquierda(){
  digitalWrite(m01,HIGH);
  digitalWrite(m02,LOW);
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
}
void derecha(){
  digitalWrite(m01,LOW);
  digitalWrite(m02,HIGH);
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
}
