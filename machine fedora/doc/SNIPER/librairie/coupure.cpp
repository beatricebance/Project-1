/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  Implementation de la fonction pour faire les coupures
  *
 */
#include "coupure.h"



/*****************************************************************************************
* Fonction: Les_coupures                                                             
* Description: Fonction qui permet de faire le parcours des coupures et 
               d'actionner une sonarite selon les transitions entre les coupures       															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/
void Coupure::Les_coupures(){
        SuiveurLigne suiveur;
        Roues R;
        SONORITE s;
//while (fairecoupure){
        //ligne t-v
        while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){
        
        suiveur.suiveurLigne();
        }
        while  ((!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)))
        {
             s.son_aigu();
        R.ajustementRoues(0,40,DROITE);
        _delay_ms(25);    
        }
        
        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);


        //ligne w-y
        while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){
        s.arreterSonorite();
        suiveur.suiveurLigne();
        }
        while  ((!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)))
        {
             s.son_grave();
        R.ajustementRoues(40,0,GAUCHE);
        _delay_ms(25);    
        }
       
        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);

        
        
         //ligne z-2
        while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){

         s.arreterSonorite();
        suiveur.suiveurLigne();
        }

        while  ((!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)))
        {
              s.son_aigu();
        R.ajustementRoues(0,40,DROITE);
        _delay_ms(25);    
        }

        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);

       
 

        //ligne t-v
        while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){
              s.arreterSonorite();
        
        suiveur.suiveurLigne();
        }
        while  ((!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)))
        {
             s.son_grave();
        R.ajustementRoues(40,0,GAUCHE);
        _delay_ms(25);    
        }
        R.ajustementRoues(0,0,AVANT);
        _delay_ms(50);


          
        while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){
        s.arreterSonorite();
          suiveur.suiveurLigne();
        }

        R.ajustementRoues(0,0,AVANT);
     //     _delay_ms(100);
     //           while (!(CAP_5)){
     //                    R.ajustementRoues(40,0,AVANT); // tourne a gauche avec une vitesse de 40%
     //           }
     //            R.ajustementRoues(0,0,AVANT);
     //            _delay_ms(900);  // durant 400 ms
     //            fairecoupure = false; // sort de la fonction Les_Deux_Boucles
       
//}
  
}