//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
/**************************************/
/* files:    USART.h                  */
/* authors: *Ursule Joelle Kanmegne   */
/*          *Aymen-Alaeddine Zeghaida */
/*          *Michelle Sepkap Sime     */
/*          *Khadija Rekik            */
/* Date:     October 21, 2019         */
/*                                    */
/**************************************/
/**************************************/

#ifndef USART_H
#define USART_H

#include <avr/io.h>

// Pour ajuster les registres du microcontroleur afin de permettre 
// la communication RS232
void initialisationUART ( void );

// Procédure qui envoie un octet de la carte vers le PC
void transmissionUART ( uint8_t data );

// Procédure qui envoie une chaîne de caractères de la carte vers le PC  
void transmissionUARTChaine( char* chaine );

// Procédure qui envoie un octet du PC vers la carte
uint8_t receptionUART ( void);

#endif /* USART_H */