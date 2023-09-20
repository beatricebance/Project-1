#include "coupure.h"
#include "sonorite.h"



void Coupure::Les_coupures(){
        SuiveurLigne suiveur;
        Roues R;
        SONORITE s;
        //boostDepart();
        // R.ajustementR(35,35); 
        //_delay_ms(5);


   //while (fairecoupure) {
        //ligne t-v
        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        
        suiveur.suiveurLigneCoupure();
        }
        while (!US(1) && !US(2) && !US(3) && !US(4) && !US(5))
        {
             s.son_aigu();
        R.ajustementRoues(0,40,DROITE);
        _delay_ms(25);    
        }
        
        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);


        //ligne w-y
        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        s.arreterSonorite();
        suiveur.suiveurLigneCoupure();
        }
        while (!US(1) && !US(2) && !US(3) && !US(4) && !US(5))
        {
             s.son_grave();
        R.ajustementRoues(40,0,GAUCHE);
        _delay_ms(25);    
        }
       
        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);

        
        
         //ligne z-2
        while (US(1)||US(2)||US(3)||US(4)||US(5)){

         s.arreterSonorite();
        suiveur.suiveurLigneCoupure();
        }

        while (!US(1) && !US(2) && !US(3) && !US(4) && !US(5))
        {
              s.son_aigu();
        R.ajustementRoues(0,40,DROITE);
        _delay_ms(25);    
        }

        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);

       
 

        //ligne t-v
        while (US(1)||US(2)||US(3)||US(4)||US(5)){
              s.arreterSonorite();
        
        suiveur.suiveurLigneCoupure();
        }
        while (!US(1) && !US(2) && !US(3) && !US(4) && !US(5))
        {
             s.son_grave();
        R.ajustementRoues(40,0,GAUCHE);
        _delay_ms(25);    
        }
        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);


          
        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        s.arreterSonorite();
          suiveur.suiveurLigneCoupure();
        }
        R.ajustementRoues(0,0,AVANT);
  
  
}