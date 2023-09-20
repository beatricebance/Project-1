#ifndef _SONORITE_H_
#define _SONORITE_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include "debug.hpp"

class Sonorite
{
public:
  Sonorite();
  void sonner(uint8_t note);
  void arreter();

private:
  bool enTrainDeSonner = false;
  uint16_t frequence[37] = {
      110, 117, 123, 131, 139,
      147, 156, 165, 175, 185,
      196, 208, 220, 233, 247,
      262, 277, 294, 311, 330,
      349, 370, 392, 415, 440,
      466, 494, 523, 554, 587,
      622, 659, 698, 740, 784,
      831, 880};
};

#endif /* _SONORITE_H_ */