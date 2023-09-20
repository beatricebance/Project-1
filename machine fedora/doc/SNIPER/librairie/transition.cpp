/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : Implementation de la fonction pour faire les deux boucles
  *
 */

#include "transition.h"

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupe par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupe par l'afficheur

void Transition :: TransitionSection(){

   // Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);
   disp.clear();
  disp << sectionParcouru;

// si les trois cpateurs de gauche ou droite ou si si tous les capteurs sont eteint
 if( (CAP_1 && CAP_2 && CAP_3) || (CAP_3 && CAP_4 && CAP_5) || (CAP_1 && CAP_2 && CAP_3 && CAP_4 && CAP_5)  || (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)) ){


    // tant que la condition est vrai                                    
       while ((CAP_1 && CAP_2 && CAP_3) || (CAP_3 && CAP_4 && CAP_5) || (CAP_1 && CAP_2 && CAP_3 && CAP_4 && CAP_5)  || (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)) ){
               
              while (!(CAP_3)){
                 // tourne a gauche avec une vitesse de 40%
                ajustementRoues(40,0,AVANT);
              } 
              
               ajustementRoues(0,0,AVANT);
               _delay_ms(300);
            
        }
        

    sectionParcouru ++; // incremente la sectionParcouru

                                            
 }

}


void Transition :: Redressement(){

  while (!(CAP_5)){
     ajustementRoues(40,0,AVANT); 
  }
  ajustementRoues(0,0,AVANT);
               _delay_ms(300);

}