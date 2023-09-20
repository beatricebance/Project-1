/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : Implementation des fonctions pour faire le suiveur de ligne
                 Deux fonctions car pour les boucles le robots doit rouler
                 a une vitesse un peu faible pour eviter qu'il rentre sur la mauvaise boucle
*/
#include "suiveurLigne.h"


/*********************************************************************************************
* Fonction: suiveurLigneBoucle_droit                                                            
* Description: Fonction qui permet au robot de suivre la ligne lors du parcours de deux boucles  
                Grace aux capteurs
* Paramètres: aucun
* Retour: rien                                                              
*********************************************************************************************/
void SuiveurLigne::suiveurLigneBoucle_droit(){

// direction des ports
DDRA = 0xC0;  // port A en entree sauf ses broches 6 et 7 en sortie car utiliser pour la DEL libre
DDRD = 0xFF;  // port D en sortie       

          if(CAP_1 && CAP_2 && CAP_3){
                  
                 
                    _delay_ms(10);
                    while (CAP_1 && CAP_2 && CAP_3){
                    ajustementRoues(38,38,AVANT);
                    }
                    compteur ++; // compteur incrementer de 1
                    
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

/*****************************************************************************************
* Fonction: suiveurLigne                                                           
* Description: Fonction qui permet au robot de suivre la ligne noir lors de son parcours
               Grace aux capteurs       															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/

 void SuiveurLigne::suiveurLigne(){  

DDRA = 0xC0;  // port A en entree sauf les broches 6 et 7 en sortie car utiliser pour la DEL libre
DDRD = 0xFF;  // port D en sortie
  
            if(CAP_3){
                    _delay_ms(10);
                    if(CAP_3){
                    ajustementRoues(55,55,AVANT);                    }
            }
            else if(CAP_1){
                    _delay_ms(10);
                    if(CAP_1){
                    ajustementRoues(45,15,GAUCHE);
                    }
            }
            else if(CAP_2){
                    _delay_ms(10);
                    if(CAP_2){
                    ajustementRoues(45,25,GAUCHE);
                    }
            }
            else if(CAP_4){
                    _delay_ms(10);
                    if(CAP_4){
                    ajustementRoues(25,45,DROITE);
                    }
            }
            else if(CAP_5){
                    _delay_ms(10);
                    if(CAP_5){
                    ajustementRoues(15,45,DROITE);
                    }
            }
            else
            {
                    _delay_ms(100);
                    if(PINA || 0)
                    ajustementRoues(0,0,AVANT);          }
    }