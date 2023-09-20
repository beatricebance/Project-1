/*
  * Nom: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe DEL
  *
 */

#include "DEL.h"
#include "communication.h"


/*
*Fonction pour allumer la Del selon la couleur voulu passer en parametre
*/

void DEL::allumerDEL(uint8_t couleur){
            PORTA  = couleur ;
}


/* Fonction pour allumer la Del en Ambre*/
void DEL :: allumerDelAmbre()
{
		allumerDEL(VERT);//Allumer la Del en vert
		_delay_ms(10);
		allumerDEL(ROUGE);//Allumer la Del en rouge
		_delay_ms(5);
}

// Permet de faire clignoter la del.
void DEL :: clignoter(uint8_t couleur, uint16_t dureeAllumee, uint16_t dureeEteinte){
	PORTA= couleur;
	attendre(dureeAllumee);
	PORTA= ETEINT;
	attendre(dureeEteinte);
}

