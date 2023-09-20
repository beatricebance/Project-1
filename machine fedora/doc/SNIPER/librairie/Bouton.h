/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du bouton poussoir et interrupt
  *
 */
#ifndef BOUTON_H
#define BOUTON_H

#define F_CPU 8000000UL
#include <avr/io.h>  
#include <avr/interrupt.h>
#include <util/delay.h>


class BOUTON {
public:
  void initialisation(void);
  void initialisation_2(void);
  volatile uint8_t bouton_poussoir = 0;
  volatile uint8_t bouton_interrupt = 0;

};
#endif