#include "sonorite.hpp"

/**
 * \brief Constructeur par défaut.
 */
Sonorite::Sonorite()
{
    DDRB |= (1 << PORTB2) | (1 << PORTB3);
    OCR0A = 0;              // quand OCROA = 0 la frequence est maximale = 8 000 000 / (256 * 2) Hz
    PORTB &= (0 << PORTB2); // B2 est toujours 0.
}

/**
 * \fn void Sonorite::sonner(uint8_t note)
 * \brief Fonction qui permet de jouer une note via le piezoelectrique du robot.
 * \param[in] note la note à jouer.
 */
void Sonorite::sonner(uint8_t note)
{
    if (note >= 45 && note <= 81)
    {
        if (!enTrainDeSonner)
        {
            TCCR0A |= (1 << WGM01) | (1 << COM0A0); // CTC mode + Toggle OC0A on Compare Match
            TCCR0B |= (1 << CS02);                  // déviser l'horloge par 256.
        }
        enTrainDeSonner = true;

        OCR0A = (15625 / frequence[note - 45]) - 1; // 15625 = 8 000 000 / (256 * 2)
    }
    else
    {
        DEBUG_PRINT("Erreure: Note en dehors de l'intervalle.");
    }
}

/**
 * \fn void Sonorite::arreter()
 * \brief Fonction qui permet d'arreter de jouer une note en cours d'execution.
 */
void Sonorite::arreter()
{
    enTrainDeSonner = false;
    TCCR0A &= (0 << COM0A0);
}