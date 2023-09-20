#ifndef F_CPU
#define F_CPU 8000000
#endif

#include "Magic.h"


bool isPressed()
{
    bool state1 = PIND & 0x04;
    _delay_ms(15);
    bool state2 = PIND & 0x04;
    return state1 && state2;
}

void changeLEDColor(Color c)
{
    if(c != ORANGE){
        PORTB = c;        
    }
    else
    {
        PORTB = 2;
        _delay_ms(1);
        PORTB = 1;
        _delay_ms(1);
    }
}

//Function to generate PWM on output "out" (PORTx for example), using a frequency "f" and a duty cycle "r"
//To make this generic with any output signal, we can assign custom values to the LOW and HIGH instead of usual 0 and 1
void PWM_L(const float freq, const float rate, volatile uint8_t& out, const uint8_t low, const uint8_t high)
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

void initialisation ( void ) {

	cli ();

	DDRD = 0xff; // Le port D est une SORTIE

	// cette procédure ajuste le registre EIMSK
	// de l’ATmega324PA pour permettre les interruptions externes
	EIMSK |= (1 << INT0);

	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA
	EICRA |= (1 << INT0);

	sei ();
}

void PWM_M_Wheel(const float freqL, const float freqR)
{
	OCR1A = freqR;
	OCR1B = freqL;
	
	//Pour les moteurs
    TCCR1A |= (1 << COM1B1) | (1 << COM1A1) |(1 << WGM10);
	TCCR1B |= (1 << CS11);
	TCCR1C = 0;
}

void PWM_M_Buzzer(const float freq)
{
	float TOP = (F_CPU/(2*64*freq))-1;
	OCR0A = TOP;
	OCR0B = TOP * 0.5;
	
    TCCR0A |= (1 << WGM00) |(1 << WGM01) | (1<<COM0A0) | (1<<COM0B1) | (1<<COM0B0); 
    TCCR0B |= (1 << WGM02) | (1<<CS01)  | (1<<CS00);
}
