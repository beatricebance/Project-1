/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe DEL
  *
 */

#include "DEL.h"


/******************************************************************************
* Fonction: couleur                                                                 
* Description: Allume la Del selon la couleur passer en parametre          															  
* Paramètres: uint8_t couleur
* Retour: aucun       
* LE PORTA EST LE PORT UTILISER POUR LA DEL                                                           
******************************************************************************/

void DEL::Couleur(uint8_t couleur){
            PORTA  = couleur ;
}



/******************************************************************************
* Fonction: couleurAmbre                                                                 
* Description: Allume la Del en Ambre , elle fait appel la fonction couleur        															  
* Paramètres: aucun
* Retour: aucun  
* UTILISATION DE LA FONCTION attendre PAR HERITAGE DE LA CLASSE COMMUNICATION                                                              
******************************************************************************/


void DEL :: CouleurAmbre()
{
		Couleur(VERT);//Allumer la Del en vert
		attendre(5);
		Couleur(ROUGE);//Allumer la Del en rouge
		attendre(5);
}



/******************************************************************************
* Fonction: clignoter                                                                 
* Description: Fais clignoter la del selon la couleur passer en parametre 
* et le nombre de repetition  souhaiter     															  
* Paramètres: uint8_t nbRepetition, uint8_t couleur
* Retour: aucun                                                                 
******************************************************************************/


void DEL :: clignoter(uint8_t nbRepetition, uint8_t couleur) {

    for (int i = 0; i <nbRepetition ; i++){
        Couleur(couleur);
        attendre(1000);
        Couleur(ETEINT);
        attendre(1000);                
    }   
}

