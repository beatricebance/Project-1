#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "Magic.h"



bool isPressed()
{
    bool state1 = PIND & 0x04;
    _delay_ms(15);
     bool state2 = PIND & 0x04;
     return state1 && state2;
}

void changeLEDColor(uint8_t c, uint8_t port)
{
    if(c != 3){
        port = c;        
    }
    else
    {
        port = 2;
        _delay_ms(1);
        port = 1;
        _delay_ms(1);
    }
}

//Function to generate PWM on output "out" (PORTx for example), using a frequency "f" and a duty cycle "r"
//To make this generic with any output signal, we can assign custom values to the LOW and HIGH instead of usual 0 and 1
void PWM(const float freq, const float rate, uint8_t out, const uint8_t low, const uint8_t high)
{
	const float cycle = 1.0/freq;

	out = high;
	for(int i = 0; i < cycle * rate * 1000.0; i++)
		_delay_ms(1);

	out = low;
	for(int i = 0; i < cycle * (1.0-rate) * 1000.0; i++)
		_delay_ms(1);
}

//Used to remap a value located in a range towards a new range
void remap(uint8_t value, uint8_t min, uint8_t max, uint8_t newMin, uint8_t newMax)
{
	value = (value - min + newMin) * ((float)(newMax-newMin) / (max-min));
}
