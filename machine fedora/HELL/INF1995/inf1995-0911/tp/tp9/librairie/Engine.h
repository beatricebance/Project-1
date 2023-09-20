#ifndef _ENGINE_H
#define _ENGINE_H
#include <avr/io.h>
#include "Magic.h"

enum Direction { Forward, Backward, Right, Left };

class Engine
{
    /* La roue droite: OCR1A -- la broche 6: vitesse
                             -- la broche 8: direction
       La roue gauche: OCR1B -- la broche 5: vitesse
                             -- la broche 7: direction */
  public:
	Engine();
    void move(uint8_t speed, Direction dir);
    void stop();
};
#endif
