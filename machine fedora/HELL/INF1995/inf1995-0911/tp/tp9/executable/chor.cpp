#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"
#include "Magic.h"
#include "Engine.h"

#define VITESSE_MAX 255

// pour que le robot fonctionne, on doit brancher la roue de gauche aux ports D5-D7,
// la roue de droite aux ports D6-D8, le buzzer aux port B3-B4, et la LED au port B1-B2.  


//liste des instructions
enum Instructions{dbt=0x01, att=0x02, dal=0x44, det =0x45, sgo=0x48, sar=0x09, mar=0x60, mar2=0x61, mav=0x62, mre=0x63, trd=0x64, trg=0x65, dbc=0xc0, fbc=0xc1, fin=0xff};
//liste des frequences
float notesFreq[38]={110,116.5409404,123.4708253,130.8127827,138.5913155,146,832384,155.5634919,164.8137785,174.6141157,184.9972114,195.997718,207.6523488,220,233.0818808,246.9416506,261.6255653,277.182631,293.6647679,311.1269837,329.6275569,349.2282314,369.9944227,391.995436,415.3046976,440,466.1637615,493.8833013,523.2511306,554.365262,587.3295358,622.2539674,659.2551138,698.4564629,739.9888454,783.990872,830.6093952,880};

int main(){
	
	DDRB = 0xff; // port B en sortie
	
	initialisation();
    Engine engine;
    Memoire24CXXX memoire = Memoire24CXXX();
    
    uint8_t nbOctets = 0;
    memoire.lecture(0x0000, &nbOctets, 0x02);

    uint16_t adresse = 0x0000;
    uint8_t instruction = 0;
    uint8_t operande = 0;
    
    uint16_t loopAdress = 0;
    uint8_t loopCounter = 0;
    
    //dans le but d'ignorer toutes les commandes avant dbt
    do {
		memoire.lecture(adresse, &instruction);
		adresse += 1;
		memoire.lecture(adresse, &operande);
		adresse += 1;
	} while (instruction != dbt);
    
    
    do{
		//on lit le premier octet qui est l'instruction
		memoire.lecture(adresse, &instruction);
		adresse += 1;
		//on lit le second octet qui est l'operande
		memoire.lecture(adresse, &operande);
		adresse += 1;
		
        switch(instruction){
			// attendre 25*operande
            case att :
                for(uint8_t i = 0; i<operande; i++)
                    _delay_ms(25);
				break;
			// allumer la DEL
            case dal :
                changeLEDColor(GREEN);
				break;
			// eteindre la DEL
            case det :
                changeLEDColor(NONE);
				break;
			// jouer une note (operande)
            case sgo :
                if(operande>=45 && operande <=81){
                    PWM_M_Buzzer(notesFreq[operande-45]);
                }
				break;
			// arreter la note
            case sar :
				OCR0A = 0;
				break;
			// arreter les moteurs
            case mar :
            case mar2 :
                engine.stop();
				break;
			// avancer avec la vitesse : operande
            case mav :
                engine.move(operande, Forward);
				break;
            case mre :
            // reculer avec la vitesse : operande
                engine.move(operande, Backward);
				break;
			// tourner a droite de 1/4 de tour
            case trd :
                engine.move(VITESSE_MAX, Right);
                _delay_ms(1000);
                engine.stop();
				break;
			// tourner a gauche de 1/4 de tour
            case trg :
                engine.move(VITESSE_MAX, Left);
                _delay_ms(1000);
                engine.stop();
				break;
			// debut d'une boucle
            case dbc :
                loopAdress = adresse;
                loopCounter = operande;
				break;
			//fin de la boucle
            case fbc :
                if(loopCounter>0){
                    adresse = loopAdress;
                    loopCounter--;
                }
				break;
			case fin:
				engine.stop();
				OCR0A = 0;
				changeLEDColor(NONE);
				break;
        }
    } while(instruction != fin);
}
