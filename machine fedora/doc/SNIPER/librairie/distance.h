/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe distance pour faire le parcours HIJKL
  *
 */
#ifndef DISTANCE_H
#define DISTANCE_H
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "DEL.h"
#include "roues.h"
#include "suiveurLigne.h"


class Distance {
public:
void initialisationTimer0(void);
void sonar();
};
#endif