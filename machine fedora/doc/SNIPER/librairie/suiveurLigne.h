/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : classe qui permet au robot de suivre la ligne noir
  *
 */
#ifndef _SUIVEURLIGNE_H_
#define _SUIVEURLIGNE_H_

#define F_CPU 8000000UL
#define CAP_1  PINA & 1<<0
#define CAP_2  PINA & 1<<1
#define CAP_3  PINA & 1<<2
#define CAP_4  PINA & 1<<3
#define CAP_5  PINA & 1<<4


#include <avr/io.h>
#include <util/delay.h>
#include "roues.h"

class SuiveurLigne : public Roues{

public:
        
         void suiveurLigneBoucle_droit();
         void suiveurLigne (); 
         volatile uint8_t compteur = 0;
};
#endif