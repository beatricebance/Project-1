/*
  * Nom: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
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



/*****************************************************************************************
* Fonction: Constructeur BOUTON                                                                
* Description: initialisation de la configuration pour effectuer les interruptions en INT0         															  
* Paramètres: aucun
* Retour: aucun                                                               
******************************************************************************************/


//initialisation de ISR du bouton_poussoir
void BOUTON:: initialisation(void)
{
    cli();
    DDRD = 0x00;
    DDRB = 0xff;
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC10);
    sei();
}


//initialisation de ISR du bouton interrupt
void BOUTON:: initialisation_2(void)
{
    cli();
    DDRD = 0x00;
    DDRB = 0xff;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

