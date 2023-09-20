/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe communication permetttant l'initialisation des ports 
  *
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

class COMMUNICATION{
public: 
  // Constante pour la direction des ports
const uint8_t PORT_ENTREE = 0x00 ;
const uint8_t PORT_SORTIE = 0xff ;

// Constante couleur DEL
const uint8_t ROUGE = 0x02 ;
const uint8_t VERT = 0x01 ;
const uint8_t ETEINT = 0x00 ;


// Constante moteur
const uint8_t MAX_MOTEUR = 255 ;
const uint8_t MIN_MOTEUR = 0 ;

// Fonction permettant d'attendre en utilisant _delay_ms
void attendre(uint16_t millisecondes);
// Fonstion pour l'initialisation de la direction des ports
void initialisation ( uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD );

};


#endif
