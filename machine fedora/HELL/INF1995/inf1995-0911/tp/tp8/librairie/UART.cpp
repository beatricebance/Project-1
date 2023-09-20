#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"
#include "UART.h"


uint8_t var;

void initialisationUART ( void ) {

	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0
	UCSR0A = 0 ;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) ;

	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

uint8_t USART_Receive( void ) {
	while(!(UCSR0A & (1<<RXC0))){
	}
	var = UDR0;
}

void Receive_USART(uint8_t taille){
	Memoire24CXXX memoire1 = Memoire24CXXX();
	initialisationUART();
	
	memoire1.ecriture(0x0000, &var, taille);

}


