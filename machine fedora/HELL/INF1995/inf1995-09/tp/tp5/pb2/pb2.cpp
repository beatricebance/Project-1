/**
*   File: pb2.cpp
*   Date: 24/01/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <util/delay_basic.h>

enum Color
{
    NONE,
    GREEN,
    RED,
    AMBER
};

void initialisation(void);
void changeLEDColor(Color c);
void partirMinuterie(uint16_t duree);
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

bool isPressed()
{
    bool state1 = PIND & 0x04;
    _delay_ms(10);
    bool state2 = PIND & 0x04;
    return state1 && state2;
}

int main()
{
    initialisation();
    _delay_ms(10000);
    changeLEDColor(RED);
    _delay_ms(100);
    changeLEDColor(NONE);
    partirMinuterie(F_CPU/1024);
    do
    {
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    } while (minuterieExpiree == 0 && boutonPoussoir == 0);
    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli();
    // Verifier la réponse
    changeLEDColor(boutonPoussoir==1?GREEN:NONE);
return 0;
}

ISR(TIMER0_COMPA_vect)
{
    minuterieExpiree = 1;
}

ISR(INT0_vect)
{

    boutonPoussoir = isPressed();
}
void partirMinuterie(uint16_t duree)
{
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée

    TCNT1 = 0x0000;
    OCR1A = duree;
    TCCR1A = 0b01010000;
    TCCR1B = 0b00001101; //Page 179
    TCCR1C = 0b10000000;
    TIMSK1 = 0b00100010;
}

void initialisation(void)
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRD = 0x00; //Port D is an input (Button)
    DDRA = 0xff; //Port A is an output (LED+ connected to A2 and LED- connected to A1)
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    //EIMSK |= (2 << TIMER1_COMPA);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= 0x01;
    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

void changeLEDColor(Color c)
{
    if (c != AMBER)
    {
        PORTA = c;
    }
    else
    {
        PORTA = RED;
        _delay_ms(31);
        PORTA = GREEN;
        _delay_ms(1); // here we wait less than 11ms because we will already wait 10ms for the next isPressed to execute
    }
}
