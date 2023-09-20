#include "sirc.hpp"

SIRC::SIRC()
{
}

/**
 * \fn void SIRC::initialiserTransmissionIR(void).
 * \brief fonction qui permet d'initilaiser la transmission du signal infrarouge.
 */
void SIRC::initialiserTransmissionIR()
{
    DDRB |= (1 << PORTB1) | (1 << PORTB3); // B3 = PWM ; B1 = GND.
    OCR0A = 0x70;                          // OCROA = 0x68 (104) => frequence = 8 000 000 / 2 * (1 + 104) = 38 kHz
    TCCR0A |= (1 << WGM01);                // CTC mode
    TCCR0B |= (1 << CS00);                 // No prescaling => horloge = 8 MHz.
    PORTB &= ~(1 << PORTB1);               // B1 est toujours 0 = GND.
}

void SIRC::arreterTransmissionIR()
{
    OCR0A = 0;               // OCROA = 0x68 (104) => frequence = 8 000 000 / 2 * (1 + 104) = 38 kHz
    TCCR0A &= ~(1 << WGM01); // CTC mode
    TCCR0B &= ~(1 << CS00);  // No prescaling => horloge = 8 MHz.
}

/**
 * \fn void SIRC::transmissionIR(const COMMANDE commande, const ADRESSE adresse).
 * \brief fonction qui permet la transmission du signal infrarouge. En validant 3 fois
   la transmission émit par le deuxième robot.
 * \param[in] commande Commande de transmission.
 * \param[in] adresse Adresse de transmission.
 */
void SIRC::transmissionIR(const COMMANDE commande, const ADRESSE adresse)
{
    for (uint8_t i = 0; i < 3; i++) // 3 fois la transmission de la même chose pour validation.
    {
        // Debut de la transmission
        TCCR0A |= (1 << COM0A0);  // Depart PWM
        _delay_us(2400);          // delais 2,4 ms = signaler le debut de la transmission
        TCCR0A &= ~(1 << COM0A0); // Arret PWM
        _delay_us(600);           // delais 0,6 ms

        // Transmission de la commande de longeur 7 bits (du LSB vers MSB)
        for (uint8_t j = 0; j < 7; j++)
        {
            if ((commande >> j) & 0x01) // Transmission d'un bit = 1
            {
                TCCR0A |= (1 << COM0A0);  // Depart PWM
                _delay_us(1200);          // delais 1,2 ms = 1 logique
                TCCR0A &= ~(1 << COM0A0); // Arret PWM
                _delay_us(600);           // delais 0,6 ms = intervalle entre chaque bit transmis
            }
            else if (!((commande >> j) & 0x01)) // Transmission d'un bit = 0
            {
                TCCR0A |= (1 << COM0A0);  // Depart PWM
                _delay_us(600);           // delais 0,6 ms = 0 logique
                TCCR0A &= ~(1 << COM0A0); // Arret PWM
                _delay_us(600);           // delais 0,6 ms = intervalle entre chaque bit transmis
            }
        }

        // Transmission de l'adresse de longeur 5 bits (du LSB vers MSB)
        for (uint8_t k = 0; k < 5; k++)
        {
            if ((adresse >> k) & 0x01) // Transmission d'un bit = 1
            {
                TCCR0A |= (1 << COM0A0);  // Depart PWM
                _delay_us(1200);          // delais 1,2 ms = 1 logique
                TCCR0A &= ~(1 << COM0A0); // Arret PWM
                _delay_us(600);           // delais 0,6 ms = intervalle entre chaque bit transmis
            }
            else if (!((adresse >> k) & 0x01)) // Transmission d'un bit = 0
            {
                TCCR0A |= (1 << COM0A0);  // Depart PWM
                _delay_us(600);           // delais 0,6 ms = 0 logique
                TCCR0A &= ~(1 << COM0A0); // Arret PWM
                _delay_us(600);           // delais 0,6 ms = intervalle entre chaque bit transmis
            }
        }
    }
}

/**
 * \fn void SIRC::initialiserReceptionIR().
 * \brief fonction qui permet d'initilaiser la réception du signal infrarouge.
 */

void SIRC::initialiserReceptionIR()
{
    TCNT1 = 0;              // Compteur de 16 bits à partir de 0.
    TCCR1B |= (1 << CS10);  // No prescaling => horloge = 8 MHz.
    DDRC &= ~(1 << PORTC3); // C3 mode entree pour recevoir IR signal.
}

