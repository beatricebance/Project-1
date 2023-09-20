#include <math.h> 

#ifndef SONORITE_H
#define SONORITE_H
#define F_CPU 8000000UL

class SONORITE 
{
public:
    SONORITE();
    void ajustementPWM_sonorite (double frequence);
    void arreterSonorite ();
    void jouer(uint8_t note);
    void son_grave();
    void son_aigu();

    // Constante sonorite
const double FREQUENCE_LA = 440.0;
const double MIDI_110Hz = 45.0;
const double MIDI_440Hz = 69.0;
const double MIDI_880Hz = 81.0;
const uint8_t TEMPS_QUART = 63;
const uint8_t TEMPS_TIER = 83;
const uint8_t TEMPS_DEMI = 125;
const uint8_t TEMPS_PLEIN = 250;
const uint16_t TEMPS_DOUBLE = 500;
};
#endif 