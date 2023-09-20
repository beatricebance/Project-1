/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  Main du projet
  *
 */

#define F_CPU 8000000UL

#define CAP_1  PINA & 1<<0
#define CAP_2  PINA & 1<<1
#define CAP_3  PINA & 1<<2
#define CAP_4  PINA & 1<<3
#define CAP_5  PINA & 1<<4

#define US(x) (PINA & (1 << ((x)-1)))

#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupe par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupe par l'afficheur

#include <stdlib.h>
#include <avr/io.h>
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#include <math.h> 
#include "DEL.h"
#include "communication.h"
#include "moteur.h"
#include "Bouton.h"
#include "UART.h"
#include "roues.h"

// Declarations des variables globales 
bool debut = true;
volatile uint8_t bouton_poussoir = 0;
volatile uint8_t bouton_interrupt = 0;
bool doit_choisir =true;
volatile uint8_t compteur = 0;
volatile uint8_t compteurDebutFinBoucle =0;


//initialisation de ISR du bouton_poussoir
void initialisation(void)
{
    cli();
    DDRD = 0x00;
    DDRB = 0xff;
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC10);
    sei();
}


//initialisation de ISR du bouton interrupt
void initialisation_2(void)
{
    cli();
    DDRD = 0x00;
    DDRB = 0xff;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

//routine du bouton_poussoir
ISR(INT1_vect)
{

    _delay_ms(30);
    if (!(PIND & 0x08)){
    
        bouton_poussoir = 1;
    }
    else
    {
        
        bouton_poussoir = 0;
    }

    EIFR |= (1 << INTF0);
}


//routine du bouton interrupt
ISR(INT0_vect)
{
    _delay_ms(30);
  
    if (!(PIND & 0x04)){
    
        bouton_interrupt = 1;
        
    }
    else
    {
        
        bouton_interrupt = 0;
    }

    EIFR |= (1 << INTF0);
}

//  Enumeration des differents etats
enum ETAT{COULOIR,MUR,LES_DEUX_BOUCLES,COUPURES} ;	


// suiveur de ligne pour les deux boucles detecteurs normal 
void suiveurLigneBoucle_droit(){
// Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);

       DDRA = 0x00;
       DDRD = 0xFF;
       Roues R;


            if(CAP_1 && CAP_2 && CAP_3){

                    _delay_ms(10);
                    while (CAP_1 && CAP_2 && CAP_3){
                    R.ajustementRoues(40,40,AVANT);
                    }
                    compteur ++;
                    disp.clear();
                    disp << compteur;    
            }



            else if(CAP_3){
                    _delay_ms(10);
                    if(US(3)){
                    R.ajustementRoues(40,40,AVANT);
                    }
            }
            else if(CAP_1){
                    _delay_ms(10);
                    if(US(1)){
                    R.ajustementRoues(50,25,AVANT);
                    }
            }
            else if(CAP_2){
                    _delay_ms(10);
                    if(US(2)){
                    R.ajustementRoues(50,35,AVANT);
                    }
            }
            else if(CAP_4){
                    _delay_ms(10);
                    if(US(4)){
                    R.ajustementRoues(35,50,AVANT);
                    }
            }
            else if(CAP_5){
                    _delay_ms(10);
                    if(US(5)){
                    R.ajustementRoues(30,50,AVANT);
                    }
            }
            
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    R.ajustementRoues(0,0,AVANT);
            }
    

}


