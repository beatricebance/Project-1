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


// Inclusion des librairies 
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
#include "boucles.h"
#include "couloir.h"
#include "coupure.h"
#include "transition.h"
#include "distance.h"
// Declarations des variables globales 
bool doit_choisir =true;

// Instanciation de la classe bouton
BOUTON b;

//routine du bouton_poussoir sur le breadboard
ISR(INT1_vect)
{

    _delay_ms(30);
    if (!(PIND & 0x08)){
    
       b.bouton_poussoir = 1;
    }
    else
    {
        
       b.bouton_poussoir = 0;
    }

    EIFR |= (1 << INTF0);
}


//routine du bouton poussoir interrupt
ISR(INT0_vect)
{
    _delay_ms(30);
  
    if (!(PIND & 0x04)){
    
       b.bouton_interrupt = 1;
        
    }
    else
    {
        
       b.bouton_interrupt = 0;
    }

    EIFR |= (1 << INTF0);
}

//  Enumeration des differents etats
enum ETAT{COULOIR,MUR,LES_DEUX_BOUCLES,COUPURES} ;	


int main()
{ 

    // initialisation des ports  
    DDRA = 0x00; 
    DDRC =0xff;


    // instanciation des classes
    DEL del;
    COMMUNICATION com;
    Roues R;
    Boucles boucles;
    Couloir couloir;
    Coupure coupure;
    Transition transition;
    Distance dist;



    //on initialise nos registres pour les interruptions
   b.initialisation();
   b.initialisation_2();


    // Initialisation de l'etat : on est sur le couloir au debut
    enum ETAT EtatCourant = COULOIR ;

   // Creation de l'objet LCM
   LCM disp(&DEMO_DDR, &DEMO_PORT);


///////////////////////////////////////////////////////////////////////////////CHOIX DE LA SECTION DE DEPART////////////////////////////////////////////////////////////////////////////   

while (doit_choisir)   // tant que l'on a pas encore choisir la section de depart 
  {
	  
        switch (EtatCourant) {

            case COULOIR :
						
  
                        disp.write("COULOIR ",3);
                        if (b.bouton_poussoir == 1){     
			            EtatCourant=MUR; 
                        disp.clear();
			            while(b.bouton_poussoir == 1){};   
                        } 
		
            break;

            case MUR :
                        
                        disp.write("MUR ",5);
                        if (b.bouton_poussoir == 1){
                        EtatCourant=LES_DEUX_BOUCLES; 
                        disp.clear();
			            while(b.bouton_poussoir == 1){};
			}
            break;
                      
            case LES_DEUX_BOUCLES:

                        
                        disp.write("LES_DEUX_BOUCLES",0);
                        if (b.bouton_poussoir == 1){ 
                        EtatCourant=COUPURES;  
                        disp.clear();
                        while(b.bouton_poussoir == 1){};   
                      } 

            break;

            case COUPURES:

                    
                    disp.write("COUPURES ",3);
                    if (b.bouton_poussoir == 1){
                    EtatCourant=COULOIR;
                    disp.clear();
		            while(b.bouton_poussoir == 1){};        
              }

            break;

        }


/////////////////////////////////////////////////////////////////////////////FIN DU CHOIX DE LA SECTION DE DEPART //////////////////////////////////////////////////////////////////////////



        ///////////////////////////////////////////////////////PARTIE 2 DEBUT DU PARCOURS SELON LA SECTION ///////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// LE ROBOT DOIT CONTINUER SUR LA SECTION QUI SUIT PAS ENCORE TERMINER CA////////////////////////////////////////////
        /////////////////////////////////////////////////////STOPER USAGE DU BOUTON POUSSOIR PENDANT CETTE PARTIE : REUSSI //////////////////////////////////////////////////////

        while (b.bouton_interrupt == 1) // si le bouton interrupt a ete appyer commence la section 
        {
            doit_choisir =false;
            EIMSK |= (0 << INT1);  
            EICRA |= (0 << ISC00);

            switch (EtatCourant)
            {

            case COULOIR :

                    disp.clear();
                    disp.write("COULOIR ",3);	

                				
                couloir.Le_couloir();

                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {

                    b.bouton_interrupt = 0;
                    disp.clear();
                    disp.write("FIN ",5);	

                }
                else {
                    EtatCourant = MUR;
                    b.bouton_interrupt = 1;
                }



            break;

            case MUR :
                
                   disp.clear();	
                   disp.write("MUR ",5);
                
                 dist.sonar();
              
               
                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {

                     b.bouton_interrupt = 0;
                    disp.clear();
                    disp.write("FIN ",5);	

                }
                else {
                    EtatCourant = LES_DEUX_BOUCLES;
                    b.bouton_interrupt = 1;
                }
                   
            break;
                      
            case LES_DEUX_BOUCLES:

                  disp.clear();	
                  disp.write("LES_DEUX_BOUCLES",0);
                 
                boucles.Les_Deux_Boucles();
                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {
  
                     b.bouton_interrupt = 0;
                    disp.clear();
                    disp.write("FIN ",5);	

                }
                else {
                    EtatCourant = COUPURES;
                    b.bouton_interrupt = 1;
                }

                  

            break;

            case COUPURES:

                 disp.clear(); 
                 disp.write("COUPURES ",3);  
                coupure.Les_coupures();
                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {

                     b.bouton_interrupt = 0;
                    disp.clear();
                    disp.write("FIN ",5);	

                }
                else {
                    EtatCourant = COULOIR;
                    b.bouton_interrupt = 1;
                }

            break;

            }

        }

      // b.bouton_interrupt = 0;
       // doit_choisir = true;
      //  EIMSK |= (1 << INT1);   

  } 

 
  return 0; 
}


