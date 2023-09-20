/**
*   File: pb2.cpp
*   Date: 26/02/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "can.h"

//Enum to handle different LED colors (0x00 = Off, 0x01 = Green, 0x02 = Red)
enum Color
{
    NONE,
    GREEN,
    RED
};

void initialization(void);
void changeLEDColor(Color c);
void PWM(const float f, const float r, volatile uint8_t& out, const uint8_t low = 0, const uint8_t high = 1);
void remap(uint8_t& value, uint8_t min, uint8_t max, uint8_t newMin, uint8_t newMax);


volatile uint8_t button = 0;
uint8_t counter = 0;

int main()
{
    initialization();

    while (true)
    {
		can c;
		uint8_t luminosity = c.lecture(0) >> 2;
		//We found luminosity isn't really between [0, 255] but within [~108, 255] with some adjustements.
		//This is due to the fact the photoresistor has always a base resistance of 4K on 11K, so we'd like to remap the luminosity interval according to this
		remap(luminosity, 108, 255, 0, 255);

		//We set an arbitrary frequency of 100 Hz for smooth color changing
  		const float FREQ = 100.0;
		PWM(FREQ, luminosity/255.0, PORTB, GREEN, RED);		
    }
    return 0;
}



//Initialize our inte_delay_msrrupts
void initialization(void)
{
    DDRB = 0xff; //Port B is an output (LED+ connected to A2 and LED- connected to A1)
}

//Function to generate PWM on output "out" (PORTx for example), using a frequency "f" and a duty cycle "r"
//To make this generic with any output signal, we can assign custom values to the LOW and HIGH instead of usual 0 and 1
void PWM(const float f, const float r, volatile uint8_t& out, const uint8_t low, const uint8_t high)
{
	const float cycle = 1.0/f;

	out = high;
	for(int i = 0; i < cycle * r * 1000.0; i++)
		_delay_ms(1);

	out = low;
	for(int i = 0; i < cycle * (1.0-r) * 1000.0; i++)
		_delay_ms(1);
}

//Used to remap a value located in a range towards a new range
void remap(uint8_t& value, uint8_t min, uint8_t max, uint8_t newMin, uint8_t newMax)
{
	value = (value - min + newMin) * ((float)(newMax-newMin) / (max-min));
}
