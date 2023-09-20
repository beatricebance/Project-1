/*
  * Nom: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe UART
  *
 */
#include "UART.h"
#include <string.h>


/******************************************************************************
* Fonction: initialisationUART                                                                  
* Description: Initialisation des registre qui permettent la communication RS232      															  
* Paramètres: aucun
* Retour: aucun                                                                 
******************************************************************************/

void UART:: initialisationUART ( void ) {

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


/******************************************************************************
* Fonction: transmissionUART                                                                 
* Description: Transmettre la donnee a UDR0 si le transmit buffer est vide       															  
* Paramètres: uint8_t donnee
* Retour: aucun                                                                 
******************************************************************************/

void UART::transmissionUART (uint8_t donnee) {
	 /* Verifie si le buffer est vide */
	while ( !( UCSR0A & (1<<UDRE0)) );

   /* enregistre les donnees dans le buffer*/
	UDR0 = donnee;
}



/******************************************************************************
* Fonction: lectureUART                                                                
* Description: Fonction qui Retourne la donnée chargée dans le buffer      															  
* Paramètres: aucun
* Retour: aucun                                                                 
******************************************************************************/

char UART::lectureUART(void) {
    while(!((UCSR0A)&(1 << RXC0))); //RXC0 = USART COMPLETRE FLAG
    return UDR0; //UDR0 = RECEIVE BUFFER
}



/**********************************************************************************************
* Fonction: afficherMessageDebogage                                                                
* Description: Fonctions qui pemet d'afficher un message de debogage sur l'ecran du PC via RS32   															  
* Paramètres: const char* message
* Retour: aucun                                                                 
***********************************************************************************************/

void UART::afficherMessageDebogage(const char* message)
{
     for (uint8_t i = 0; i < strlen(message); i++)
     {
          transmissionUART(message[i]);
     }
}
