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
#include "DEL.h"
#include "communication.h"
#include "moteur.h"


int main()
{


  DEL del;
  COMMUNICATION com;
  Moteur moteur;
    
    DDRD=0xff;
    DDRA=0x00;
    DDRC=0xff;
    DDRB=0xff;

  del.Couleur(com.VERT);

 while (1){
        //     if (del_1){

        //             do {
        //                  moteur.tournerDroite(100); 
        //             }while (!(del_3));
                    

        //     }
                
        //    else  if (del_3 || del_2 || del_4){
        //            moteur.avancer(150.0,150.0);  
        //    }

        //    else  if (del_3 & del_2 & del_4){
        //            moteur.avancer(150.0,150.0);  
        //    }
 
        //    else  if (del_1 && del_2 && del_3 & del_4 & del_5){
        //            moteur.avancer(150.0,150.0);  
        //    }

        //     else if (del_5){
        //             do {
        //                  moteur.tournerGauche(100); 
        //             } while (!(del_3));
                    

        //     }
                        
        //    else {
               
          _delay_ms(3000);
               moteur.avancer(110.0,125.0); 
             // moteur.arreterMoteur();
        //    }
                

 }
           
 
  return 0; 
}


