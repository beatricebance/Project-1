/*
  * Nom: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :implemtation des fonctions pour utiliser les deux boutons
  *
 */


#include "Bouton.h"



/*****************************************************************************************
* Fonction: initialisation                                                                
* Description: initialisation de la configuration pour effectuer les interruptions en INT1         															  
* Paramètres: aucun
* Retour: aucun                                                               
******************************************************************************************/


void BOUTON:: initialisation(void)
{
    cli();
    DDRD = 0x00;
    DDRB = 0xff;
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC10);
    sei();
}


/*****************************************************************************************
* Fonction: initialisation                                                                
* Description: initialisation de la configuration pour effectuer les interruptions en INT0         															  
* Paramètres: aucun
* Retour: aucun                                                               
******************************************************************************************/
void BOUTON:: initialisation_2(void)
{
    cli();
    DDRD = 0x00;
    DDRB = 0xff;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

