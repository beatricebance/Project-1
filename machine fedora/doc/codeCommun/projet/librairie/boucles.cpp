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

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h> 
#include "roues.h"
#include "suiveurLigne.h"
#include "boucles.h"

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupe par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupe par l'afficheur


 void Boucles:: Les_Deux_Boucles()
{ 
    Roues R;
    SuiveurLigne suiveur;


// Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);

suiveur.compteur =0 ; 
                     
                while (faireboucle) {

                disp.clear();
                disp << suiveur.compteur;
                
                if(suiveur.compteur <= 2){
                                suiveur.suiveurLigneBoucle_droit();   
                                                    
                        }

                        else if(suiveur.compteur == 3){
                        
                                 
                                R.ajustementRoues(0,0,AVANT);
                                _delay_ms(500);
                                
                                if(debut){ 

                                                R.ajustementRoues(60,0,AVANT);
                                                _delay_ms(400);
                                                debut = false;
                                                suiveur.compteur ++;
                                                
                                        }

        
                        }
                        else  if (suiveur.compteur >3 && suiveur.compteur <7){
                                

                        if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) )
                        
                        {



                                while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                                
                                R.ajustementRoues(40,0,AVANT);
                                _delay_ms(100);

                                }
                
                        }

                                suiveur.suiveurLigneBoucle_droit(); 
         
                        }

        ////////////////////////////////////////PROBLEME///////////////////////////////////////////////////////////////////

                        else if (suiveur.compteur >=7 && suiveur.compteur <11) {
        

                                        if(CAP_1 && CAP_2 && CAP_3){

                                                _delay_ms(700);
                                                  R.ajustementRoues(0,0,AVANT);
                                                  _delay_ms(100);
                                        
                                                        while (!(CAP_3)){
                                                                R.ajustementRoues(39,0,AVANT);
                                                                       // _delay_ms(400);
                                                                }
                                                        

                                                
                                                suiveur.compteur ++ ;
                                                
                                               

                                            
                                        }


                           else  if(!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) )
                        
                        {



                                while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5) ){
                                
                                R.ajustementRoues(50,0,AVANT);
                                _delay_ms(100);

                                }
                
                        }
                                
                                        
                                  suiveur.suiveurLigneBoucle_droit(); 
                                                
                                                

                        }

                        else if (suiveur.compteur >=11 && suiveur.compteur <=13){
                                
                        suiveur.suiveurLigneBoucle_droit();

                        }
                        else if (suiveur.compteur == 14){


                                  R.ajustementRoues(0,0,AVANT);
                                 _delay_ms(100);
                                  R.ajustementRoues(40,0,AVANT);
                                 _delay_ms(400);

                                 faireboucle = false;


                        }


                } 




          

  } 


