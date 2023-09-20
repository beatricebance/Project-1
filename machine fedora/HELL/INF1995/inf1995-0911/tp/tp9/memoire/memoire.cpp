#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "Magic.h"
#include "memoire_24.h"
#include "UART.h"

int main(){
	Memoire24CXXX memoire = Memoire24CXXX();
	initialisationUART();
	
	uint8_t lecture;
	uint16_t adresse = 0x00;
	
	do {
		lecture = USART_Receive();
		memoire.ecriture(adresse, lecture);
		adresse += 0x1;
	} while ((lecture != 0xff) && (adresse % 2 == 0));
	
	
	// dans le but de laisser savoir que lecriture dans la memoire est terminer :
	DDRB = 0xff;
	for (int i = 0; i < 5; i++){
		PORTB = 1;
		_delay_ms(100);
		PORTB = 0;
		_delay_ms(100);
	}
			
	return 0;
}
