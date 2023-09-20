/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du bouton poussoir 
  *
 */
#include <avr/io.h>
#include <string.h>
#ifndef UART_H
#define UART_H
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

class UART
{
public:
    UART();
    ~UART();
    void initialisationUART ( void );
    void transmissionUART ( uint8_t donnee );
    uint8_t lectureUART();
    void AffichageUART(char mot[100],uint8_t nbAffichage);
    void afficherMessageDebogage(const char *message);
   
};

#endif /* UART_H */
