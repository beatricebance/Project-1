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

#define DEMO_DDR	DDRC 
#define DEMO_PORT	PORTC 


// Inclusion des librairies 
// #include <stdlib.h>
// #include <avr/io.h>
// #include <util/delay.h>
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
// #include <math.h> 
// #include "DEL.h"
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
    DDRA = 0xC0; 
    DDRC =0xff;

    // instanciation des classes
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


////////////////////CHOIX DE LA SECTION DE DEPART////////////////////   

while (doit_choisir)  
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

                        
                        disp.write("LES DEUX BOUCLES",0);
                        if (b.bouton_poussoir == 1){ 
                        EtatCourant=COUPURES;  
                        disp.clear();
                        while(b.bouton_poussoir == 1){};   
                      } 

            break;

            case COUPURES:

                    
                    disp.write("COUPURES ",3);                    if (b.bouton_poussoir == 1){
                    EtatCourant=COULOIR;
                    disp.clear();
		            while(b.bouton_poussoir == 1){};        
              }

            break;

        }


///////////////FIN DU CHOIX DE LA SECTION DE DEPART //////////////////////////



//////////////DEBUT DU PARCOURS SELON LA SECTION /////////////////////////////

        while (b.bouton_interrupt == 1) // si le bouton interrupt a ete appuyer 
        {
            _delay_ms(2000);
            doit_choisir =false; // fin du choix de la section
            EIMSK |= (0 << INT1);   // desactive les interruptions en INT1
            EICRA |= (0 << ISC00);  // met a 0 le registre de changement logique

            switch (EtatCourant)
            {

            case COULOIR :

                disp ="COULOIR";					
                couloir.Le_couloir();

                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {
                   
                 transition. Redressement(); 
                  b.bouton_interrupt = 0;
                   // R.ajustementRoues(40,0,AVANT);
                   //  _delay_ms(600);
                   // R.ajustementRoues(0,0,AVANT);
                    disp ="FIN ";	

                }
                else {
                    EtatCourant = MUR;
                    b.bouton_interrupt = 1;
                }



            break;

            case MUR :
                
                disp = "MUR";  
                dist.sonar(); 
                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {
                     
                     transition. Redressement();
                     b.bouton_interrupt = 0;
                    //  R.ajustementRoues(40,0,AVANT);
                    //  _delay_ms(600);
                    //  R.ajustementRoues(0,0,AVANT);
                     disp ="FIN ";	

                }
                else {
                    EtatCourant = LES_DEUX_BOUCLES;
                    b.bouton_interrupt = 1;
                }
                   
            break;
                      
            case LES_DEUX_BOUCLES:

                disp ="LES DEUX BOUCLES";  
                boucles.Les_Deux_Boucles();
                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {
                    transition. Redressement();
                    // R.ajustementRoues(40,0,AVANT);
                    //  _delay_ms(600);
                    // R.ajustementRoues(0,0,AVANT);
                    b.bouton_interrupt = 0;
                    disp ="FIN ";	

                }
                else {
                    EtatCourant = COUPURES;
                    b.bouton_interrupt = 1;
                }

                  

            break;

            case COUPURES:

                disp ="COUPURES "; 
              //  _delay_ms(2000); // delai de deux(2) secondes avant le depart	
                coupure.Les_coupures();
                transition.TransitionSection();
                if (transition.sectionParcouru == 4) {
                    transition. Redressement();
                     b.bouton_interrupt = 0;
                    //  R.ajustementRoues(40,0,AVANT);
                    //  _delay_ms(600);
                    //  R.ajustementRoues(0,0,AVANT);
                     disp ="FIN ";	

                }
                else {
                    EtatCourant = COULOIR;
                    b.bouton_interrupt = 1;
                }

            break;

            }

        }

//////////FIN DU PARCOURS SI LE ROBOT A FAIT LES QUATRE(4) SECTIONS////////////
  } 

 
  return 0; 
}


