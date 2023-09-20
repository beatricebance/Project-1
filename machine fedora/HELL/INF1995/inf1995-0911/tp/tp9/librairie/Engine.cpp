#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Magic.h"
#include "Engine.h"

Engine::Engine(){
}

void Engine::move(uint8_t speed, Direction dir){
	
	float FRQ_ENGINE = speed;
	PORTD = 0x00;
	
	if (dir == Forward){
		PWM_M_Wheel(FRQ_ENGINE, FRQ_ENGINE);
	}
	else if (dir == Right){
		PWM_M_Wheel(FRQ_ENGINE,0);
	}
	else if (dir == Left){
		PWM_M_Wheel(0,FRQ_ENGINE);
	}
	else {
		PWM_M_Wheel(FRQ_ENGINE, FRQ_ENGINE);
		// pour que la polarite soit inverser on ajoute des 1 dans la 2e pin
		// d'ou la raison pour laquelle les moteurs doivent etre connecter aux
		// ports : D5-D7 et D6-D8
		PORTD = 0b11000000;
	}
}

void Engine::stop(){
	PWM_M_Wheel(1,1);
	PORTD = 0x00;
}
