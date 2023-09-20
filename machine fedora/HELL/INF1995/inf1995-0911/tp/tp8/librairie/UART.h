#ifndef UART_H
#define UART_H
#endif

#include <avr/io.h>
#include <util/delay.h>

void Receive_USART(uint8_t taille);
unsigned char USART_Receive( void );
void initialisationUART ( void );
