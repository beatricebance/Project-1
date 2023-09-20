// DESCRIPTION: Programme contenant la definition de la classe Bouton         //
//              qui permet  d'activer l'interruption externe et de savoir     //
//              l'etat du bouton poussoir.                                    //
////////////////////////////////////////////////////////////////////////////////

#ifndef _BOUTON_SECTION_H_
#define _BOUTON_SECTION_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sirc.hpp"
#include "minuterie.hpp"

extern volatile bool demarrerSection;
extern volatile uint8_t compteurReceptionIR;

class BoutonSection
{
  public:
    BoutonSection();
    void initialiserBoutonSection();
    void arreterBoutonSection();
};

#endif /* _BOUTON_SECTION_H_ */