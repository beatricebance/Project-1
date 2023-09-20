/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe ROUE
  *
 */

#ifndef ROUE_H
#define ROUE_H

#include <avr/io.h>

class ROUE
{
public:  
    ROUE(); 
    void ajustementPWM(uint8_t VitesseA, uint8_t VitesseB);

    
};

#endif /* ROUE_H */
