#include "suiveurLigne.h"
#include "DEL.h"


void SuiveurLigne :: suiveurLigneBoucle_droit(){

        // direction des ports
        DDRA = 0xC0;  // port A en entree
        DDRD = 0xFF;  // port D en sortie


        // instance de la classe Roues
        Roues R;
       
       

        // direction des ports
        DDRA = 0xC0;
        DDRD = 0xFF;
       

          if(CAP_1 && CAP_2 && CAP_3){
                  
                 
                    _delay_ms(10);
                    while (CAP_1 && CAP_2 && CAP_3){
                    ajustementRoues(38,38,AVANT);
                    }
                    compteur ++;
                    
            }

            else if(CAP_3){
                    _delay_ms(10);
                    if(CAP_3){
                    ajustementRoues(38,38,AVANT);
                    }
            }
            else if(CAP_1){
                    _delay_ms(10);
                    if(CAP_1){
                    ajustementRoues(50,25,AVANT);
                    }
            }
            else if(CAP_2){
                    _delay_ms(10);
                    if(CAP_2){
                    ajustementRoues(50,35,AVANT);
                    }
            }
            else if(CAP_4){
                    _delay_ms(10);
                    if(CAP_4){
                    ajustementRoues(35,50,AVANT);
                    }
            }
            else if(CAP_5){
                    _delay_ms(10);
                    if(CAP_5){
                    ajustementRoues(30,50,AVANT);
                    }
            }
            
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    ajustementRoues(0,0,AVANT);
            }




}


void SuiveurLigne::suiveurLigne(){       


        // direction des ports
        DDRA = 0xC0;  // port A en entree
        DDRD = 0xFF;  // port D en sortie

        DEL del;
      

       

        //    if((CAP_1 && CAP_2 && CAP_3) || (CAP_1 && CAP_2 && CAP_3 && CAP_4) || (CAP_1 && CAP_2 && CAP_3 && CAP_4 && CAP_5) ){

        //             _delay_ms(10);
        //             while (!(CAP_3) ){
        //             ajustementRoues(0,40,AVANT);
        
        //             }
        //             compteur ++; 
       
        //     }

        // else if (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                                  
                                                            
        //         ajustementRoues(0,40,AVANT);
        //         _delay_ms(500);


        //                         }

            if(CAP_3){
                    // uart.transmissionUART(3);
                    _delay_ms(10);
                    if(CAP_3){
                    ajustementRoues(38,38,AVANT);
                    }
            }
            else if(CAP_1){
                    // uart.transmissionUART(1);
                    _delay_ms(10);
                    if(CAP_1){
                    ajustementRoues(40,30,AVANT);
                    }
            }
            else if(CAP_2){
                    // uart.transmissionUART(2);
                    _delay_ms(10);
                    if(CAP_2){
                    ajustementRoues(50,35,AVANT);
                    }
            }
            else if(CAP_4){
                     //uart.transmissionUART(4);
                    _delay_ms(10);
                    if(CAP_4){ 
                    ajustementRoues(35,50,AVANT);
                    }
            }
            else if(CAP_5){
                    // uart.transmissionUART(5);
                    _delay_ms(10);
                    if(CAP_5){
                    ajustementRoues(30,40,AVANT);
                    }
            }

             else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    ajustementRoues(0,0,AVANT);          }
}        
     

    void SuiveurLigne::suiveurLigneCoupure (){       
    DDRA = 0xC0;
    DDRD=0xFF;
  
            if(US(3)){
                    _delay_ms(10);
                    if(US(3)){
                    ajustementRoues(55,55,AVANT);                    }
            }
            else if(US(1)){
                    _delay_ms(10);
                    if(US(1)){
                    ajustementRoues(45,15,GAUCHE);
                    }
            }
            else if(US(2)){
                    _delay_ms(10);
                    if(US(2)){
                    ajustementRoues(45,25,GAUCHE);
                    }
            }
            else if(US(4)){
                    _delay_ms(10);
                    if(US(4)){
                    ajustementRoues(25,45,DROITE);
                    }
            }
            else if(US(5)){
                    _delay_ms(10);
                    if(US(5)){
                    ajustementRoues(15,45,DROITE);
                    }
            }
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    ajustementRoues(0,0,AVANT);          }
    }

 void SuiveurLigne::suiveurLigneCouloire (){       
    DDRA = 0xC0;
    DDRD=0xFF;
  
            if(US(3)){
                    _delay_ms(10);
                    if(US(3)){
                    ajustementRoues(55,55,AVANT);                    }
            }
            else if(US(1)){
                    _delay_ms(10);
                    if(US(1)){
                    ajustementRoues(45,15,GAUCHE);
                    }
            }
            else if(US(2)){
                    _delay_ms(10);
                    if(US(2)){
                    ajustementRoues(45,25,GAUCHE);
                    }
            }
            else if(US(4)){
                    _delay_ms(10);
                    if(US(4)){
                    ajustementRoues(25,45,DROITE);
                    }
            }
            else if(US(5)){
                    _delay_ms(10);
                    if(US(5)){
                    ajustementRoues(15,45,DROITE);
                    }
            }
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    ajustementRoues(0,0,AVANT);          }
    }