// suiveur de ligne pour les deux boucles detecteurs normal 
void suiveurLigneBoucle_tourner(){


       DDRA = 0x00;
       DDRD = 0xFF;
       Roues R;

// Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);

            if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){

                    _delay_ms(10);
           while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                     
                      R.ajustementRoues(40,0,AVANT);
                      _delay_ms(400);

                    }
                //     compteur ++;
                //     disp.clear();
                //     disp << compteur;    
            }


            if(CAP_1 && CAP_2 && CAP_3){

                    _delay_ms(10);
                    while (CAP_1 && CAP_2 && CAP_3){
                    
                    }
                    compteur ++;
                    disp.clear();
                    disp << compteur;    
                    
            }



           else if(CAP_3){
                    _delay_ms(10);
                    if(US(3)){
                    R.ajustementRoues(40,40,AVANT);
                    }
            }
            else if(CAP_1){
                    _delay_ms(10);
                    if(US(1)){
                    R.ajustementRoues(50,25,AVANT);
                    }
            }
            else if(CAP_2){
                    _delay_ms(10);
                    if(US(2)){
                    R.ajustementRoues(50,35,AVANT);
                    }
            }
            else if(CAP_4){
                    _delay_ms(10);
                    if(US(4)){
                    R.ajustementRoues(35,50,AVANT);
                    }
            }
            else if(CAP_5){
                    _delay_ms(10);
                    if(US(5)){
                    R.ajustementRoues(30,50,AVANT);
                    }
            }
            
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    R.ajustementRoues(0,0,AVANT);
            }
    

}

// suiveur de ligne pour la petite boucles
void suiveurLigneBoucle_tourner_Petite(){


       DDRA = 0x00;
       DDRD = 0xFF;
       Roues R;

// Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);


        if(CAP_1 && CAP_2 && CAP_3){

                     R.ajustementRoues(0,0,AVANT);
                     _delay_ms(100);
         
         while (CAP_1 && CAP_2 && CAP_3){
                    R.ajustementRoues(40,0,AVANT);
                            _delay_ms(500);
                    }
                            

                    
                    compteur ++;
                    disp.clear();
                    disp << compteur;    
            }

           else if(CAP_3){
                    _delay_ms(10);
                    if(US(3)){
                    R.ajustementRoues(40,40,AVANT);
                    }
            }
            else if(CAP_1){
                    _delay_ms(10);
                    if(US(1)){
                    R.ajustementRoues(50,25,AVANT);
                    }
            }
            else if(CAP_2){
                    _delay_ms(10);
                    if(US(2)){
                    R.ajustementRoues(50,35,AVANT);
                    }
            }
            else if(CAP_4){
                    _delay_ms(10);
                    if(US(4)){
                    R.ajustementRoues(35,50,AVANT);
                    }
            }
            else if(CAP_5){
                    _delay_ms(10);
                    if(US(5)){
                    R.ajustementRoues(30,50,AVANT);
                    }
            }
        //    else if((CAP_1) && (CAP_2) && (CAP_3) && (CAP_4) && (CAP_5) ){

        //             R.ajustementRoues(0,0,AVANT);
        //    }

           else if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){

                    _delay_ms(10);
           while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                     
                      R.ajustementRoues(40,0,AVANT);
                      _delay_ms(830);

                    }
                //     compteur ++;
                //     disp.clear();
                //     disp << compteur;    
            }
            
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    R.ajustementRoues(0,0,AVANT);
            }
    

}

