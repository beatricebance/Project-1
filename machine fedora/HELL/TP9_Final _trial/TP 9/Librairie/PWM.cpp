

#define F_CPU 8000000
#include "PWM.h"
#include <avr/io.h> 
#include <util/delay.h>

const uint16_t TEMPS_ROTATION_COMPLETE = 1900;
const uint8_t MAX = 255;
const int CENTRE = 1, DROITE = 2, GAUCHE = 3;
float a, b, puissance = 0, rA = 1, rB = 1;
const uint16_t ETEINT = 0x00;
const uint16_t ROUGE = 0x02;
const uint16_t VERT = 0x01;


void maj () {
	
  int a = MAX*puissance*rA;
  int b = MAX*puissance*rB*0.91;
  
  PORTD &= (0 << 7);
  PORTD &= (0 << 6);

  

  if(a < 0){
    PORTD |= 1 << 6;
    a = -a;
    
  }

  if(b < 0){
    PORTD |= 1 << 7;
    b = -b;
  }



  if(a > 255){
    a = 255;
  }
  if(b > 255){
    b = 255;
  } 
  
  if(puissance > 0){
    OCR1A = 0;
    OCR1B = 0; 
    _delay_ms(35);
  }
    
  OCR1A = MAX-a;
  OCR1B = MAX-b;  
}

void arret () {
  puissance = 0;
  rA = rB = 1;
  maj();
}

void setPuissance (double p) {
  puissance = p;
  maj();
}

void accelerer (float a) {
  puissance += a;
  if(puissance > 1){
    puissance = 1;
  }
  maj();
}

void tournerRayon (float r, int sens) {
  r = (r-5)/(r+5);
  rA = 1;
  rB = 1;
  if(sens == 3){
    rB += (rA-r);
    rA = r;
  }
  else if (sens == 2){
    rA += (rB-r);
    rB = r;
  }
  maj();
}

void attendre (int ms){
  for(int i = 0; i < ms; i ++){
    _delay_ms(1);
  }
}

void tournerDegre (uint16_t degre, int sens) {
  double temp = puissance;
  arret();
  _delay_ms(750);
  puissance = 1 ;
  tournerRayon(0,sens);
  attendre(TEMPS_ROTATION_COMPLETE/360*degre+180);
  arret();
  _delay_ms(750);
  puissance = temp;
  tournerRayon(0,CENTRE);
  
}

void initialisation () {
 

  // reservation des port ouput
  DDRD |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7); 

  // setup du timer
  TCCR1A |= (1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 0); 
  TCCR1B |= (1 << 1);
  TCCR1C = 0;

  //etat initial
  arret();

}

void setPWMA (int p){
  TCCR0A |= (1 << 6) | (1 << 4) | (1 << 1); 
  TCCR0B |= (1 << 2);
  OCR0A = p;
}

void clearPWM(){
  TCCR0A = 0;
  TCCR0B = 0;
}

void setPWMB (int p){
  TCCR0A |= (1 << 6)  | (1 << 4) | (1 << 1); 
  TCCR0B |= (1 << 2);
  OCR0B = p;
}

void setColor(int couleur){
 DDRB=0xff;
 switch(couleur) 
 {
     case ETEINT : PORTB=ETEINT;
       break;
     case VERT   : PORTB=VERT;
        break;
     case ROUGE  : PORTB=ROUGE;
        break;
     default     : break;
 }
}

void verification(bool estOk){
    DDRB=0xff;
    if(estOk==true){
        PORTB=VERT;
    }
    else {
        PORTB=ROUGE;
    }
}

void eteindreDel() {
    setColor(ETEINT);

}


