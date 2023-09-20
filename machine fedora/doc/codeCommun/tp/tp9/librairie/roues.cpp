#include "roues.h"
#include "communication.h"
#include <avr/interrupt.h>
#include <avr/io.h>
/**
 * \brief Constructeur par défaut de la classe Roues.
 */
const uint8_t PWM_POURCENT_25 = 255;
Roues::Roues()
{
    DDRD |= (1 << PORTD5) | (1 << PORTD4) | (1 << PORTD3) | (1 << PORTD2);                  // Met les quatre ports de D en mode sortie.
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
    }
}

void Roues::reculerMoteurs(uint8_t gauche, uint8_t droite) {
	PORTD = 0x0C;
    OCR1A = gauche ;  
    OCR1B = droite;	
}
//Fonctions permettant de tourner a gauche
//void roue ::
void Roues:: tournerGauche(){

    OCR1A = 0 ;  
    OCR1B = 127;	
}
//Fonctions permettant de tourner a droite
//void roue :: 
void Roues:: tournerDroite(){
	OCR1A = 127 ;  
    OCR1B = 0;
}


// Fonctions permettant d'arreter les moteurs.
//void roue :: 
void Roues:: arreterMoteurs() {
    OCR1A = 0 ;
    
    OCR1B = 0; 
}


//Fonctions permettant d'avancer à la vitesse désirée.
//void roue :: 
void Roues::  avancerMoteurs(uint8_t gauche, uint8_t droite) {
	PORTD = 0x00;
    OCR1A = gauche ;
}


    
 
