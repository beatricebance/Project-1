#include "communication.h"
#include <util/delay.h>


// Fonction permettant d'attendre en utilisant _delay_ms
void COMMUNICATION:: attendre(uint16_t  millisecondes) {
	for (uint16_t i = 0; i < millisecondes; i++)
	_delay_ms(1);
}

// Fonstion pour l'initialisation de la direction des ports
void COMMUNICATION :: initialisation ( uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD ) {
	cli ();
	DDRA = pA;
	DDRB = pB;
	DDRC = pC;
	DDRD = pD;
	sei ();
}
