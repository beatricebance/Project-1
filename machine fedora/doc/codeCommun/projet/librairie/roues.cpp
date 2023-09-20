#include "roues.h"
#include "communication.h"
#include <avr/interrupt.h>
#include <avr/io.h>
/**
 * \brief Constructeur par défaut de la classe Roues.
 */

Roues::Roues()
{
    DDRD |= (1 << PORTD5) | (1 << PORTD4) | (1 << PORTD6) | (1 << PORTD7);                  // Met les quatre ports de D en mode sortie.
    TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1) | (0 << COM1A0) | (0 << COM1B0); // inverting mode + mode 1 (PWM, Phase correct, 8 bits).
    TCCR1B |= (1 << CS11);                                                                  // déviser l'horloge par 8.
    TCCR1C = 0;
}

/**
 * \fn void Roues::ajustementRoues(void)
 * \brief Fonction qui permet d'ajuster la direction et la vitesse de rotation des moteurs selon le rapport A/B.
 * \param[in] rapportABRoueDroite la vitesse de rotation de la roue droite (de 0 à 100 %).
 * \param[in] rapportABRoueGauche  la vitesse de rotation de la roue gauche (de 0 à 100 %).
 * \param[in] direction la direction d'avancement du robot.
 */
void Roues::ajustementRoues(const uint8_t rapportABRoueDroite, const uint8_t rapportABRoueGauche, const Direction direction)
{
    OCR1A = 0xFF * (rapportABRoueDroite / 100.0); // pour générer des signaux PWM selon rapport A/B (Port D5).
    OCR1B = 0xFF * (rapportABRoueGauche / 100.0); // pour générer des signaux PWM selon rapport A/B (Port D4).

    switch (direction)
    {

    case AVANT:
    {
        PORTD &= (0 << PORTD4) | (0 << PORTD5); // PORT D4 = Direction roue gauche; PORT D5 = Direction roue droite.
        break;                                  // 0 pour avancer et 1 pour reculer.
    }

    case ARRIERE:
    {
        PORTD |= (1 << PORTD4) | (1 << PORTD5);
        break;
    }

    case DROITE:
    {
        PORTD &= (0 << PORTD5);
        PORTD |= (1 << PORTD4);
        break;
    }

    case GAUCHE:
    {
        PORTD &= (0 << PORTD4);
        PORTD |= (1 << PORTD5);
        break;
    }
    }
}


    
 
