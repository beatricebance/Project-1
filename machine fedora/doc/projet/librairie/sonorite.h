#include "communication.h"
#include <math.h> 

#ifndef SONORITE_H
#define SONORITE_H

class SONORITE : public COMMUNICATION 
{
public:
    SONORITE();
    void ajustementPWM_sonorite (double frequence);
    void arreterSonorite ();
    void jouer(uint8_t note);
    void son_grave();
    void son_aigu();
};
#endif /* SONORITE_H */