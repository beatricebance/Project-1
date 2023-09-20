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
BOUTON::BOUTON() {

initialisation();
}




void BOUTON::initialisation (){

	cli(); // cli est une routine qui bloque toutes les interruptions
	DDRD = (0 << PORTD2); // PORT D2 est en mode entree
    DDRA = 0x03; // PIN 0 ET 1 DU PORT A EN SORTIE
	EIMSK |= (1 << INT0);  // Activer les interruptions externes
	EICRA |= (1 << ISC00); // regler INT0 pour declencher n'importe quel changement de logique
	sei(); //sei permet de recevoir à nouveau des interruptions.

}