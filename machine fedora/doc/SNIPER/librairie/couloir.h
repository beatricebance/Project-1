/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : classe Couloir
  *
 */
#ifndef _COULOIR_H_
#define _COULOIR_H_
#define F_CPU 8000000UL
#include <avr/io.h> 
#include <math.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "roues.h"




class Couloir
{
public:

 void Le_couloir();
 bool debutZone_BG = true;
 bool Zonevide =true;
 
};
#endif
