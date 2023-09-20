// suiveur de ligne pour les coupures pour redresser a droite
#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <math.h> 
#include "roues.h"
#include <avr/interrupt.h>

#define cap_1  PINA & 1<<0
#define cap_2  PINA & 1<<1
#define cap_3  PINA & 1<<2
#define cap_4  PINA & 1<<3
#define cap_5  PINA & 1<<4



/*void suiveurLigneCoupures_WXY_345(){

        DDRD=0xff;
       
       // instance de la classe moteur
        Roues roues;

            if (cap_1){
                   
                    //moteur.tournerDroite(100); 
                   roues.ajustementRoues(100.0,120.0,AVANT);  // ajuste par rapport a ton code

            }
     
                
           else  if (cap_3 || cap_2 || cap_4){
                   roues.ajustementRoues(120.0,120.0,AVANT);  
           }

            else if (cap_5){
                    
                    //moteur.tournerGauche(100);  
                   roues.ajustementRoues(120.0,100.0,AVANT); 

            }
                        
           else {

             //moteur.tournerGauche(100);  
             roues.ajustementRoues(120.0,100.0,AVANT);   // si il capte rien arrete le moteur
                                          // il est arriver a la fin de TUV ou Z12 
                                          // il doit tourner a droite ensuite pour continuer
                                          // sur les prochains segments avec le prochain suiveur de ligne
              
            
           }
           

}*/



void suiveurLigneCoupures_TUV_Z12(){

        DDRD=0xff;
       
       // instance de la classe moteur
        Roues roues;

            if (cap_1){
                   
                    //moteur.tournerDroite(100); 
                   roues.ajustementRoues(90.0,100.0,AVANT);  // ajuste par rapport a ton code

            }
     
                
           else  if (cap_3 || cap_2 || cap_4){
                   roues.ajustementRoues(120.0,120.0,AVANT);  
           }

            else if (cap_5){
                    
                    //moteur.tournerGauche(100);  
                   roues.ajustementRoues(100.0,90.0,AVANT); 

            }
                        
           else  if (!(cap_1) || !(cap_2) || !(cap_3) || !(cap_4) || !(cap_5)){
                   
        //        while (!ligne) {
        //              moteur.tournerDroite(100);    
        //              moteur.tournerGauche(100); 
        //        }

             roues.ajustementRoues(0,0,AVANT);
              
            
           }
           

}


/*void suiveurLigneCoupure() {
    Roues roues;    
    bool avancer = false;
    int coupure = 0;    
    DDRA=0x20;   
        if(coupure==0) {
                avancer=false;
               // disp.write("j'avance", 2);
                roues.ajustementRoues(100,100,AVANT);
                if (cap_1 || cap_2 || cap_3 || cap_4 || cap_5) {
                        coupure=1;
                       // disp.clear();
                }
        }
        if(coupure==1) {
               // disp.write("coupure1", 2);
                suiveurLigneCoupures_TUV_Z12();
                if(avancer==false){
                //detecter();
                if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                        _delay_ms(50);
                        //detecter();
                         if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                       // disp.clear();
                       // disp.write("           Tourne Droite",4);
                        avancer=true;
                        }
                }
                }
                if (avancer) {
                      roues.ajustementRoues(0,90,DROITE);
                      _delay_ms(5);
                      //detecter();
                        if (cap_1 || cap_2 || cap_3 || cap_4 || cap_5) {
                        _delay_ms(5);
                        //detecter();
                         if (cap_1 || cap_2 || cap_3 || cap_4 || cap_5) {
                                coupure=2;
                                avancer=false;
                               // disp.clear();
                               roues.ajustementRoues(0,0,AVANT);
                                _delay_ms(500);
                         }
                }
                }
        }
        if(coupure==2) {
                // disp.write("coupure2", 2);
                suiveurLigneCoupures_WXY_345();
                if(avancer==false){
                //detecter();
                if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                        _delay_ms(50);
                        //detecter();
                         if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                       // disp.clear();
                        //disp.write("           TourneGauche",4);
                        avancer=true;
                        }
                }
                }
                if (avancer) {
                      roues.ajustementRoues(90,0,GAUCHE);
                      _delay_ms(5);
                      //detecter();
                        if (cap_1 || cap_2 || cap_3 || cap_4 || cap_5) {
                        _delay_ms(5);
                        //detecter();
                         if (cap_1 || cap_2 || cap_3 || cap_4 || cap_5) {
                                coupure=3;
                                avancer=false;
                                //disp.clear();
                                roues.ajustementRoues(0,0,AVANT);
                                _delay_ms(500);
                         }
                }
                }
        }
        if(coupure==3) {
                 //disp.write("coupure3", 2);
                suiveurLigneCoupures_TUV_Z12();
                if(avancer==false){
                //detecter();
                if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                        _delay_ms(50);
                        //detecter();
                         if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                        //disp.clear();
                        //disp.write("           Tourne Droite",4);
                        avancer=true;
                        }
                }
                }
                if (avancer) {
                      roues.ajustementRoues(0,90,DROITE);
                      _delay_ms(5);
                      //detecter();
                        if (cap_1 || cap_2 || cap_3 || cap_4 || cap_5) {
                        _delay_ms(5);
                        //detecter();
                         if (cap_1 || cap_2 || cap_3 || cap_4 || cap_5) {
                                coupure=4;
                                avancer=false;
                               // disp.clear();
                                roues.ajustementRoues(0,0,AVANT);
                                _delay_ms(500);
                         }
                }
                }
        }
        if(coupure==4) {
               // disp.write("coupure4", 2);
                suiveurLigneCoupures_WXY_345();
                if(avancer==false){
                //detecter();
                if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                        _delay_ms(50);
                        //detecter();
                         if (!cap_1 & !cap_2 & !cap_3 & !cap_4 & !cap_5) {
                        //disp.clear();
                        //disp.write("           Tourne Gauche",4);
                        avancer=true;
            }
        }
 }
        }
}*/
int main(){
        suiveurLigneCoupures_TUV_Z12();
        }
