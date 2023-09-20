/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe Minuterie
  *
 */

#include "Minuterie.h"

/*
    *Constructeur de la classe Minuterie
*/
Minuterie::Minuterie() {
	minuterieCommencee_ = false;
	minuterieExpiree_ = 0;
}



/*Fonction qui fait usage du Timer1 pour lancer la minuterie des registre*/

void Minuterie :: partirMinuterie(uint16_t duree)
{
    minuterieCommencee_ = true;
	minuterieExpiree_ = 0;

	// mode CTC du timer 1 avec horloge divisée par 1024

	// interruption après la durée spécifiée

	TCNT1 = 0; // initialise le timer a 0

	OCR1A = duree; // valeur a laquel le timer sera comparer (on compare OCR1A avec TCNT1 pendant le decompte)

	TCCR1A = 0;

	TCCR1B = (1 << CS12) | (1 << CS10); // divise l'horloge par 1024

	TCCR1C = 0;

	TIMSK1 |= (1 << OCIE1A); // le bit d'activation d'interruption correspondant doit être activé
}

// getters

/*
    * entier qui indique si la minuterie est expiree
*/
uint8_t Minuterie::getminuterieExpiree() {
	return minuterieExpiree_;
}

/*
    * booleen qui indique si la minuterie est active
*/
bool Minuterie::getminuterieComencee() {
	return minuterieCommencee_;
}

/*
    * fonction qui indique que la minuterie est expiree
*/

void Minuterie::setminuterieExpiree() {
    minuterieExpiree_= 1;
}

