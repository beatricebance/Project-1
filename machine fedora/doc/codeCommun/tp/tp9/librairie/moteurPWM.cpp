/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */

#define F_CPU 8000000
#define uneSecondeH1 7813
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#define VITESSE_MAX 255


void initialiserRegistre(){
// mise à un des sorties OC1A et OC1B sur comparaison

// réussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

// page 177 de la description technique du ATmega324PA)



// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1A |= (1<<COM1A1)|(1<<COM1B1) |(1<<WGM10)  ;

TCCR1B |=  (1<<CS11);

TCCR1C = 0;

}

void avancerPWM( uint8_t vitesse) {

  //initialiserRegistre();
// la fonction qui faire clignoter la DEL pendant 10 s
PORTD= 0x00;
OCR1A = vitesse;
OCR1B = vitesse;

}

void reculerPWM(uint8_t vitesse){
     PORTD = 0x0C;
    OCR1A = vitesse;
    OCR1B = vitesse;
}

void arreterMoteur(){
    OCR1A = 0;
    OCR1B = 0;
}

void tournerGauche(){
    OCR1A = 0;
    OCR1B = 127;
}

void tournerDroite(){
    OCR1B = 0;
    OCR1A = 127;
}
