#include "Arduino.h"

#define IN1 2
#define IN2 4
#define IN3 6
#define IN4 7
#define ENA 5
#define ENB 3
#define ledInit 10
#define SD  9
#define SI  12
int vel = 255, vsd, vsi;
int motor[4]={IN1,IN2,IN3,IN4};
void setup() {
    DDRD = B11111100; 
    DDRB |= (1 << PB2); 
    DDRB &= ~((1 << PB1);
    DDRB &= ~ (1 << PB4);

}
void loop(){

  inicioLed();
  
  vsd = (PINB & (1 << PB1));//SD
  vsi = (PINB & (1 << PB4));//SI
  if(vsd == LOW and vsi == HIGH ){
    OCR0B = vel; // ENA 
    OCR0A = vel; // ENB     
    PORTD &= ~((1 << PD6) // IN3 en LOW
    PORTD &= ~(1 << PD2)); // IN1 en LOW
    PORTD |=  ((1 << PD7); // IN4 en HIGH
    PORTD |=  ((1 << PD4)); // IN2 en HIGH
    PORTB &= ~(1 << PB2); // apaga ledInit

  }
// y los otras bobinas?????
  if(vsd == HIGH and vsi == HIGH  ){
    OCR0B = 0;   // ENA 
    OCR0A = vel; // ENB 
    PORTD &= ~(1 << PD6); // IN3 en LOW
    PORTD |= (1 << PD7);  // IN4 en HIGH
    PORTB &= ~(1 << PB2); // apaga ledInit
  }

  if(vsd == LOW and vsi == LOW){
    OCR0A = 0;   // ENB 
    OCR0B = vel; // ENA
    PORTD &= ~(1 << PD2); // IN1 en LOW
    PORTD |= (1 << PD4);  // IN2 en HIGH
    PORTB &= ~(1 << PB2); // apaga ledInit

  }



}

int estadoSecuencia = 0;
unsigned long tiempoAnterior = 0;

void inicioLed() {
int ledEstado=0;
  unsigned long tiempoActual = millis();
  while (ledEstado<6) {
    switch(ledEstado){
        case 0: 
          if (tiempoActual - tiempoAnterior >= 1620) {
            PORTB |= (1 << PB2); 
            tiempoAnterior = tiempoActual;
            ledEstado++;
          }
          break;
        case 1: // LED encendido por 150 ms
          if (tiempoActual - tiempoAnterior >= 150) {
            PORTB &= ~(1 << PB2); // ledInit en LOW
            tiempoAnterior = tiempoActual;
            ledEstado++;
          }
          break;
        case 2: // LED apagado, espera de 900 ms
          if (tiempoActual - tiempoAnterior >= 900) {
            PORTB |= (1 << PB2); // ledInit en HIGH
            tiempoAnterior = tiempoActual;
            ledEstado++;
          }
          break;
        case 3: // LED encendido por 150 ms
          if (tiempoActual - tiempoAnterior >= 150) {
            PORTB &= ~(1 << PB2); // ledInit en LOW
            tiempoAnterior = tiempoActual;
            ledEstado++;
          }
          break;
        case 4: // LED apagado, espera de 900 ms
          if (tiempoActual - tiempoAnterior >= 900) {
            PORTB |= (1 << PB2); // ledInit en HIGH
            tiempoAnterior = tiempoActual;
            ledEstado++;
          }
          break;
        case 5: // LED encendido por 150 ms (último paso)
          if (tiempoActual - tiempoAnterior >= 150) {
            PORTB &= ~(1 << PB2); // ledInit en LOW
            tiempoAnterior = tiempoActual;
            ledEstado++;
          }
          break;
        case 6: // Fin de la espera, marca la secuencia como terminada
            estadoSecuencia++;
          break;
    }
  }
}