int main()
{ 

    // initialisation des ports  
    DDRA = 0x00; 
    DDRC =0xff;


    // instanciation des classes
    DEL del;
    COMMUNICATION com;
    Roues R;



    //on initialise nos routines d'interruptions
    initialisation();
    initialisation_2();


    // Initialisation de l'etat : on est sur le 
    enum ETAT EtatCourant = COULOIR ;

	// Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);


   

while (doit_choisir) 
  {
	  
        switch (EtatCourant) {

            case COULOIR :
						
  
                        disp.write("COULOIR ",3);
                        if (bouton_poussoir == 1){     
						 EtatCourant=MUR; 
                         disp.clear();
						while(bouton_poussoir == 1){};   
                        } 
		
            break;

            case MUR :
                        
                        disp.write("MUR ",5);
                        if (bouton_poussoir == 1){
                        EtatCourant=LES_DEUX_BOUCLES; 
                        disp.clear();
						while(bouton_poussoir == 1){};
					  }
            break;
                      
            case LES_DEUX_BOUCLES:

                        
                        disp.write("LES_DEUX_BOUCLES",0);
                        if (bouton_poussoir == 1){ 
                        EtatCourant=COUPURES;  
                        disp.clear();
                        while(bouton_poussoir == 1){};   
                      } 

            break;

            case COUPURES:

                    
                    disp.write("COUPURES ",3);
                    if (bouton_poussoir == 1){
                    EtatCourant=COULOIR;
                    disp.clear();
		while(bouton_poussoir == 1){};        
              }

            break;

        }

        if (bouton_interrupt == 1)
        {
            doit_choisir =false;
            EIMSK |= (0 << INT1);  
            EICRA |= (0 << ISC00);

            switch (EtatCourant)
            {

            case COULOIR :
						


                  disp.clear();
                  disp.write("FIN ",5);
		
            break;

            case MUR :
                     
 
                 disp.clear();
                  disp.write("FIN ",5);
                   
            break;
                      
            case LES_DEUX_BOUCLES:

                     for (;;){

                         
                     if(compteur <= 2){
                        suiveurLigneBoucle_droit();                       
                     }

                     else if(compteur == 3){

                             R.ajustementRoues(0,0,AVANT);
                             _delay_ms(500);
                             
                        if(debut){ 
                
                                          disp.clear();
                                          disp << compteur;

                                        R.ajustementRoues(50,0,AVANT);
                                        _delay_ms(1600);
                                        debut = false;
                                        compteur ++;
                                        
                                }
   
                      }
                      else  if (compteur >3 && compteur <7){
                              
                        //       disp.clear();
                        //       disp << compteur; 
                        //       suiveurLigneBoucle_tourner();  
                        




                     if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) )
                     
                     {

                        _delay_ms(10);

                        while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                        
                        R.ajustementRoues(40,0,AVANT);
                        _delay_ms(400);

                         }
             
                    }

                        suiveurLigneBoucle_droit(); 




                                 
                             
                      }

                      else if (compteur >=7 && compteur <=12)
                      {
                        //    disp.clear();
                        //   disp << compteur; 
                        //   // disp.write("petite",0);
                        //    suiveurLigneBoucle_tourner_Petite();    





                                        if(CAP_1 && CAP_2 && CAP_3){

                                        R.ajustementRoues(0,0,AVANT);
                                        _delay_ms(100);
                                
                                                while (CAP_1 && CAP_2 && CAP_3){
                                                        R.ajustementRoues(40,0,AVANT);
                                                                _delay_ms(500);
                                                        }
                                                

                                        
                                        compteur ++;
                                        disp.clear();
                                        disp << compteur;    
                                }




                                else if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){

                                _delay_ms(10);
                                        while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                                                
                                                R.ajustementRoues(40,0,AVANT);
                                                _delay_ms(830);

                                                }
                                //     compteur ++;
                                //     disp.clear();
                                //     disp << compteur;    
                                }
                        
                                        else {
                                                suiveurLigneBoucle_droit(); 
                                        }

                      }

                    else if (compteur >=13 && compteur <15 ){
                     suiveurLigneBoucle_droit();

                //       if(CAP_1 && CAP_2 && CAP_3){
                
                //                 while (CAP_1 && CAP_2 && CAP_3){
                //                         R.ajustementRoues(40,40,AVANT);
                //                                // _delay_ms(500);
                //                         }
                                

                        
                //         compteur ++;
                //         disp.clear();
                //         disp << compteur; 
                //         disp.clear();   
                //     }
            }

                      else if (compteur == 15){
                          
                          
                          disp << compteur; 
                        // R.ajustementRoues(40,40,AVANT);
                        //  _delay_ms (300);
                        R.ajustementRoues(0,0,AVANT);
                        _delay_ms(1000);
                       // suiveurLigneBoucle_droit();

                       
                      
                     
                           
                      }

                     }   
                                        

            break;

            case COUPURES:

                    
                                                    // ICI LE CODE POUR LES COUPURES
   

                    disp.clear();
                    disp.write(" FIN ",5);

            break;

            }

        }

        bouton_interrupt = 0;
        doit_choisir = true;
        EIMSK |= (1 << INT1);   

  } 

 
  return 0; 
}


