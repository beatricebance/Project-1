#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "Magic.h"
int main(){
	int x = 0;
	if (isPressed()){
		x++;
	}
}
