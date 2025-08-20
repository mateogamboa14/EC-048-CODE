#include <Arduino.h>

// Asignacion de strings a pines:

//  Motores:
#define IN0 18
#define IN1 4
#define IN2 19
#define IN3 21

//  Jumpers:
#define J1 14
#define J2 12
#define J3 13

//  Sensores:
#define S0 36 // PIN: SVP-->GPIO 36
#define S1 34
#define Echo 35
#define Trig 32

//  Aviso:
#define Led 26

//  Colores de Race:
#define BlancoR 1
#define NegroR 0

int M0[2] = {IN0, IN1};
int M1[2] = {IN2, IN3};

int Jumpers[3] = {J1, J2, J3};

bool flagS = false;
hw_timer_t *tmp = NULL;
void timer_init()
{

  tmp = timerBegin(0, 80, true);
  timerStart(tmp);
}

void setup()
{
  for (int k = 0; k < 2; k++)
  {
    pinMode(M0[k], OUTPUT);
    pinMode(M1[k], OUTPUT);
    pinMode(Jumpers[k], INPUT);
  }
  pinMode(Trig, OUTPUT);
  pinMode(S0, INPUT);
  pinMode(S1, INPUT);
  pinMode(Echo, INPUT);
}
void loop()
{
  while (digitalRead(J1))
  {
    // Racing
    timer();
    race();
  }
  while (digitalRead(J3))
  {
    // Despeje
    timer();
    desp();
  }
  timer();
  sumo();
}

void timer(){
  while (!(flagS))
  {
    if (timerRead(tmp) >= 4800000)
    {
      digitalWrite(Led, HIGH);
      flagS = true;
    }
  }
}

void race()
{
  int estadosR = digitalRead(S0) >> 1 || digitalRead(S1);
  switch(estadosR){
    case 11:
      adelante();
      break;
    case 10:
      izquierda();
      break;
    case 01:
      derecha();
      break;
    default:
      atras();
      break;
  }
}
void desp()
{
  
}
void sumo()
{
}

void adelante()
{
  digitalWrite(IN0, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
}
void atras()
{
  digitalWrite(IN0, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
}
void izquierda()
{
  digitalWrite(IN0, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
}
void derecha()
{
  digitalWrite(IN0, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
}