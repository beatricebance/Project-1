/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe du bouton poussoir
  *
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Bouton.h"


/* 
	*Constructeur de la classe Del 
*/
BOUTON::BOUTON() {
}

/* 
  *Fonction qui effectue une lecture du bouton-poussoir avec l'antirebond 
*/
bool BOUTON :: estAppuyer()
{
  if (PIND & 0x04)
  {
    _delay_ms(10);
    return PIND & 0x04;
  }
  return false;
}

/* 
  *Fonction qui effectue l'initialisation de la configuration pour effectuer les interruptions en INT0
  *PORTD EN MODE ENTREE  (car INT0 se trouve au niveau de PD2)
*/

void BOUTON :: initialisation(void)
{
	cli(); // cli est une routine qui bloque toutes les interruptions
	DDRD = 0x00; // PORT D est en mode entree
	EIMSK |= (1 << INT0);  // Activer les interruptions externes
	EICRA |= (1 << ISC00); // regler INT0 pour declencher n'importe quel changement de logique
	sei(); //sei permet de recevoir à nouveau des interruptions.
}



