#include "roues.hpp"

/**
 * \brief Constructeur par défaut de la classe Roues.
 */
Roues::Roues()
{
    DDRD |= (1 << PORTD7) | (1 << PORTD6) | (1 << PORTD5) | (1 << PORTD4); // Met les quatre ports de D en mode sortie.
    TCCR2B |= (1 << CS20);                                                 // No prescale.
}

/**
 * \fn void Roues::arretPwmMoteur(void)
 * \brief Fonction pour arrêter le signal PWM des deux roues
 */

void Roues::arretPwmMoteur()
{
    TCCR2A &= ~(1 << WGM20) & ~(1 << COM2A1) & ~(1 << COM2B1);
}

/**
 * \fn void Roues::demarrerPwmMoteur(void)
 * \brief Fonction pour démarrer le signal PWM des deux roues
 */

void Roues::demarrerPwmMoteur()
{
    TCCR2A |= (1 << WGM20) | (1 << COM2A1) | (1 << COM2B1) | (0 << COM2A0) | (0 << COM2B0); // inverting mode + mode 1 (PWM, Phase correct, 8 bits).
}

/**
 * \fn void Roues::ajustementRoues(const uint8_t rapportABRoueDroite, const uint8_t rapportABRoueGauche, const Direction direction)
 * \brief Fonction qui permet d'ajuster la direction et la vitesse de rotation des moteurs selon le rapport A/B.
 * \param[in] rapportABRoueDroite la vitesse de rotation de la roue droite (de 0 à 100 %).
 * \param[in] rapportABRoueGauche  la vitesse de rotation de la roue gauche (de 0 à 100 %).
 * \param[in] direction la direction d'avancement du robot.
 */
void Roues::ajustementRoues(const uint8_t rapportABRoueDroite, const uint8_t rapportABRoueGauche, const Direction direction)
{
    OCR2A = 0xFF * (rapportABRoueDroite / 100.0); // pour générer des signaux PWM selon rapport A/B (Port D7).
    OCR2B = 0xFF * (rapportABRoueGauche / 100.0); // pour générer des signaux PWM selon rapport A/B (Port D6).

    switch (direction)
    {

    case AVANT:
    {
        PORTD &= ~(1 << PORTD4) & ~(1 << PORTD5); // PORT D4 = Direction roue gauche; PORT D5 = Direction roue droite.
        break;                                    // 0 pour avancer et 1 pour reculer.
    }

    case ARRIERE:
    {
        PORTD |= (1 << PORTD4) | (1 << PORTD5);
        break;
    }

    case DROITE:
    {
        PORTD &= ~(1 << PORTD5);
        PORTD |= (1 << PORTD4);
        break;
    }

    case GAUCHE:
    {
        PORTD &= ~(1 << PORTD4);
        PORTD |= (1 << PORTD5);
        break;
    }
    }
}

/**
 * \fn void Roues::tournerGauche90()
 * \brief Fonction qui permet de tourner le robot de 90 degres vers la gauche.
 */
void Roues::tournerGauche90()
{
    demarrerPwmMoteur();
    ajustementRoues(60, 60, GAUCHE);
    _delay_ms(700);
    arretPwmMoteur();
}

/**
 * \fn void Roues::tournerGauche90()
 * \brief Fonction qui permet de tourner le robot de 90 degres vers la droite.
 */
void Roues::trounerDroite90()
{
    demarrerPwmMoteur();
    ajustementRoues(60, 60, DROITE);
    _delay_ms(700);
    arretPwmMoteur();
}
