#include "UART.h"



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
	return UDR0;
}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0= data;
}
