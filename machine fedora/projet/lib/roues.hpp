#ifndef _ROUES_H_
#define _ROUES_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

enum Direction
{
  AVANT,
  ARRIERE,
  DROITE,
  GAUCHE
};

class Roues
{
public:
  Roues();
  void ajustementRoues(const uint8_t rapportABRoueDroite, const uint8_t rapportABRoueGauche, const Direction direction = AVANT);
  void arretPwmMoteur();
  void demarrerPwmMoteur();
  void tournerGauche90();
  void trounerDroite90();
};

#endif /* _ROUES_H_ */