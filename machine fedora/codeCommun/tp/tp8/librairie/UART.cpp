/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe UART
  *
 */

#define F_CPU   8000000UL
#include "UART.h"

//Constructeur par defaut
UART::UART()
{
    initialisationUART();
}

//Destructeur
UART::~UART()
{
}

/*
	*initialisation de la fonction qui permet la transmission par UART0
*/
void UART::initialisationUART ( void ) {

	// 2400 bauds. Nous vous donnons la valeur des deux

	// premier registres pour vous éviter des complications

	UBRR0H = 0;

	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0

    //UCSR0A |= (1 << RXC0) | (1 << TXC0);
	UCSR0A &= ~(_BV(U2X0));

	UCSR0B |= _BV(RXEN0) | _BV(TXEN0);

	// Format des trames: 8 bits, 1 stop bits, none parity

	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);

}

/*
	*Fonction qui Transmettre la donnee a UDR0 si le transmit buffer est vide (Indiqué par UDRE0) 
	*et que le registre de control et statut du UART est prêt 
*/
void UART::transmissionUART ( uint8_t donnee ) {
	
	while ( !( UCSR0A & (1<<UDRE0)) );
	
	UDR0 = donnee;
}

/*
	*Fonction qui Retourne la donnée chargée dans le recieve buffer
*/
uint8_t UART::lectureUART() {
    while(!((UCSR0A)&(1 << RXC0))); //RXC0 = USART COMPLETRE FLAG
    return UDR0; //UDR0 = RECEIVE BUFFER
}

/*
	*Fonction qui Fait la lecture de la mémoire et afficher celle-ci par le UART
*/

void UART::AffichageUART(char mot[100],uint8_t nbAffichage){
    for (uint8_t i = 0; i < nbAffichage; i++ ) {
        for (uint8_t j = 0; j < 100; j++ )
            transmissionUART(mot[j]);
    }

}

/**
 * \fn void UART::afficherMessageDebogage(const char *message)
 * \brief Fonction qui pemet d'afficher un message de debogage (char[]) sur l'ecran du PC.
 * \param[in] message le message (un tableau de type char) à transmettre.
 */
void UART::afficherMessageDebogage(const char* message)
{
     for (uint8_t i = 0; i < strlen(message); i++)
     {
          transmissionUART(message[i]);
     }
}
