/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : classe Coupure
  *
 */
#ifndef _COUPURE_H_
#define _COUPURE_H_
#define F_CPU 8000000UL

#include <avr/io.h> 
#include <math.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "roues.h"
#include "sonorite.h"


class Coupure
{
public:

 void Les_coupures();
 bool fairecoupure = true;
};
#endif
