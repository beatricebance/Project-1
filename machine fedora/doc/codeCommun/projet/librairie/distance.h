/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du suiveur de ligne
  *
 */
#ifndef DISTANCE_H
#define DISTANCE_H

#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>


class Distance {
public:
void initialisationTimer0(void);
void sonar();
//void redresser();
bool parcour = true;
bool fairesonar =true;


};
#endif