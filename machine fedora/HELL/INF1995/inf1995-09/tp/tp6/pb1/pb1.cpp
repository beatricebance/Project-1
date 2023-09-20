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
#include "memoire_24.h"

enum Color
{
    NONE,
    GREEN,
    RED,
    AMBER
};
//void changeLEDColor(Color c);

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

int main()
{
    DDRA = 0xff;
    Memoire24CXXX m = Memoire24CXXX();
    const int SIZE = 20;
    char str[SIZE] = "ECOLE POLYTECHNIQUE";

    for (int i = 0; i < SIZE; i++)
    {
        m.ecriture(i, str[i]);
        _delay_ms(5);
    }

    bool ok = true;
    for (int i = 0; i < SIZE && ok; i++)
    {
        unsigned char lu = 0;
        m.lecture(i, &lu);
        ok = lu == str[i];
        _delay_ms(5);
    }

    if (ok)
        changeLEDColor(GREEN);
    else
        changeLEDColor(RED);
    return 0;
}
