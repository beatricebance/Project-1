#include "commun.h"


void attendre(uint16_t millisecondes) {
	for (uint16_t i = 0; i < millisecondes; i++)
		_delay_ms(1);
}

void initialisation ( uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD ) {
	cli ();
	DDRA = pA;
	DDRB = pB;
	DDRC = pC;
	DDRD = pD;
	sei ();
}
