#include "roues.h"
#include <avr/interrupt.h>
#define PWM_MAX 255
#define PWM_POURCENT_MAX 100


/**
 * \ void Roues::ajustementRoues(void)
 * \permet d'ajuster la direction et la vitesse de rotation des moteurs selon le rapport A/B.
 * \vitesseRoueDroite: la vitesse de rotation de la roue droite (de 0 à 100 %).
 * \vitesseRoueGauche : la vitesse de rotation de la roue gauche (de 0 à 100 %).
 * \direction: la direction d'avancement du robot.
 */
void Roues::ajustementRoues(const uint8_t vitesseRoueDroite, const uint8_t vitesseRoueGauche, const Direction direction)
{
    // pour générer des signaux PWM selon rapport A/B (Port D5).
    OCR1A = (vitesseRoueDroite / PWM_MAX)* PWM_POURCENT_MAX; 

   // pour générer des signaux PWM selon rapport A/B (Port D4).
    OCR1B = (vitesseRoueGauche / PWM_MAX)*PWM_POURCENT_MAX; 


    // division d'horloge par 8 - implique une frequence de PWM fixe
    // 8-bit phase correct
    TCCR1A = (1 << COM1A1) | (1 << COM1B1)| (1 << WGM10);
    // Prescaler de 8
    TCCR1B = (1 << CS11) ;
    TCCR1C = 0;

    switch (direction)
    {

    case AVANT:
    {
        PORTD &= (0 << PORTD2) | (0 << PORTD3); // PORT D2 = Direction roue gauche; PORT D3 = Direction roue droite.
        break;                                  // 0 pour avancer et 1 pour reculer.
    }

    case ARRIERE:
    {
        PORTD |= (1 << PORTD2) | (1 << PORTD3);
        break;
    }

    case DROITE:
    {
        PORTD &= (0 << PORTD3);
        PORTD |= (1 << PORTD2);
        break;
    }

    case GAUCHE:
    {
        PORTD &= (0 << PORTD2);
        PORTD |= (1 << PORTD3);
        break;
    }
    case ARRET:
    {
        PORTD &= (0 << PORTD2);
        PORTD |= (0 << PORTD3);
        break;
    }


    }
}
