#ifndef _COUPURE_H_
#define _COUPURE_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h> 
#include <math.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "roues.h"


#define US(x) (PINA & (1 << ((x)-1)))

class Coupure
{
public:

 void Les_coupures();
 bool fairecoupure = true ;
};
#endif
