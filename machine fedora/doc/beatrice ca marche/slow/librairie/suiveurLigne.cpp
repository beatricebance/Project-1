#include "suiveurLigne.h"
#include <util/delay.h>
#include "roues.h"


void SuiveurLigne :: suiveurLigneBoucle_droit(){

        // instance de la classe Roues
        Roues R;

        // direction des ports
        DDRA = 0x00;
        DDRD = 0xFF;
       

            if(CAP_1 && CAP_2 && CAP_3){

                    _delay_ms(10);
                    while (CAP_1 && CAP_2 && CAP_3){
                    R.ajustementRoues(38,38,AVANT);
                    }
                    compteur ++; 
            }

            else if(CAP_3){
                    _delay_ms(10);
                    if(CAP_3){
                    R.ajustementRoues(38,38,AVANT);
                    }
            }
            else if(CAP_1){
                    _delay_ms(10);
                    if(CAP_1){
                    R.ajustementRoues(40,30,AVANT);
                    }
            }
            else if(CAP_2){
                    _delay_ms(10);
                    if(CAP_2){
                    R.ajustementRoues(50,35,AVANT);
                    }
            }
            else if(CAP_4){
                    _delay_ms(10);
                    if(CAP_4){
                    R.ajustementRoues(35,50,AVANT);
                    }
            }
            else if(CAP_5){
                    _delay_ms(10);
                    if(CAP_5){
                    R.ajustementRoues(30,40,AVANT);
                    }
            }
            
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    R.ajustementRoues(0,0,AVANT);
            }
    

}