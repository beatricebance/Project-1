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

