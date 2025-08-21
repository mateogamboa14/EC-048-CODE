#include <Arduino.h>

// Asignacion de macros a pines:

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
  while ((GPIO_IN_REG >> J1) & 1)
  {
    // Racing
    timer();
    race();
  }
  while ((GPIO_IN_REG >> J3) & 1)
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
      WRITE_PERI_REG(GPIO_OUT_W1TS_REG, (1<<Led));
      flagS = true;
    }
  }
}

void race()
{
  int estadosR = (((GPIO_IN1_REG >> (S0 - 32)) & 1U) >> 1)| ((GPIO_IN1_REG >> (S1 - 32)) & 1U);
  switch(estadosR){
    case 0b11:
      adelante();
      break;
    case 0b10:
      izquierda();
      break;
    case 0b01:
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
    WRITE_PERI_REG(GPIO_OUT_W1TS_REG, (1<<IN0));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN1));
    WRITE_PERI_REG(GPIO_OUT_W1TS_REG, (1<<IN2));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN3));
}
void atras()
{
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN0));
    WRITE_PERI_REG(GPIO_OUT_W1TS_REG, (1<<IN1));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN2));
    WRITE_PERI_REG(GPIO_OUT_W1TS_REG, (1<<IN3));
}
void izquierda()
{
    WRITE_PERI_REG(GPIO_OUT_W1TS_REG, (1<<IN0));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN1));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN2));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN3));
}
void derecha()
{
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN0));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN1));
    WRITE_PERI_REG(GPIO_OUT_W1TS_REG, (1<<IN2));
    WRITE_PERI_REG(GPIO_OUT_W1TC_REG, (1<<IN3));
}