void SIRC::arreterReceptionIR()
{
    TCCR1B &= ~(1 << CS10); // No clock source.
}

/**
 * \fn bool SIRC::receptionIR(uint8_t &commandeRecue, uint8_t &adresseRecue).
 * \brief fonction qui permet de recevoir le signal infrarouge du deuxieme robot. On verifie 2 fois sur 3   
 * si le signal est bien emit par le deuxieme fois et non par des interferences exterieures, avant de faire la commande.
 * \param[out] &commandeRecue Commande de reception.
 * \param[out] &adresseRecue Adresse de reception.
 * return un bool qui verifie si le signal est emit par le deuxieme robot.
 */
bool SIRC::receptionIR(uint8_t &commandeRecue, uint8_t &adresseRecue)
{
    uint16_t time[3][13] = {}; // Pour stocker le temps de chaque pulsation.
    uint8_t commandeTemp[3] = {};
    uint8_t adresseTemp[3] = {};

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 13; j++)
        {
            {
                while (PINC & 0x08)
                    ;
                TCNT1 = 0;
                while (!(PINC & 0x08))
                    ;
                time[i][j] = TCNT1;
            }
        }
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 13; j++)
        {
            if (((time[i][j] >= 15000) && (time[i][j] <= 23000)) && (j == 0)) // if  2,250 ms <= time <= 2,625 m => start.
            {
                continue;
            }
            else if (!((time[i][j] >= 15000) && (time[i][j] <= 23000)) && (j == 0)) // if time hors plages permises
            {
                break;
            }

            if (j < 8)
            {
                if ((time[i][j] >= 8000) && (time[i][j] <= 12000)) // 1,063 ms <= time <= 1,388 ms => logical "1".
                {
                    commandeTemp[i] |= (1 << (j - 1));
                }
                else if ((time[i][j] >= 3000) && (time[i][j] <= 7000)) // 0,531 ms <= time <= 0,693 ms => logical "0".
                {
                    commandeTemp[i] &= ~(1 << (j - 1));
                }
                else if (!((time[i][j] >= 8000) && (time[i][j] <= 12000)) && !((time[i][j] >= 3000) && (time[i][j] <= 7000))) // if time hors plages permises.
                {
                    break;
                }
            }
            else if (j > 7)
            {
                if ((time[i][j] >= 8000) && (time[i][j] <= 12000)) // 1,063 ms <= time <= 1,388 ms => logical "1".
                {
                    adresseTemp[i] |= (1 << (j - 8));
                }
                else if ((time[i][j] >= 3000) && (time[i][j] <= 7000)) // 0,531 ms <= time <= 0,693 ms => logical "0".
                {
                    adresseTemp[i] &= ~(1 << (j - 8));
                }
                else if (!((time[i][j] >= 8000) && (time[i][j] <= 12000)) && !((time[i][j] >= 3000) && (time[i][j] <= 7000))) // if time hors plages permises
                {
                    break;
                }
            }
        }
    }

    if ((commandeTemp[0] == commandeTemp[1]) && (commandeTemp[0] != 0) && (commandeTemp[1] != 0))
    {
        commandeRecue = commandeTemp[0];
        return true;
    }
    else if ((commandeTemp[0] == commandeTemp[2]) && (commandeTemp[0] != 0) && (commandeTemp[2] != 0))
    {
        commandeRecue = commandeTemp[0];
        return true;
    }
    else if ((commandeTemp[1] == commandeTemp[2]) && (commandeTemp[1] != 0) && (commandeTemp[2] != 0))
    {
        commandeRecue = commandeTemp[1];
        return true;
    }
    else
    {
        return false;
    }

    if ((adresseTemp[0] == adresseTemp[1]) && (adresseTemp[0] != 0) && (adresseTemp[1] != 0))
    {
        adresseRecue = adresseTemp[0];
        return true;
    }
    else if ((adresseTemp[0] == adresseTemp[2]) && (adresseTemp[0] != 0) && (adresseTemp[2] != 0))
    {
        adresseRecue = adresseTemp[0];
        return true;
    }
    else if ((adresseTemp[1] == adresseTemp[2]) && (adresseTemp[1] != 0) && (adresseTemp[2] != 0))
    {
        adresseRecue = adresseTemp[1];
        return true;
    }
    else
    {
        return false;
    }
}
