#ifndef _MAGIC_H
#define _MAGIC_H
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum Color{NONE, GREEN, RED, ORANGE};

enum Register{ OCR1A_, OCR1B_, OCR0A_, OCR0B_};

bool isPressed();
void changeLEDColor(Color c);
void PWM_L(const float freq, const float rate, volatile uint8_t&  out, const uint8_t low = 0, const uint8_t high = 1);
void remap(uint8_t value, uint8_t min, uint8_t max, uint8_t newMin, uint8_t newMax);

void initialisation ( );
void PWM_M_Wheel(const float freqL, const float freqR);
void PWM_M_Buzzer(const float freq);

#endif
