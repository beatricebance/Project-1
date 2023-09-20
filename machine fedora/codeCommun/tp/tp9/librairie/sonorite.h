#include "communication.h"

#ifndef SONORITE_H
#define SONORITE_H

class SONORITE
{
public:
    SONORITE();
    void ajustementPWM_sonorite (double frequence);
    void arreterSonorite ();
    void jouer(uint8_t note);
    void tune_NokiaRingtone ();
    void tune_StarWars ();
};
#endif /* SONORITE_H */