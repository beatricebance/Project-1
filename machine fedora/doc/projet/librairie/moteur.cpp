
/*
  * Noms:
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :classe moteur pour faire tourner les roues  
  *
 */
#define F_CPU 8000000UL
#include "moteur.h"
#include <util/delay.h>
#include <avr/io.h> 


#define MAX 255
#define POURCENTAGE 100

/******************************************************************************
* Fonction:  moteur                                                                  
* Description: Constructeur qui met en sortie les broches 4 a 7 du port D          															  
* Paramètres: aucun
* Retour: aucun                                                                 
******************************************************************************/


void Moteur::moteur()
{
    //0xF0 On met en sortie les broches 4 a 7 du PORTD
    // roue gauche 4 et 6
    // roue droite 5 et 7 
        DDRD |= _BV(4) | _BV(5) |_BV(6) |_BV(7); 
                                                
                                               
}



/******************************************************************************
* Fonction:  ajustementPWM                                                                    
* Description: ajuste la vitesse de rotation des roues          															  
* Paramètres: double vitesseDroite, double vitesseGauche
* Retour: aucun                                                                 
******************************************************************************/


void Moteur::ajustementPWM(double vitesseDroite, double vitesseGauche) {


TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10) ; //table16-4 pour phase correcte


// si la valeur est superieur a la valeur maximale 255 utiliser 255
 if (vitesseDroite > 255){
    vitesseDroite = 255;
 }

// si la valeur est superieur a la valeur maximale 255 utiliser 255        
if (vitesseGauche > 255){
   vitesseGauche = 255;
}

OCR1A = vitesseDroite ;

OCR1B = vitesseGauche ;


// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1B = TCCR1B |= (1<<CS11) ; //p135 clk/8;

}


/******************************************************************************
* Fonction: arreterMoteur                                                                   
* Description: arreter les moteurs          															  
* Paramètres: aucun
* Retour: aucun                                                                 
******************************************************************************/

void Moteur::arreterMoteur(){
    
    ajustementPWM(0.0, 0.0);

}



/******************************************************************************
* Fonction: avancer                                                                  
* Description: avancer avec les roues         															  
* Paramètres: double vitesseDroite, double vitesseGauche
* Retour: aucun                                                                 
******************************************************************************/


void Moteur::avancer(double vitesseDroite, double vitesseGauche)
{
    PORTD &= 0x00;
    ajustementPWM(vitesseDroite, vitesseGauche);
    
    
}


/******************************************************************************
* Fonction: reculer                                                                  
* Description: reculer avec les roues        															  
* Paramètres:double vitesseDroite, double vitesseGauche
* Retour: aucun                                                                 
******************************************************************************/


void Moteur::reculer(double vitesseDroite, double vitesseGauche){
    PORTD |= 0xF0;  
    ajustementPWM(vitesseDroite, vitesseGauche);
    
}

/******************************************************************************
* Fonction: tournerGauche                                                                  
* Description: avancer la roue gauche pour tourner a gauche          															  
* Paramètres: double vitesseGauche
* Retour: aucun                                                                 
******************************************************************************/


void Moteur::tournerGauche(double vitesseGauche)
{
    // on force a 1 les ports 4 et 6 relier a la roue Gauche
    PORTD |= ~_BV(4) & ~_BV(6); 
    ajustementPWM(0, vitesseGauche);

    
}

/******************************************************************************
* Fonction: tournerDroite                                                                  
* Description: avancer la roue droite pour tourner a droite          															  
* Paramètres: double vitesseDroite
* Retour: aucun                                                                 
******************************************************************************/


void Moteur::tournerDroite(double vitesseDroite){
    
    // on force a 1 les ports 5 et 7 relier a la roue Droite
    PORTD |= ~_BV(5) & _BV(7); 
   ajustementPWM(vitesseDroite,0);

    
}
