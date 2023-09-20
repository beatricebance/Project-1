//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
/**************************************/
/* files:    PWMgenerator.h           */
/* authors: *Ursule Joelle Kanmegne   */
/*          *Aymen-Alaeddine Zeghaida */
/*          *Michelle Sepkap Sime     */
/*          *Khadija Rekik            */
/* Date:     October 21, 2019         */
/*                                    */
/**************************************/
/**************************************/

#ifndef PWM_H
#define PWM_H

#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>

// le timer doit compter jusqu'à 4000 pour réaliser une période
#define PERIOD 4000 


//Fonction créée pour faire des délais à partir de variables, duree en ms.
void myDelay(uint16_t duration); 

// Ajuste les registres d'une façon précise afin de produire du PWM
// dutyCycleLeft et Right sont entre 0 et 1
void ajustHardwarePWM ( uint8_t dutyCycleLeft, uint8_t dutyCycleRight ) ;

// Génère du PWM de façon logicielle
void generateSoftwarePWM(uint8_t dutyCycle, uint8_t direction, uint8_t duration); 

// Fait avancer le robot
void goForward(uint8_t dutyCycleLeft, uint8_t dutyCycleRight );

// Fait reculer le robot
void goBackward(uint8_t dutyCycleLeft, uint8_t dutyCycleRight );

// Arrete le robot
void stopMotion();

// Fait tourner le robot de d'un angle du degree specifie a partir de la droite 
void turnRight(const uint8_t angle);

// Fait tourner le robot de d'un angle du degree specifie a partir de la gauche 
void turnLeft(const uint8_t angle);


#endif /* PWM_H */