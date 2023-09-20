//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
/**************************************/
/* files:    USART.cpp                */
/* authors: *Ursule Joelle Kanmegne   */
/*          *Aymen-Alaeddine Zeghaida */
/*          *Michelle Sepkap Sime     */
/*          *Khadija Rekik            */
/* Date:     October 21, 2019         */
/*                                    */
/**************************************/
/**************************************/

#include "USART.h"

/*******************************************************************/
/* Pour ajuster les registres du microcontroleur afin de permettre */
/* la communication RS232                                          */
/* Aucun paramètre                                                 */
/* Aucune valeur de retour                                         */
/*******************************************************************/
void initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0
    UCSR0A |= (1 << TXC0);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C |= (3 << UCSZ00) ;

    // Activer une interruption lorsqu'il y a des donnees 
    // non lues dans le tampon de reception
    UCSR0B |= (1 << RXCIE0);

}

/*********************************************************************/
/* Procédure qui envoie un octet de la carte vers le PC              */
/* Paramètre : l'octet à envoyer                                     */
/* Aucune valeur de retour                                           */
/*********************************************************************/
void transmissionUART ( uint8_t data ) {
     /* Wait for empty transmit buffer */
     while ( !( UCSR0A & (1 << UDRE0)) );

     /* Put data into buffer, sends the data */
     UDR0 = data;
}

/************************************************************************************/
/* Procédure qui envoie une chaîne de caractères de la carte vers le PC             */
/* Paramètre : un pointeur vers la chaine à envoyer                                 */
/* Aucune valeur de retour                                                          */
/************************************************************************************/
void transmissionUARTChaine( char* chaine ) {
    uint8_t i = 0;
    while (chaine[i] != '\0') {
        transmissionUART(chaine[i]);
        i++;
    }
}

/*********************************************************************/
/* Procédure qui envoie un octet du PC vers la carte                 */
/* Aucun paramètre                                                   */
/* retour : l'octet envoyé                                           */
/*********************************************************************/
unsigned char receptionUART ( void) {
    
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    
    /* Get and return received data from buffer */
    return UDR0;

}

