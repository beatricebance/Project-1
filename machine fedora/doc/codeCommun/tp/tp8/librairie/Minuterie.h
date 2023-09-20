/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du bouton poussoir 
  *
 */
#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <avr/io.h> 
#include <avr/interrupt.h>

class Minuterie {
public:
	Minuterie();
	void partirMinuterie(uint16_t duree);
	uint8_t getminuterieExpiree();
	bool getminuterieComencee();
	void setminuterieExpiree();
private:
	uint8_t minuterieExpiree_;
	bool minuterieCommencee_;
};
#endif
