/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe DEL
  *
 */


#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h> 
#include "DEL.h"


void DEL::Del()
{
    DDRA |= _BV(6) | _BV(7); // Broches 6 et 7 du PORTD en sortie
    PORTA &= ~_BV(6) & ~_BV(7); //led off
}
void DEL::couleurAmbre()
{
    couleurVerte();
    _delay_ms(10);
    couleurRouge();
    _delay_ms(10);
    
}
    
    
void DEL::couleurVerte()
{      
    //PORTD = 0x01;
    PORTA &= ~_BV(6);
    PORTA |= _BV(7);   
}
    
    
void DEL::couleurRouge()
{
        
    PORTA &= ~_BV(7);
    PORTA |= _BV(6); 

}
    
    
void DEL::delEteinte()
{
    
    
    PORTA &= ~_BV(6) & ~_BV(7);//ceci definit la DEL eteinte
}


