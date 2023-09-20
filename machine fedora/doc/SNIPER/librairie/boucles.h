/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : classe Boucles
  *
 */

#ifndef _BOUCLES_H_
#define _BOUCLES_H_

#define F_CPU 8000000UL
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <math.h> 
#include "roues.h"
#include "suiveurLigne.h"


#define CAP_1  PINA & 1<<0 // Definit pin0 = 1 comme capteur 1 (CAP_1)
#define CAP_2  PINA & 1<<1 // Definit pin1 = 1 comme capteur 2 (CAP_2)
#define CAP_3  PINA & 1<<2 //Definit pin2 = 1 comme capteur 3  (CAP_3)
#define CAP_4  PINA & 1<<3 //Definit pin3 = 1 comme capteur 4  (CAP_4)
#define CAP_5  PINA & 1<<4 // Definit pin4 =1 comme capteur 5  (CAP_5)


class Boucles{

public:
         void Les_Deux_Boucles();
         bool debut = true;
         bool faireboucle = true ;
       
};
#endif