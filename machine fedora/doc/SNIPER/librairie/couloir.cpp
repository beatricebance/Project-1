/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  Implementation de la fonction pour faire le Couloir
  *
 */

#include "couloir.h"

/*****************************************************************************************
* Fonction: Le_couloir                                                              
* Description: Fonction qui permet de faire le parcours du couloir         															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/

void Couloir::Le_couloir()
{
        SuiveurLigne suiveur;
        Roues R;


 // ligne A B
        while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){
                suiveur.suiveurLigne();
        }
        
// ligne B G
       while ( !(CAP_2) && !(CAP_3) && !(CAP_4)){
               while (debutZone_BG )
                {
                        R.ajustementRoues(35, 0, AVANT);
                        _delay_ms(250);
                        debutZone_BG  = false;
                }
                 while (CAP_5)
                {
                        R.ajustementRoues(50, 0, AVANT); //50
                        _delay_ms(200); 
                }
                while (CAP_1)
                {
                        R.ajustementRoues(0, 50, AVANT); //50
                        _delay_ms(200); 
 
                }
                while ( CAP_3) {
                     R.ajustementRoues(0,0,AVANT); 
                    _delay_ms(500);
                  

                }

       }

// G H
  while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){

        if (CAP_5 && CAP_1){
                while (!(CAP_3)){

                        R.ajustementRoues(0,40,AVANT);

                        while (CAP_2){
                           R.ajustementRoues(0,0,AVANT);    
                           _delay_ms(500); 
                                while (!(CAP_3)){
                                        R.ajustementRoues(40,0,AVANT);
                                }
                         
                        }
                        
                } 

                
        }
        R.ajustementRoues(0,0,AVANT); 
                _delay_ms(500);

        while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){
               suiveur.suiveurLigne();
        }
                            
  }


R.ajustementRoues(0,0,AVANT);
}