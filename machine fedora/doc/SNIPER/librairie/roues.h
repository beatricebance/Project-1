/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe Roues
  *
 */

#ifndef _ROUES_H_
#define _ROUES_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


// enumeration des directions
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

};

#endif 
