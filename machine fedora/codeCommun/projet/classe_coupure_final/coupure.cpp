#include "coupure.h"



void Coupure::coupure(){
        SuiveurLigne suiveur;
        Roues roues;
        //boostDepart();
        // roues.ajustementRoues(35,35,AVANT); 
        //_delay_ms(5);


        //ligne t-v
        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        
        suiveur.suiveurLigne();
        }
        while (US(3)==0)
        {
        roues.ajustementRoues(0,40,DROITE);
        _delay_ms(25);    
        }
        //roues.ajustementRoues(0,0,AVANT);
        //_delay_ms(300);
         //boostDepart;
        roues.ajustementRoues(25,25,AVANT); 
        _delay_ms(25);


        //ligne w-y
        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        
        suiveur.suiveurLigne();
        }
        while (US(3)==0)
        {
        roues.ajustementRoues(40,0,GAUCHE);
        _delay_ms(25);    
        }
        roues.ajustementRoues(25,25,AVANT); 
        _delay_ms(25);
         //boostDepart;
        //roues.ajustementRoues(60,60,AVANT); 
        //_delay_ms(50);
        


        
         //ligne z-2
        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        
        suiveur.suiveurLigne();
        }

        while (US(3)==0)
        {
        roues.ajustementRoues(0,40,DROITE);
        _delay_ms(25);    
        }
        //roues.ajustementRoues(0,0,AVANT);
        //_delay_ms(300);
         //boostDepart;

        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        
        suiveur.suiveurLigne();
        }

        while (US(3)==0){

        roues.ajustementRoues(0,40,DROITE);
        _delay_ms(25);  
        //_delay_ms(25);
        }
        roues.ajustementRoues(25,25,AVANT); 
        _delay_ms(25);


        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        
        suiveur.suiveurLigne();
        }
        roues.ajustementRoues(25,25,AVANT); 
        _delay_ms(25);

        while (US(3)==0){

        roues.ajustementRoues(30,0,GAUCHE);
        _delay_ms(25);  
        //_delay_ms(25);
        }
        roues.ajustementRoues(25,25,AVANT); 
        _delay_ms(25);

        while (US(1)||US(2)||US(3)||US(4)||US(5)){
        
        suiveur.suiveurLigne();
        }
        roues.ajustementRoues(0,0,AVANT);
}