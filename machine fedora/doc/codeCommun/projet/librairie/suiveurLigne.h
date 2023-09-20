#ifndef _SUIVEURLIGNE_H_
#define _SUIVEURLIGNE_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define CAP_1  PINA & 1<<0
#define CAP_2  PINA & 1<<1
#define CAP_3  PINA & 1<<2
#define CAP_4  PINA & 1<<3
#define CAP_5  PINA & 1<<4


#define US(x) (PINA & (1 << ((x)-1))) // marche pas dans les boucles

#include <avr/io.h>
#include <util/delay.h>
#include "roues.h"

class SuiveurLigne : public Roues{

public:
         void suiveurLigneBoucle_droit();
         void suiveurLigne ();
         void suiveurLigneCoupure ();
         void suiveurLigneCouloire();
         
         volatile uint8_t compteur = 0;
};
#endif