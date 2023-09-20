/**
*   File: pb2.cpp
*   Date: 24/01/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

void initialisation(void);
void ajustementPWM(uint8_t rate);

int main()
{
    initialisation();
    const int DUREE_MS = 2000;
    PORTD = 0b100;

    ajustementPWM(25);
    _delay_ms(DUREE_MS);

    ajustementPWM(50);
    _delay_ms(DUREE_MS);

    ajustementPWM(75);
    _delay_ms(DUREE_MS);

    ajustementPWM(100);
    _delay_ms(DUREE_MS);
        
    PORTD = 0;
        
    return 0;
}

/*ISR(TIMER0_COMPB_vect)
{
    PORTD = OC1B | 0b10;
}*/

void ajustementPWM(uint8_t rate)
{
    OCR1A = 0xff * (rate/100.0);
    //OCR1B = 0xff * (rate/100.0);
    TCCR1A |= (1<<COM1A1) | (1<< WGM10);
    TCCR1B |= 1<<CS11; //Page 179
    TCCR1C = 0;//1<<FOC1A;
    //TIMSK1 = 0b00100110;

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
}

void initialisation(void)
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRD = 0xff; //Port D is an output 
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    //EIMSK |= (1 << INT0);
    //EIMSK |= (2 << TIMER1_COMPA);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau dINT0u bouton-poussoir
    // en ajustant le registre EICRA
    //EICRA |= 0x01;
    // sei permet de recevoir à nouveau des interruptions.
    sei();
}