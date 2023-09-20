/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe ROUE
  *
 */

#define F_CPU 8000000UL
#include "roue.h"
#include <avr/interrupt.h>
#include <avr/io.h>

   /* Constructeur de la classe roue */

    ROUE::ROUE() {

    } 

/*
    *Fonction pour faire tourner les roues grace au mode pwm en phase correct
*/
void ROUE :: ajustementPWM ( uint8_t VitesseA, uint8_t VitesseB ) {
    //sortie OCR1A et OCR1B sur comparaison.
    //mode PWM 8 bits et phase correcte
    DDRD = 0xff; // PORT D est en mode entree
    OCR1A = VitesseA ;
    
    OCR1B = VitesseB ;
    
    TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
    
    TCCR1B |= (1 << CS11);
    
    TCCR1C = 0;
    
}