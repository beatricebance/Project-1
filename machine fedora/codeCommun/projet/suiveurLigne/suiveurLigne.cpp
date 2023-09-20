/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  suiveur de ligne
  *
 */

#define F_CPU 8000000UL

#define del_1  PINA & 1<<0
#define del_2  PINA & 1<<1
#define del_3  PINA & 1<<2
#define del_4  PINA & 1<<3
#define del_5  PINA & 1<<4



#include <avr/io.h>
#include <math.h> 
#include "moteur.h"
#include "suiveurLigne.h"



/******************************************************************************
* Fonction:      initialisationSuiveurligne                                                              
* Description: Constructeur qui met en  entree le port a sauf le pin 5 qui est en sortie       															  
* Paramètres: aucun
* Retour: aucun                                                                 
******************************************************************************/

void Suiveurligne::initialisationSuiveurligne()
{
       DDRA=0x20;                                                                                            
}


/******************************************************************************
* Fonction:      suiveurLigneCouloir                                                             
* Description: Constructeur qui met en  entree le port a sauf le pin 5 qui est en sortie       															  
* Paramètres: aucun
* Retour: aucun                                                                 
******************************************************************************/

void Suiveurligne::suiveurLigneCouloir(){

  Moteur moteur;

  // while (1){
            if (del_1){
                    moteur.tournerDroite(100); 
            }
               
           else  if (del_3 || del_2 || del_4){
                   moteur.avancer(150.0,150.0);  
           }

           else  if (del_3 & del_2 & del_4){
                   moteur.avancer(150.0,150.0);  
           }
 
           else  if (del_1 && del_2 && del_3 & del_4 & del_5){
                   moteur.avancer(150.0,150.0);  
           }

            else if (del_5){
                    
                    moteur.tournerGauche(100); 

            }
                        
           else {

               moteur.avancer(150.0,150.0); 
             // moteur.arreterMoteur();
           }
                

 //}

}



void suiveurLigneCouloir_AB_GH(){

        DDRD=0xff;
       
       // instance de la classe moteur
        Moteur moteur;

            if (del_1){
                   // moteur.tournerDroite(100); 
                   moteur.avancer(170.0,40.0); 

            }
     
                
           else  if (del_3 || del_2 || del_4){
                   moteur.avancer(170.0,170.0);  
           }

            else if (del_5){
                    
                   // moteur.tournerGauche(100); 
                   moteur.avancer(170.0,40.0); 

            }

            else  if (del_3 && del_2 && del_3 && del_4){
                   moteur.avancer(40.0,170.0);  
           }
                        
           else {

              // moteur.avancer(150.0,150.0); 
              moteur.arreterMoteur();
            
           }

}



// suiveur de ligne pour le couloir partie CEDF

void suiveurLigneCouloir_CEDF(){

        DDRD=0xff;
       
       // instance de la classe moteur
        Moteur moteur;

            if (del_1){
                    moteur.tournerDroite(100); 

            }

            else if (del_5){
                    
                    moteur.tournerGauche(100); 

            }

            else  if (del_3 || del_2 || del_4){
                   moteur.avancer(150.0,150.0);  
           }

            else  if (del_3 && del_2 && del_4){
                   moteur.avancer(40.0,170.0);  
           }
              
                        
           else {

               moteur.avancer(150.0,150.0); 
           }
}


                         R.ajustementRoues(50,50,AVANT);
                         while (CAP_1 && CAP_2 && CAP_3)
                         {
                                R.ajustementRoues(0,0,AVANT);  
                                 disp.clear();
                                 disp.write(" the end ",2);
                         }




                          R.ajustementRoues(40,40,AVANT);
                         _delay_ms (3000);
                        R.ajustementRoues(0,0,AVANT);





























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
            else if (compteur >=13){
                     //suiveurLigneBoucle_droit();

                      if(CAP_1 && CAP_2 && CAP_3){
                
                                while (CAP_1 && CAP_2 && CAP_3){
                                        R.ajustementRoues(40,40,AVANT);
                                               // _delay_ms(500);
                                        }
                                

                        
                        compteur ++;
                        disp.clear();
                        disp << compteur;    
                    }

                    if (compteur == 15)
                    {
                        R.ajustementRoues(0,0,AVANT);     
                    }
            }







                      }

                      else if (compteur >=18){
                          
                          disp.clear();
                          disp << compteur; 
                        // R.ajustementRoues(40,40,AVANT);
                        //  _delay_ms (300);
                        // R.ajustementRoues(0,0,AVANT);
                       // suiveurLigneBoucle_droit();
                     
                           
                      }
