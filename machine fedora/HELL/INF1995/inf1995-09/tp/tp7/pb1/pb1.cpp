/**
*   File: pb2.cpp
*   Date: 21/02/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

//Enum to handle different LED colors (0x00 = Off, 0x01 = Green, 0x02 = Red)
enum Color
{
    NONE,
    GREEN,
    RED,
    AMBER
};

void initialization(void);
void changeLEDColor(Color c);


volatile uint8_t button = 0x04;


int main()
{
    initialization();

    while (true)
    {
        //S0 (reset)
        uint8_t counter = 0;

        //We wait in S0 until the button is pressed
        while (button == 0x04){
        }
        //S1 (button is pressed and held down)
        _delay_ms(100);

        while (counter <= 120 && button == 0)
        {
            counter+=1;
            _delay_ms(100);
        }

        //S2 (Button released)
        changeLEDColor(GREEN);
        _delay_ms(500);
        changeLEDColor(NONE);

        _delay_ms(2000);

        //S3 (blinking)
        for (uint8_t i = 0; i < counter / 2; i++)
        {
            changeLEDColor(RED);
            _delay_ms(250);
            changeLEDColor(NONE);
            _delay_ms(250);
        }

        //S4 (end)
        changeLEDColor(GREEN);
        _delay_ms(500);
        changeLEDColor(NONE);
    }
    return 0;
}

ISR(INT0_vect)
{
    //Anti-rebound
    _delay_ms(10);
    button = PIND & 0x04;
}

//Initialize our interrupts
void initialization(void)
{
    cli();

    DDRD = 0x00; //Port D is an input (Button)
    DDRA = 0xff; //Port A is an output (LED+ connected to A2 and LED- connected to A1)

    EIMSK |= (1 << INT0);

    //Capture both rising and falling edges
    EICRA |= 1 << ISC00;

    sei();
}

//Used to cleanly switch our LED color using seamless enum -> int conversion
void changeLEDColor(Color c)
{
    if (c != AMBER)
    {
        PORTA = c;
    }
    else 
    {
        //If Amber, alternate between Red and Green
        PORTA = RED;
        _delay_ms(1);
        PORTA = GREEN;
        _delay_ms(1);
    }
}
