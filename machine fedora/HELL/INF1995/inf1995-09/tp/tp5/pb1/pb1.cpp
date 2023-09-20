/**
*   File: pb2.cpp
*   Date: 24/01/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/

/*   State table:
    State   Button  State+  DEL
    E0      1       E1      AMBER
    E0      0       E0      RED
    E1      1       E1      AMBER
    E1      0       E2      GREEN
    E2      1       E3      RED
    E2      0       E2      GREEN
    E3      1       E3      RED
    E3      0       E4      NONE
    E4      1       E5      GREEN
    E4      0       E4      NONE
    E5      1       E5      GREEN
    E5      0       E0      RED
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
enum DELState
{
    E0,
    E1,
    E2,
    E3,
    E4,
    E5
};

void initialisation(void);
void changeLEDColor(Color c);

int main()
{
    initialisation();
    changeLEDColor(RED);
    while (true)
        ;
    return 0;
}

volatile DELState delState = E0;

ISR(INT0_vect)
{

    _delay_ms(30);

    bool isPressed = PIND & 0x04;

    switch (delState)
    {
    case E0:
        if (isPressed)
        {
            delState = E1;
            changeLEDColor(AMBER);
        }
        break;
    case E1:
        if (!isPressed)
        {
            delState = E2;
            changeLEDColor(GREEN);
        }
        else
            changeLEDColor(AMBER); //We must repeat to get amber color
        break;
    case E2:
        if (isPressed)
        {
            delState = E3;
            changeLEDColor(RED);
        }
        break;
    case E3:
        if (!isPressed)
        {
            delState = E4;
            changeLEDColor(NONE);
        }
        break;
    case E4:
        if (isPressed)
        {
            delState = E5;
            changeLEDColor(GREEN);
        }
        break;
    case E5:
        if (!isPressed)
        {
            delState = E0;
            changeLEDColor(RED);
        }
        break;
    }
    EIFR |= (1 << INTF0);
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
    DDRA = 0xff; //Port A is an output (LED+ connected to A1 and LED- connected to A2)
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
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
