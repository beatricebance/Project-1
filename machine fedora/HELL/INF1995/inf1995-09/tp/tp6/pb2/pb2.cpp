/**
*   File: pb2.cpp
*   Date: 24/01/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

void initialisationUART(void)
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications

    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la reception et la transmission par le UART0
    UCSR0A |= (1 << TXC0);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXEN1) | (1 << TXEN1);
    //011
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C |= (1 << UCSZ10) | (1 << UCSZ11) | (1 << UCSZ00) | (1 << UCSZ01);
}

void transmissionUART(uint8_t donnee)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main()
{
    initialisationUART();

    uint8_t i, j;
    char mots[21] = "Le robot en INF1995\n";
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 20; j++)
        {
            transmissionUART(mots[j]);
        }
    }
    return 0;
}
