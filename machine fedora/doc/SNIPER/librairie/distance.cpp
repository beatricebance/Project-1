/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : Implementation des fonctions de la classe distance
  *
 */

#include "distance.h"


// Declarations des variables globales
static volatile uint16_t pulse = 0;
static volatile int i = 0;
volatile uint16_t debordement = 0;

void Distance::initialisationTimer0(void)
{
    cli();
    // les autres broches en sortie et la broche 3 du port B en mode entree
    DDRB = 0b11111011;
    // Mettre les broches du PORT A en sortie
    DDRA = 0xC0;
    // Activer l'interruption INT2
    EIMSK |= (1 << INT2);
    // Fixer le trigger de l'interruption pour un changement logique
    EICRA |= (1 << ISC20);
    // Desactiver le compteur
    TCCR0B = 0;
    // Activer les interruptions globales
    sei();
}
/********************************************************/
//*****Routine d'interruption des service avec  INT2 **//
/********************************************************/
ISR(INT2_vect)
{
    if (i == 1)
    {
        // Arreter le compteur
        TCCR0B = 0;
        // Activer l'interruption pour le debordement
        TIMSK0 &= ~(1 << TOIE0);
        // La memoire de comptage est mis a jour en entier
        pulse = TCNT0 + (256 * debordement);
        // Reinitialiser la memoire de comptage
        TCNT0 = 0;
        // Remettre la variable i a 0
        i = 0;
    }
    if (i == 0)
    {
        debordement = 0;
        TCCR0B |= (1 << CS01);

        //clock/8 --> tcnt1 incremente chaque 1 microseconde
        //simplifie le calcul pas besoin de convertir le pulse
        TIMSK0 |= (1 << TOIE0);  
        i = 1;
    }
}
/**********************************************************/
//* Routine de service d'interruption pour le debordement*//
//** appele a chaque fois que le compteur TCNT0 deborde **//
/**********************************************************/
ISR(TIMER0_OVF_vect)
{
    // garder la trace du nombre de debordements
    ++debordement;
}


/*****************************************************************************************
* Fonction: Distance                                                             
* Description: Fonction qui permet de faire le parcours du mur   
*Fonction permettant de calculer la distance entre 
*le sonar(SRF05) et le mur. Si la distance est bonne 
* la LED devient verte sinon elle devient rouge pendant l'ajustement du robot.
* Paramètres: aucun
* Retour: rien                                                              
******************************************************************************************/

void Distance::sonar()
{


    // Initialiser le timer
    initialisationTimer0();

    // Instanciation des classes dont on a besoin
    DEL del;
    Roues R;
    SuiveurLigne suiveur;
   
    // Definition d'une variable distance pour stocker la distance
    uint16_t COUNTA = 0;
    // Mettre la broche 1 du port B en sortie
    DDRB |= _BV(DDB0);
    // Mettre la broche 3 du port B en entree
    DDRB &= ~_BV(DDB2);
    PORTB |= 0b00000011;
    // Observer un delai
    _delay_us(15);
    // Mettre le port B en entree
    PORTB |= 0b00000000;
    _delay_ms(50);

    // ligne H I
    while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5)
    {
        suiveur.suiveurLigne();
    }
        // Sonar
        while (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5))
        {
            PORTB |= _BV(PINB0);
            _delay_us(15);
            PORTB &= ~_BV(PINB0);
            // Calculer la distance
            COUNTA = pulse / 58;
            _delay_ms(50);
            if (COUNTA <= (13))
            {
                // Avancer le robot vers la droite quand la distance atteint 13cm
                R.ajustementRoues(30,50,AVANT);
                del.couleurRouge();
            }
            else if (COUNTA > (16))
            {
                // Avancer le robot vers la gauche quand la distance atteint 16cm
                R.ajustementRoues(50,30, AVANT);
                del.couleurRouge();
            }
            else if ((COUNTA >= (14)) && (COUNTA <= (16)))
            {
                // Avancer le robot quand la distance est entre 14 et 16.
                R.ajustementRoues(38, 38, AVANT);
                del.couleurVerte();
            } 
            // Definir un delai de 50ms
            _delay_ms(50);
        }
        del.delEteinte();
      

    // ligne JK 
    while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){
        
           R.ajustementRoues(40,40, AVANT);  
            _delay_ms(900);
           R.ajustementRoues(0,0, AVANT);
    }
   

   // Redressement
   while ((!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5))){
       while (!(CAP_3)){

            R.ajustementRoues(0,50, AVANT);

       }
   }

    R.ajustementRoues(0,0, AVANT);


//LIGNE KL
while (CAP_1 || CAP_2 || CAP_3 || CAP_4 || CAP_5){  
        suiveur.suiveurLigne();
    }    
    

while (CAP_1 && CAP_2 && CAP_3 && CAP_4 && CAP_5){
         _delay_ms(600);
         R.ajustementRoues(0,0, AVANT);
          _delay_ms(900);
    } 

 R.ajustementRoues(0,0,AVANT); 
 
 }