/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du bouton poussoir 
  *
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>

class UART
{
public:
    UART();
    ~UART();
    void initialisationUART ( void );
    void transmissionUART ( uint8_t donnee );
    uint8_t lectureUART();
    void AffichageUART(char mot[100],uint8_t nbAffichage);

   
};

#endif /* UART_H */
