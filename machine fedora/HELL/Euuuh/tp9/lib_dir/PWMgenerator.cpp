/**************************************/
/**************************************/
/* files:    PWMgenerator.cpp         */
/* authors: *Ursule Joelle Kanmegne   */
/*          *Aymen-Alaeddine Zeghaida */
/*          *Michelle Sepkap Sime     */
/*          *Khadija Rekik            */
/* Date:     October 21, 2019         */
/* Modification:   Novembre 5, 2019   */
/*                                    */
/**************************************/
/*                                    */
/* Spécifications : Pour le PWM       */
/*  matériel, les broches 5 et 6      */
/*  correspondent au PWM et les       */
/*  broches 7 et 8 à la direction.    */
/*  6 et 8 pour roue droite           */
/*  5 et 7 pour roue gauche           */  
/**************************************/
/**************************************/
#include "PWMgenerator.h"

#define D7 7
#define D6 6

#define MAX 255
#define PERCENTAGE 100

#define ON 0x01
#define OFF 0x00

#define FULL_RIGHT_TURN_DURATION 1720
#define FULL_LEFT_TURN_DURATION 1550
#define TURN_RATE 200
#define RIGHT_ANGLE 90

/*******************************************************************/
/* Fonction créé pour faire des délais à partir de variables,      */
/* duree en ms                                                     */
/* param: duration                                                 */
/*          la durée du delay                                      */  
/* Aucune valeur de retour                                         */
/*******************************************************************/
void myDelay(uint16_t duration){ 
    for (uint16_t i = 0; i < duration; i++){
     _delay_ms(1);
    } 
}

/********************************************************************/
/* Fonction créé pour ajuster le PWM de façon matérielle            */
/* param: dutyCycleLeft                                             */
/*        Niveau haut du PWM pour la roue gauche(entre [255..0])    */        
/* param: dutyCycleRight                                            */
/*        Niveau haut du PWM pour la roue droite (entre [255..0])   */
/* dutyCycle est la proportion du niveau haut du PWM par rapport a  */
/* toute la periode                                                 */        
/* Aucune valeur de retour                                          */
/********************************************************************/
void ajustHardwarePWM ( uint8_t dutyCycleLeft, uint8_t dutyCycleRight ) {

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)
    OCR1A =  dutyCycleRight * MAX / PERCENTAGE;
    OCR1B =  dutyCycleLeft  * MAX / PERCENTAGE;

    // division d'horloge par 8 - implique une frequence de PWM fixe
    // 8-bit phase correct
    TCCR1A = (1 << COM1A1) | (1 << COM1B1)| (1 << WGM10);
    // Prescaler de 8
    TCCR1B = (1 << CS11) ;
    TCCR1C = 0;

}

/*******************************************************************/
/* Fonction créé pour générer le PWM de façon logicielle           */
/* param:   *dutyCycle                                             */  
/*        Pourcentage niveau haut du PWM                           */
/*         *direction                                              */
/*          la direction de la roue                                */
/*         *duration                                               */
/*          la durée du signal PWM                                 */        
/* Aucune valeur de retour                                         */
/*periode de 510 us donc il faut compter jusqu'à 4000 por l'atteindre*/
/*                                                                 */
/* La broche 1 correspond au PWM et 2 à la direction               */
/*******************************************************************/
void generateSoftwarePWM(uint8_t dutyCycle, uint8_t direction, uint8_t duration){ 
    uint16_t highLevelDuration;

    switch(dutyCycle) {
        case 0 : highLevelDuration = 0;
                    break;
        case 25 : highLevelDuration = PERIOD / 4;
                    break;
        case 50 : highLevelDuration = PERIOD / 2;
                    break;
        case 75 : highLevelDuration = 3 * (PERIOD / 4);
                    break;
        case 100 : highLevelDuration = PERIOD ;
                    break;
        default : break;
    }
    //prendre les mêmes ports qu'on aurait pris pour le PWM de façon matérielle.

    PORTB = (ON | (direction << 1));
    _delay_loop_2(highLevelDuration);
    PORTB = (OFF | (direction << 1));
    _delay_loop_2(PERIOD  - highLevelDuration);
}

/*******************************************************************/
/* Fais avancer les roues (Pin 7 et 8 (du robot) doivent etre a 0) */
/* param: dutyCycleLeft                                            */
/*        Niveau haut du PWM pour la roue gauche(entre [255..0])   */ 
/* param: dutyCycleRight                                           */
/*        Niveau haut du PWM pour la roue droite (entre [255..0])  */
/*******************************************************************/
void goForward(uint8_t dutyCycleLeft, uint8_t dutyCycleRight ) {
    
    PORTD &= ~( (1 << D6) | (1 << D7) );
    
    ajustHardwarePWM( dutyCycleLeft, dutyCycleRight );
}

/*******************************************************************/
/* Fais avancer les roues (Pin 7 et 8 (du robot) doivent etre a 1) */
/* param: dutyCycleLeft                                            */
/*        Niveau haut du PWM pour la roue gauche(entre [255..0])   */ 
/* param: dutyCycleRight                                           */
/*        Niveau haut du PWM pour la roue droite (entre [255..0])  */
/*******************************************************************/
void goBackward(uint8_t dutyCycleLeft, uint8_t dutyCycleRight ) {
    
    PORTD |= (1 << D6) | (1 << D7);
    
    ajustHardwarePWM( dutyCycleLeft, dutyCycleRight );
}

/*******************************************************************/
/* Arrete les roues                                                */
/* param:  -                                                       */  
/*******************************************************************/
void stopMotion(){

    ajustHardwarePWM( OFF, OFF);

}

/*******************************************************************/
/* Fais tourner le robot d'un angle precise vers la droite         */
/* param:    angle    uint8_t                                      */  
/*           Angle en degree a tourner [180..0]                    */   
/*******************************************************************/
void turnRight(const uint8_t angle){
   
    // Un elan initial a la vitesse maximale est necessaire afin de faire 
    // tourner les 2 roues a partir du repos. 
    goForward(MAX, OFF );
    _delay_ms(25);
    
    goForward(TURN_RATE, OFF );
    myDelay((angle / RIGHT_ANGLE) * FULL_RIGHT_TURN_DURATION );

    stopMotion();
    _delay_ms(25);
}

/*******************************************************************/
/* Fais tourner le robot d'un angle precise vers la gauche         */
/* param:    angle    uint8_t                                      */  
/*           Angle en degree a tourner [180..0]                    */   
/*******************************************************************/
void turnLeft(const uint8_t angle){
    
    // Un elan initial a la vitesse maximale est necessaire afin de faire 
    // tourner les 2 roues a partir du repos. 
    goForward(OFF, MAX);
    _delay_ms(25);
    
    goForward(OFF, TURN_RATE );
    myDelay((angle / RIGHT_ANGLE) * FULL_LEFT_TURN_DURATION  );

    stopMotion();
    _delay_ms(25);
}