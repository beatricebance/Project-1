/*
  * Nom: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  * Description : Suite d'instruction executer par le robot a partir du fichier binaire
  *
 */
#include <avr/io.h>
#include "sonorite.h"
#include "communication.h"
#include "DEL.h"
#include "memoire_24.h"
#include "roues.h"
#include "debug.h"


// Constantes
const uint8_t dbt = 0x01;   // Debut des instructions
const uint8_t att= 0x02;   // Attendre
const uint8_t dal= 0x44;   // Alumer DEL
const uint8_t det = 0x45;   // Eteindre DEL
const uint8_t sgo = 0x48;   // Sonorite GO
const uint8_t sar = 0x09;   // Sonorite Arret
const uint8_t mar= 0x60;   // Arret des moteurs
const uint8_t mar1 = 0x61;  // Arret des moteurs
const uint8_t mav = 0x62;   // Avancer
const uint8_t mre = 0x63;   // Reculer
const uint8_t trd= 0x64;   // Tourner a droite
const uint8_t trg = 0x65;   // Tourner a gauche
const uint8_t dbc = 0xC0;   // Debut de boucle
const uint8_t fbc = 0xC1;   // Fin de boucle
const uint8_t fin = 0xFF;   // Fin des instructions

/* Instanciation des classes*/
	Memoire24CXXX maMemoire; 
    DEL del;
	SONORITE sono;
	Roues s;



/*Variables globales*/
    const uint8_t TEMPS_ATTENTE = 25;
	uint8_t operande; 
    uint16_t adresse= 0x00;
    uint8_t instruction; 
	uint16_t nbMillisecondes;
	uint8_t loopAdresse = 0;
	uint8_t loopCompteur=0;
	int debut =false;

void transmi(){
maMemoire.lecture(adresse,&instruction);
_delay_ms(15);
uart.transmissionUART(instruction);
_delay_ms(15);
adresse+=2;

}

int main(){

/* Initialisation des Instanciations*/
	maMemoire.init();
	uart.initialisationUART(); 

/*Direction des port */		
	DDRA =0xFF;
	DDRD =0xFF;
	DDRB =0XFF;

/* Initialisation des ports*/
    initialisation (PORT_SORTIE,PORT_SORTIE,PORT_SORTIE,PORT_SORTIE);
	const uint16_t DELAI_CLIGNOTER = 1000;
    del.clignoter(ROUGE,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
	del.clignoter(VERT,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
	del.clignoter(ROUGE,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
	del.clignoter(VERT,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
   
   // sono.tune_StarWars();
    sono.tune_NokiaRingtone ();

	adresse +=2;

//On lit et ecris jusqu a atteindre l'instruction debut
      while (instruction != 0x01){
        maMemoire.lecture(adresse,&instruction);
		
		 _delay_ms(15);
		// uart.transmissionUART(instruction);
		// _delay_ms(15);
        adresse+=2;
	  }
 		

	if(instruction == dbt) { 
        debut = true;
        del.allumerDEL(1);
		_delay_ms(10000);
    }
	
   while (debut == true) {

//DEBUG_PRINT(("ADDRESSE INCREMENTER CAR DBT LU\n"));
        maMemoire.lecture(adresse, &instruction);
		_delay_ms(15);
       // uart.transmissionUART(instruction);
		// _delay_ms(15);
        adresse++;
		

		// Executer l'instruction
			switch(instruction){

				case att:
				   
				   maMemoire.lecture(adresse,&operande);
					nbMillisecondes=TEMPS_ATTENTE*operande; 
					attendre(nbMillisecondes);
					 adresse++;
					//DEBUG_PRINT(("Delai attente\n"));
					break;
					
				case dal:
				    maMemoire.lecture(adresse,&operande);
					del.allumerDEL(operande);
					 adresse++;

					break;
					
				// L'existence d'une seule DEL fait que l'operande,
				// dans ce cas, ne sera pas utile.
				case det:
				   
					del.allumerDEL(ETEINT);
					//DEBUG_PRINT(("eteint del\n"));
					break;
				
				case sgo:
				    maMemoire.lecture(adresse,&operande);
					sono.jouer(operande);
					adresse++;
					//DEBUG_PRINT(("jouer musique\n"));
					break;
					
				case sar:
				   
					sono.arreterSonorite();
					//DEBUG_PRINT(("stop musique\n"));
					break;
			
				case mar: // arreter moteur
				    
					s.ajustementRoues(0, 0, ARRET);
					//DEBUG_PRINT(("moteur arret\n"));
					break;
				
				case mar1: // arreter moteur
				   
					s.ajustementRoues(0, 0, ARRET);
					//DEBUG_PRINT(("moteur arret\n"));
					break;
				
				case mav:  // avancer ligne droite puissance =operande 
				          maMemoire.lecture(adresse,&operande);   
					s.ajustementRoues(operande,operande,AVANT);\
					//DEBUG_PRINT(("moteur avant\n"));
					_delay_ms(10000);
					adresse++; 
					break;
               
				case mre: // reculer ligne droite puissance= operande
				      maMemoire.lecture(adresse,&operande); 
					  s.ajustementRoues(operande,operande,ARRIERE);
					//DEBUG_PRINT(("moteur arriere\n"));
					//s.reculerMoteurs(operande,operande);
					_delay_ms(1000);
					adresse++;
					break;

				case trd: // Tourner droite
			
					s.ajustementRoues(255, 0, DROITE);
					//DEBUG_PRINT(("tourner droite\n"));
					//s.tournerDroite();
					_delay_ms(1000);

					break;

				case trg: // Tourner gauche
				
					s.ajustementRoues(0, 255, GAUCHE);
					//DEBUG_PRINT(("tourner gauche\n"));
					//s.tournerGauche();
					_delay_ms(1000);
					break;

				case dbc:	// dbc (debut de boucle)
				 maMemoire.lecture(adresse,&operande); 
				//	loop = true;
					loopCompteur = operande;
					loopAdresse = adresse;	
					adresse++;	
					//DEBUG_PRINT(("DBT boucle \n"));	
					break;
					
				case fbc:	// fbc (fin de boucle)

				loopCompteur--;
					if (loopCompteur != 0)
						adresse = loopAdresse;
					break;
				
				default : 
					break;				
	   		
		}	
	} 

	return 0;
}