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
#include "UART.h"
#include "communication.h"
#include "DEL.h"
#include "memoire_24.h"
#include "roues.h"

int main(){

/* Instanciation des classes*/
	Memoire24CXXX maMemoire; 
    DEL del;
	SONORITE sono;
	Roues s;
	UART uart;
	
	DDRA =0xFF;
	DDRD =0xFF;
	DDRB =0XFF;

/* Initialisation des ports*/
    initialisation (PORT_SORTIE,PORT_SORTIE,PORT_SORTIE,PORT_SORTIE);
	uart.initialisationUART();
	const uint16_t DELAI_CLIGNOTER = 1000;
    del.clignoter(ROUGE,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
	del.clignoter(VERT,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
	del.clignoter(ROUGE,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
	del.clignoter(VERT,DELAI_CLIGNOTER,DELAI_CLIGNOTER);
   
    sono.tune_NokiaRingtone();
	
    const uint8_t TEMPS_ATTENTE = 25;
	uint8_t operande; 
    uint16_t adresse= 0x00,taille;
    uint8_t instruction; 
	uint16_t nbMillisecondes;
	bool loop;
	uint8_t loopAdresse = 0;
	uint8_t loopCompteur=0;
	bool condition = false;

	//maMemoire.lecture(adresse+1, &octet1);
	//maMemoire.lecture(adresse+1, &octet2);
	//taille = octet1;
	//taille = (taille << 8) + octet2;
	
	
    do{
 		//On lit jusqu a atteindre l'instruction debut
        maMemoire.lecture(adresse, &instruction);
        _delay_ms(5);
        //maMemoire.lecture(adresse++, &operande); // l'operande est a l'adresse suivante
        uart.transmissionUART(instruction);
		_delay_ms(5);
        adresse+=2;
	 
    }
    while (instruction != 0x01);


    while (instruction !=0xFF ){
      //On lit jusqu a atteindre l'instruction fin
	  	//_delay_ms(10);
        maMemoire.lecture(adresse, &instruction);
		_delay_ms(5);
		uart.transmissionUART(instruction);
        maMemoire.lecture(adresse, &operande); // l'operande est a l'adresse suivante
		uart.transmissionUART(operande);
        _delay_ms(5);
		adresse++;
		
		// Executer l'instruction
			switch(instruction){
				case 0x01:
					break;

				case 0x02:
					nbMillisecondes=TEMPS_ATTENTE*operande; // TODO: const
					attendre(nbMillisecondes);
					break;
					
				case 0x44:
					del.allumerDEL(operande);
					break;
					
				// L'existence d'une seule DEL fait que l'operande,
				// dans ce cas, ne sera pas utile.
				case 0x45:
					del.allumerDEL(ETEINT);
					break;
				
				case 0x48:
					sono.jouer(operande);
					break;
					
				case 0x09:
					sono.arreterSonorite();
					break;
			
				case 0x60: // arreter moteur
					s.ajustementRoues(0, 0, AVANT);
					break;
				
				case 0x61: // arreter moteur
					s.ajustementRoues(0, 0, AVANT);
					break;
				
				case 0x62:  // avancer ligne droite puissance =operande          
					s.avancerMoteurs(operande,operande);
					_delay_ms(10000);
					break;
               
				case 0x63: // reculer ligne droite puissance= operande
					s.ajustementRoues(operande,operande,ARRIERE);
					s.reculerMoteurs(operande,operande);
					_delay_ms(10000);
					break;

				case 0x64: // Tourner droite
					//s.ajustementRoues(100, 0, DROITE);
					s.tournerDroite();
					_delay_ms(10000);

					break;

				case 0x65: // Tourner gauche
					//s.ajustementRoues(0, 100, GAUCHE);
					s.tournerGauche();
					_delay_ms(10000);
					break;

				case 0xC0:	// dbc (debut de boucle)
					loop = true;
					loopCompteur = operande;
					loopAdresse = adresse;			
					break;
					
				case 0xC1:	// fbc (fin de boucle)
					if (loopCompteur-- == 0)
						loop = false;
					else
						adresse = loopAdresse;
					break;
				
				default : 
					break;				
	   		
		}	
	}
	s.ajustementRoues(0, 0, AVANT);
	sono.arreterSonorite();
	del.allumerDEL(ETEINT);
	return 0;
}