#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>

void initialisationUART ( void ) ;
uint8_t USART_Receive( void ) ;
void USART_Transmit( unsigned char data );

