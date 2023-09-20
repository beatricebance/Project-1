#ifndef _SUIVEURLIGNE_H_
#define _SUIVEURLIGNE_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h> 
#include <math.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "roues.h"

#define US(x) (PINA & (1 << ((x)-1)))

class SuiveurLigne{

public:
         void suiveurLigne();
};
#endif