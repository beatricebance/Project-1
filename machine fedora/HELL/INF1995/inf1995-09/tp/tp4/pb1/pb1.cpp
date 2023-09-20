#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <util/delay_basic.h>

enum Color{NONE, GREEN, RED};

//OBSOLETE SEE PB2
bool PWM(const float time, const float f, float& c, volatile uint8_t& out, const uint8_t low = 0, const uint8_t high = 1)
{
	float cycle = 1.0/f;

	//To avoid float unprecision
	if(c > cycle - 1.0)
		return false;

	out = high;
	_delay_loop_2(cycle - c);

	out = low;
	_delay_loop_2(c);

	c += 1.0/time;

	return true;
}

int main()
{	
	DDRA = 0xff; //Port B is an output (LED+ connected to A2 and LED- connected to A1)

    const float b =  1000.0;	//Duration on the cycle in us
	const float TIME_SECONDS = 3.0;
    float c = 0.0;	//Duration when the LED is off


	while(PWM(TIME_SECONDS, 1.0/b, c, PORTA, NONE, RED));

	return 0;
}
