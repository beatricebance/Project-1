#include "suiveurLigne.h"

void SuiveurLigne::suiveurLigne (){       
    DDRA = 0x00;
    DDRD=0xFF;
    Roues moteur; // on declare un objet de type moteur
            if(US(3)){
                    _delay_ms(10);
                    if(US(3)){
                    moteur.ajustementRoues(60,60,AVANT);
                    }
            }
            else if(US(1)){
                    _delay_ms(10);
                    if(US(1)){
                    moteur.ajustementRoues(60,35,AVANT);
                    }
            }
            else if(US(2)){
                    _delay_ms(10);
                    if(US(2)){
                    moteur.ajustementRoues(60,45,AVANT);
                    }
            }
            else if(US(4)){
                    _delay_ms(10);
                    if(US(4)){
                    moteur.ajustementRoues(45,60,AVANT);
                    }
            }
            else if(US(5)){
                    _delay_ms(10);
                    if(US(5)){
                    moteur.ajustementRoues(40,60,AVANT);
                    }
            }
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    moteur.ajustementRoues(0,0,AVANT);
            }
    }
