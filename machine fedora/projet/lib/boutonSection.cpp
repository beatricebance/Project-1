#include "boutonSection.hpp"

volatile bool demarrerSection = false;
volatile uint8_t compteurReceptionIR = 0;

ISR(INT0_vect)
{
    _delay_ms(30); // delais entirebond.
    if (PIND & 0x04)
    {
        demarrerSection = true;
        if (compteurReceptionIR == 9)
            compteurReceptionIR = 1;
        else
            compteurReceptionIR++;
        TCNT1 = 0; // Compter à partir de 0
    }

    EIFR |= (1 << INTF0); // si une seconde interruption intervient durant celle courante,
                          // l'AVR s'en souvient et ISR sera executée après l'interruption courante.
}

/**
 * \brief constructeur de BoutonSection
 */

BoutonSection::BoutonSection()
{
}

/**
 * \fn void BoutonSection::initialiserBoutonSection()
 * \brief fonction qui initialise le bouton en activant les interruptions externes au front montant 
 */

void BoutonSection::initialiserBoutonSection()
{
    DDRD &= ~(1 << PORTD2);
    cli();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    sei();
    demarrerSection = false;
    compteurReceptionIR = 0;
}

/**
 * \fn BoutonSection::arreterBoutonSection()
 * \brief désactive les interrutpions externes pour le bouton poussoir
 */

void BoutonSection::arreterBoutonSection()
{
    DDRD |= (1 << PORTD2);
    EIMSK &= ~(1 << INT0);
    cli(); // Arret de toutes les interruptions.
}