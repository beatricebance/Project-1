/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : Implementation de la fonction pour faire les deux boucles
  *
 */


#include "boucles.h"

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupe par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupe par l'afficheur


/*****************************************************************************************
* Fonction: Les_Deux_Boucles                                                              
* Description: Fonction qui permet de faire le parcours des deux boucles         															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/

 void Boucles:: Les_Deux_Boucles()
{ 
    // instanciation des classes    
    Roues R;
    SuiveurLigne suiveur;


// Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);

               

suiveur.compteur =0 ; 
                     
 while (faireboucle) {

                disp.clear();
                disp << suiveur.compteur;
                
         if(suiveur.compteur <= 2){

                  suiveur.suiveurLigneBoucle_droit();   // appel a suiveurLigneBoucle_droit                                          
         }

        else if(suiveur.compteur == 3){  

        R.ajustementRoues(0,0,AVANT); // robot arreter
        _delay_ms(500);
                                
                if(debut){ 

                        R.ajustementRoues(60,0,AVANT);// tourne a gauche avec une vitesse de 60%
                        _delay_ms(400);              // durant 400 ms
                         debut = false;              // fin du debut de la premiere boucle
                         suiveur.compteur ++;        // incremente compteur
                                                
                }

        
        }
        
        else if (suiveur.compteur >3 && suiveur.compteur <7){
                                
                // si aucun capteur n'est allumer
                if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){

                         while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){

                              // tourne a gauche avec une vitesse de 40%  
                                R.ajustementRoues(40,0,AVANT); 
                                _delay_ms(100);

                        }
                
                }

                suiveur.suiveurLigneBoucle_droit(); // sinon fais le suiveur de ligne de la boucle
         
         }

        else if (suiveur.compteur >=7 && suiveur.compteur <11) {
        
                // si les trois(3) premiers capteurs sont allumer
                if(CAP_1 && CAP_2 && CAP_3){

                         _delay_ms(700); // attend 700 ms
                         R.ajustementRoues(0,0,AVANT);
                        _delay_ms(100);

                // tant que le capteur 3 n'est pas allumer tourne a gauche avec une vitesse de 39%                  
                         while (!(CAP_3)){ 
                                R.ajustementRoues(39,0,AVANT);         
                         }
                                                          
                        suiveur.compteur ++ ; // incremente compteur
                                            
                }

                // si aucun capteur n'est allumer
                else  if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ) {
                               
                         while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){

                              // tourne a gauche avec une vitesse de 40%    
                                R.ajustementRoues(50,0,AVANT);
                                _delay_ms(100);

                        }
                
                }
                                
                                        
                suiveur.suiveurLigneBoucle_droit(); // sinon fais le suiveur de ligne de la boucle
                                                
                                                

         }

        else if (suiveur.compteur >=11 && suiveur.compteur <=13){
                                
                suiveur.suiveurLigneBoucle_droit(); // sinon fais le suiveur de ligne de la boucle

        }
        
        else if (suiveur.compteur == 14){

                R.ajustementRoues(0,0,AVANT); // robot arreter
               _delay_ms(100);
                R.ajustementRoues(40,0,AVANT);
                _delay_ms(400);

        //        while (!(CAP_3)){
        //                 R.ajustementRoues(40,0,AVANT); // tourne a gauche avec une vitesse de 40%
        //        }
        //         R.ajustementRoues(0,0,AVANT);
        //         _delay_ms(900);  // durant 400 ms
                faireboucle = false; // sort de la fonction Les_Deux_Boucles
         }


 }         
} 


