#ifndef _MAGIC_H
#define _MAGIC_H
#endif
#include <avr/io.h>
#include <util/delay.h>

bool isPressed();
void changeLEDColor(uint8_t c, uint8_t port = PORTA);
void PWM(const float freq, const float rate, uint8_t out, const uint8_t low = 0, const uint8_t high = 1);
void remap(uint8_t value, uint8_t min, uint8_t max, uint8_t newMin, uint8_t newMax);
