/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe DEL
  *
 */


#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h> 
#include "DEL.h"


/*****************************************************************************************
* Fonction: Constructeur de la classe Del                                                              
* Description: Fonction qui permet de mettre en sortie (1) les broches 6 et 7 du port A       															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/
void DEL::Del()
{
    DDRA |= _BV(6) | _BV(7); // Broches 6 et 7 du PORTA en sortie
    PORTA &= ~_BV(6) & ~_BV(7); //led eteinte
}


/*****************************************************************************************
* Fonction: couleurAmbre                                                             
* Description: Fonction qui permet d'allumer la del en Ambre  
               en alternant le vert et le rouge tres rapidement     															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/
void DEL::couleurAmbre()
{
    couleurVerte();  // allumer del en verte
     _delay_ms(10);  // attendre pendant 10 millisecondes
    couleurRouge(); // allumer del en rouge
    _delay_ms(10);  // attendre pendant 10 millisecondes
    
}
    

/*****************************************************************************************
* Fonction: couleurVerte                                                              
* Description: Fonction qui permet d'allumer la del en Vert        															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/   
void DEL::couleurVerte()
{      
  
    PORTA &= ~_BV(6); // broche 6 en sortie
    PORTA |= _BV(7);  // broche 7 en entree
}
    

/*****************************************************************************************
* Fonction: couleurRouge                                                             
* Description: Fonction qui permet d'allumer la del en Rouge       															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/      
void DEL::couleurRouge()
{
        
    PORTA &= ~_BV(7); // broche 7 en sortie 
    PORTA |= _BV(6);  // broche 6 en entree

}
    

 /*****************************************************************************************
* Fonction: delEteinte                                                              
* Description: Fonction qui permet d'eteindre la del       															  
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/     
void DEL::delEteinte()
{
    
    
PORTA &= ~_BV(6) & ~_BV(7); //les broches 6 et 7 sont mis en entree ainsi la del est eteinte

}


