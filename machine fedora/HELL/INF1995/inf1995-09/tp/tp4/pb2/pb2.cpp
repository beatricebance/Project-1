#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

//time (s), f (Hz), c (variable to increment)
void PWM(const float f, const float r, volatile uint8_t& out, const uint8_t low = 0, const uint8_t high = 1)
{
	const float cycle = 1.0/f;

	out = high;
	for(int i = 0; i < cycle * r * 1000.0; i++)
		_delay_ms(1);

	out = low;
	for(int i = 0; i < cycle * (1.0-r) * 1000.0; i++)
		_delay_ms(1);
}

enum Direction{FORWARD, BACKWARD};

int main()
{	
	DDRD = 0xff; //Port D is an output (1 = SPEED, 2 = DIR)

    const float FREQ = 60.0;
	const float TIME = 2.0;

	for(int i = 0; i < TIME * FREQ; i++)
		PWM(FREQ, 0.25, PORTD, 0x01, 0x03);

	for(int i = 0; i < TIME * FREQ; i++)
		PWM(FREQ, 0.5, PORTD, 0x01, 0x03);

	for(int i = 0; i < TIME * FREQ; i++)
		PWM(FREQ, 0.75, PORTD, 0x01, 0x03);

	for(int i = 0; i < TIME * FREQ; i++)
		PWM(FREQ, 1.0, PORTD, 0x01, 0x03);

	PORTD = 0x00;

	return 0;
}
