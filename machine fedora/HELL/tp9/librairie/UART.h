/*
  * Nom: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  Classe UART pour la transmission 
  *
 */

#ifndef UART_H
#define UART_H
#include <avr/io.h>

class UART
{
public:
    void initialisationUART ( void );
    void transmissionUART ( uint8_t donnee );
    void transmissionUARTChaine( char* chaine );
    char lectureUART(void);
    void afficherMessageDebogage(const char *message);
    void AffichageUART(char mot[100],uint8_t nbAffichage);
};

#endif /* UART_H */
