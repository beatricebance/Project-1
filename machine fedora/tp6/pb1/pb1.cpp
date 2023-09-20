
/*

 * Nom du fichier : Probleme1.cpp
 * Auteur : Hakim Mektoub (1956925), Malek Demdoum (1887467)
 * Date : 11 Octobre 2019
 * Description : Changer les couleurs de la DEL en utilisant un bouton poussoir sur la breadboard
 *Tableau des etats
 ETAT PRESENT               BOUTON_POUSSOIR         ETAT SUIVANT              SORTIE
 
 INIT                        1                        TIMER_COMMENCE            00
 TIMER_COMMENCE              1                        VERT_0                    00
 Vert0                       1                        RIEN                      10
 RIEN                        1                        ROUGE0                    00
 ROUGE0                      1                        VERT1                     01
 VERT1                       1                        INIT                      10
  ____________________________________________________________________________________
 On utilise deux routines d'interruptions, une qui incremente notre compteur a chaque fois que le timer atteint la valeur OCR1A soit, a chaque 10ms
 L'autre gere le bouton poussoir.
 notre del libre est liee aux PORTS 0 et 1 de PORTB
 Notre fil rouge/noir est lie comme suit: rouge -> Vcc, noir -> Ground
 Notre fil bleu/brun est lie tel que le fil bleu se trouve sur le port D2
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/twi.h>

//declarations des constantes
const uint8_t BOUTTON_APPUYE = 0x04;
const uint8_t BOUTTON_NON_APPUYE = 0x00;
const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;
const uint8_t ROUGE = 0b01;
const uint8_t VERT = 0b10;
const uint8_t ETEINT = 0b00;
volatile uint8_t minuterieCommencee = 0;
volatile uint8_t bouton_poussoir = 0;
volatile uint8_t compteur = 0;

//enumeration des etats
enum ETAT
{
    init,
    timer_commence,
    vert0,
    rien,
    rouge0,
    vert1
};

//declaration de la variable etat
volatile ETAT etat;

//routine d'interruption qui incremente le compteur chaque 10ms
ISR(TIMER1_COMPA_vect)
{
    
    minuterieCommencee = 1;
    compteur++;
}

//fonction qui part la minuterie
void partirMinuterie(uint16_t duree)
{
    // mode CTC du timer 1 avec horloge divisée par 64
    // interruption après la durée spécifiée
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
}

//initialisation de ISR du bouton_poussoir
void initialisation(void)
{
    cli();

    DDRD = ENTREE;
    DDRB = SORTIE;
    TIMSK1 |= (1 << OCIE1A);
    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC00);

    sei();
}

//routine du bouton_poussoir

ISR(INT0_vect)
{
    _delay_ms(30);
    if (!(PIND & 0x04)){
    
        bouton_poussoir = 1;
    }
    else
    {
        
        bouton_poussoir = 0;
    }

    EIFR |= (1 << INTF0);
}


//procedure main()
int main()
{
    //on initialise nos routines d'interruptions
    initialisation();
    //on declare notre etat initial
    etat = init;
    for (;;)
    {
        switch (etat)
        {
        case init:
            PORTB = ETEINT;
            compteur = 0;
            minuterieCommencee = 0;
            
            if (bouton_poussoir == 1) {// quand le bouton_poussoir est appuye le timer commence
             
                etat = timer_commence;
            }
            break;

        case timer_commence:
            if (minuterieCommencee == 0)
            {
                partirMinuterie(12499); //delai de 10ms avec un prescaler a 64
                minuterieCommencee = 1;
            }
            if (bouton_poussoir == 0 || compteur >= 120) //si mon bouton poussoir est relache ou bien que le compteur atteint 120 on arrete le timer et //on va vers le prochain etat
            {
               PORTB = ROUGE;
               
                TIMSK1 = 0;
                etat = vert0;
            }
            break;

        case vert0:
            for (int i = 0; i < 5; i++) //on fait clignoter notre del en vert durant 1/2 seconde
            {
                PORTB = VERT;
                _delay_ms(50);
                PORTB = ETEINT;
                _delay_ms(50);
            }
            etat = rien; //on passe au prochain etat
            break;

        case rien:
            PORTB = ETEINT;
            _delay_ms(2000); //on reste eteint deux secondes
            etat = rouge0;
            break;

        case rouge0:
        
            for (uint8_t i = 0 ; i < compteur / 2; i++) //on fait clignoter le rouge compteur/2 fois, au rythme 2x par secondes
            {
                PORTB = ROUGE;
                _delay_ms(250);
                PORTB = ETEINT;
                _delay_ms(250);
            }
            etat = vert1;
            break;

        case vert1:
            PORTB = VERT; //on laisse notre del en vert pendant une seconde avant d'aller a l'etat initial
            _delay_ms(1000);
            etat = init;
            break;
        }
    }
}
