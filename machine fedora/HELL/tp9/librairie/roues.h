#ifndef _ROUES_H_
#define _ROUES_H_
#include <avr/io.h>

enum Direction
{
  AVANT,
  ARRIERE,
  DROITE,
  GAUCHE,
  ARRET
};

class Roues
{
public:
void ajustementRoues(const uint8_t vitesseRoueDroite, const uint8_t vitesseRoueGauche, const Direction direction);
};

#endif /* _ROUES_H_ */
