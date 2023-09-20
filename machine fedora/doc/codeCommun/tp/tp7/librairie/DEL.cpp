/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe DEL
  *
 */

#define F_CPU 8000000UL
#define ETEINT 0x00
#define ROUGE 0x02
#define VERT 0x01
#include <util/delay.h>
#include "DEL.h"


/* Constructeur de la classe Del */
DEL::DEL() {
}

/*
    *Fonction pour allumer la Del selon la couleur voulu passer en parametre
*/

void DEL::allumerDEL(uint8_t couleur){
            PORTB  = couleur ;
}


/* Fonction pour allumer la Del en Ambre*/
void DEL :: allumerDelAmbre()
{
		allumerDEL(VERT);//Allumer la Del en vert
		_delay_ms(10);
		allumerDEL(ROUGE);//Allumer la Del en rouge
		_delay_ms(5);
}



/* Fonction pour Faire clignoter la del a une couleur donnee*/
void DEL :: clignoterDel(uint8_t nbRepetition, uint8_t couleur) {

    for (int i = 0; i <nbRepetition ; i++){
        allumerDEL(couleur);
        _delay_ms(15);
        allumerDEL(ETEINT);
        _delay_ms(10);                
    }   
}


