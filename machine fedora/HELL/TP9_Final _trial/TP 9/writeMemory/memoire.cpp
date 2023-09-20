#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"
#include "PWM.h"
#include "UART.h"



int main(){
	

	Memoire24CXXX memoire = Memoire24CXXX(); 
	initialisationUART();
	
	uint8_t lecture;
	uint16_t adresse = 0x00;
	uint8_t* data;


	do {
		lecture = USART_Receive();
		memoire.ecriture(adresse++, lecture);
	
	} while (!(lecture == 0xff && adresse % 2 == 1)); 
	
	adresse=0x00; // remise de l adresse a 0x00 pour l affichage qui suit

	do { //Peremt l affichage des donnes a lecran, a titre de verification
		memoire.lecture(adresse++, data);
		
		USART_Transmit(*data);		
	
	} while (!(*data == 0xff && adresse % 2 == 1));

 
	
	for (int i = 0; i < 5; i++)  //Permet de verifier que l ecriture en memoire est termine, avec un clignotement
	{ 
		setColor(rouge);
		_delay_ms(100);
		setColor(vert);
		_delay_ms(100);
	}

	setColor(eteint);
			
	return 0;
}
