#include "uart.hpp"

/**
 *   \brief Constructeur par défaut.
 */
UART::UART()
{
     // 2400 bauds. Nous vous donnons la valeur des deux
     // premier registres pour vous éviter des complications

     UBRR0H = 0;
     UBRR0L = 0xCF;

     // permettre la reception et la transmission par le UART0

     UCSR0A |= 0;                           // Rien à changer dans ce registre (pas de gestion d'erreurs)
     UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Activation de la transmission + la reception.
     UCSR0C |= 0;                           // Rien à changer (mode par défaut: 8 bits, 1 stop bits, none parity).
}

/**
 * \fn void void UART::transmission(uint8_t donnee)
 * \brief Fonction qui permet de transmettre une donnee de la carte vers le PC.
 * \param[in] donnee la donnee à transmettre.
 */
void UART::transmission(uint8_t donnee)
{
     while (!(UCSR0A & (1 << UDRE0)))
     {
     }
     UDR0 = donnee; // transmettre la donnee de l'USART vers PC.
}

/**
 * \fn void UART::transmissionNombre8(uint8_t nombre)
 * \brief Fonction qui permet de transmettre un nombre en hex de la carte vers le PC pour des fins de debogage.
 * \param[in] nombre8 le nombre à transmettre.
 */
void UART::transmissionNombre8(uint8_t nombre8)
{
     char char1, char2;
     if ((nombre8 >> 4) < 10)
          char1 = (nombre8 >> 4) + 48;
     else
          char1 = (nombre8 >> 4) + 55;
     if ((nombre8 & 0xF) < 10)
          char2 = (nombre8 & 0xF) + 48;
     else
          char2 = (nombre8 & 0xF) + 55;
     transmission('0');
     transmission('x');
     transmission(char1);
     transmission(char2);
}

/**
 * \fn void UART::transmissionNombre16(uint16_t nombre16)
 * \brief Fonction qui permet de transmettre un nombre en hex de la carte vers le PC pour des fins de debogage.
 * \param[in] nombre16 le nombre à transmettre.
 */
void UART::transmissionNombre16(uint16_t nombre16)
{
     transmissionNombre8(nombre16 >> 8);
     char char1, char2;
     uint8_t nombre = nombre16;
     if ((nombre >> 4) < 10)
          char1 = (nombre >> 4) + 48;
     else
          char1 = (nombre >> 4) + 55;
     if ((nombre16 & 0xF) < 10)
          char2 = (nombre & 0xF) + 48;
     else
          char2 = (nombre & 0xF) + 55;
     transmission(char1);
     transmission(char2);
}

/**
 * \fn void UART::afficherMessageDebogage(const char *message)
 * \brief Fonction qui pemet d'afficher un message de debogage (char[]) sur l'ecran du PC.
 * \param[in] message le message (un tableau de type char) à transmettre.
 */
void UART::afficherMessageDebogage(const char *message)
{
     for (uint8_t i = 0; i < strlen(message); i++)
     {
          transmission(message[i]);
     }
}

/**
 * \fn uint8_t UART::telechargement()
 * \brief Fonction qui permet de transmettre une donnee du PC vers la memoire externe du robot.
 * \return la donnee à transmettre de type uint8_t.
 */
uint8_t UART::telechargement()
{
     while (!(UCSR0A & (1 << RXC0)))
     {
     }
     return UDR0;
}