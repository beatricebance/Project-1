#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>
#include "UART.h"
#include "moteur.h"
#include "communication.h"
#include "DEL.h"
// Constante couleur DEL
const uint8_t ROUGE = 0x02 ;
const uint8_t VERT = 0x01 ;
const uint8_t ETEINT = 0x00 ;

// Declaration des variables
static volatile uint16_t pulse = 0;
static volatile int i = 0;
volatile uint16_t debordement=0;

// fonction initialisation du timer
void initialisation(void){
    cli();
    // les autres broches en sortie et la broche 3 du port B en mode entree
    DDRB = 0b11111011;  
    // Mettre les broches du PORT A en sortie 
    DDRA = 0xFF;
    
    EIMSK |= (1 << INT2);
    EICRA |= (1 << ISC20);
    TCCR0B = 0;
    sei();
     // Initialiser le compteur du debordement 
}

ISR(INT2_vect)
{
    if (i==1)
    {   
		TCCR0B=0;
		TIMSK0 &=~(1<<TOIE0); // no clock source/on arrete le compteur 
        pulse=TCNT0+(256*debordement); 
        TCNT0=0;
        i=0;	
    }
    if (i==0)
    {
		debordement=0;
        TCCR0B|=(1<<CS01);
		TIMSK0 |= (1<<TOIE0); //clock/8 --> tcnt1 incremente chaque 1 microseconde simplifie le calcul pas besoin de convertir le pulse
        i=1;
    }
}
ISR(TIMER0_OVF_vect) 
{
	++debordement;
}

int main(void)
{     
    initialisation();
    UART uart;
    DEL light;
    Moteur moteur;
    uint16_t distance = 0;
    DDRB|=_BV(DDB0);
    DDRB &=~_BV(DDB2);
    PORTB |= 0b00000011;
    _delay_us(15);
    PORTB |= 0b00000000;
    moteur.avancer(60.0,60.0);
    while(true)
    {
        PORTB|=_BV(PINB0);
        _delay_us(15);
        PORTB &=~_BV(PINB0);
        distance = pulse/58;
        //_delay_ms(50);
        uart.transmissionUART(distance) ;
        if((distance < (13)) ){
            light.Couleur(ROUGE);
        }else if ((distance > (17)) ){
            light.Couleur(VERT);
        } else if ((distance >= (13)) && ((distance <= (17)))){
            light.Couleur(ETEINT);
            moteur.avancer(60.0,60.0);
        }
            _delay_ms(50);
    } 
}