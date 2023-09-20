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

#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupe par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupe par l'afficheur

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
#include <math.h> 
#include "DEL.h"
#include "communication.h"
#include "Bouton.h"
#include "roues.h"

// Declarations des variables globales 
bool debut = true;
volatile uint8_t bouton_poussoir = 0;
volatile uint8_t bouton_interrupt = 0;
bool doit_choisir =true;
volatile uint8_t compteur = 0;

//volatile uint8_t compteurDebutFinBoucle =0; LATER MAYBE JE VAIS LE USE POUR ARRETER DANS LE PARCOURS DES DEUX BOUCLES


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

        // Creation de l'objet LCM
        LCM disp(&DEMO_DDR, &DEMO_PORT);

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
                    disp.clear();
                    disp << compteur;    
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

   // Creation de l'objet LCM
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
						
                                  // PLACE POUR LE CODE COULOIR

                 // disp.clear();
                 // disp.write("FIN ",5);

                // INCREMENTE ETACOURANT POUR QU'IL CONTINUE LE PARCOURS SUR L'ETAT SUIVANT
                 // EtaCourant ++;

		
            break;

            case MUR :
                     
 
                                   // PLACE POUR LE CODE MUR

                // disp.clear();
                 // disp.write("FIN ",5);

                  // INCREMENTE ETACOURANT POUR QU'IL CONTINUE LE PARCOURS SUR L'ETAT SUIVANT
                 // EtaCourant ++;
                   
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
                                                _delay_ms(400);
                                                debut = false;
                                                compteur ++;
                                                
                                        }
        
                        }
                        else  if (compteur >3 && compteur <7){
                                

                        if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) )
                        
                        {

                               // _delay_ms(10);

                                while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                                
                                R.ajustementRoues(40,0,AVANT);
                                _delay_ms(100);

                                }
                
                        }

                                suiveurLigneBoucle_droit(); 
         
                        }

                        else if (compteur >=7 && compteur <=12) {
        

                                         if(CAP_1 && CAP_2 && CAP_3){

                                                  R.ajustementRoues(40,0,AVANT);
                                                  _delay_ms(830);
                                        
                                                        while (CAP_1 && CAP_2 && CAP_3){
                                                                R.ajustementRoues(40,0,AVANT);
                                                                        _delay_ms(400);
                                                                }
                                                        

                                                
                                                compteur ++ ;
                                                disp.clear();
                                                disp << compteur;  
                                              //  _delay_ms(10); 
                                        }


                                        else if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){

                                        _delay_ms(10);
                                                while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                                                        
                                                        R.ajustementRoues(40,0,AVANT);
                                                        _delay_ms(830);

                                                        }
                
                                        }
                                
                                        //  else  {
                                                        suiveurLigneBoucle_droit(); 
                                                // }

                        }

                        else if (compteur >=13 && compteur <=14){
                        suiveurLigneBoucle_droit();

                        }

                        // else if (compteur == 14){
                                
                        //         disp << compteur; 

                        //         // R.ajustementRoues(0,0,AVANT);
                        //         // _delay_ms(400);  
                        //          suiveurLigneBoucle_droit();   
                        // }
                        else if (compteur == 15){

                                  R.ajustementRoues(0,0,AVANT);
                                 _delay_ms(400);  

                        }

                }   

                  

            break;

            case COUPURES:

                    
                                                    // ICI LE CODE POUR LES COUPURES
   

                    //disp.clear();
                    //disp.write(" FIN ",5);


                    // INCREMENTE ETACOURANT POUR QU'IL CONTINUE LE PARCOURS SUR L'ETAT SUIVANT
                 // EtaCourant ++;

            break;

            }

        }

        bouton_interrupt = 0;
        doit_choisir = true;
        EIMSK |= (1 << INT1);   

  } 

 
  return 0; 
}


