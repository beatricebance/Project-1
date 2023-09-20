#ifndef _BOUTON_H_
#define _BOUTON_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sirc.hpp"
#include "minuterie.hpp"

enum ETAT
{
  INIT,
  ATTENTE,
};

extern volatile uint8_t compteur;

class Bouton
{
public:
  Bouton();
  void IRControl();

private:
  Minuterie temps_;
  SIRC sirc_;
  ETAT etat_ = INIT;
};

#endif /* _BOUTON_H_ */