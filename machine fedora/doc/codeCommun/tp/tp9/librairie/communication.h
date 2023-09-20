/*
  * Nom: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du bouton poussoir 
  *
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


// Constante pour la direction des ports
const uint8_t PORT_ENTREE = 0x00 ;
const uint8_t PORT_SORTIE = 0xff ;

// Constante couleur DEL
const uint8_t ROUGE = 2 ;
const uint8_t VERT = 1 ;
const uint8_t ETEINT = 0 ;

// Constante pour les attentes LED ambre
const uint8_t ATTENTE_COURT = 3 ;	// Choix arbitaire de valeur
const uint8_t ATTENTE_LONG = 10 ;	// Choix arbitaire de valeur

// Constante Bouton et debounce
const uint8_t ATTENTE_REBOND = 10 ;	// Choix arbitaire de valeur

// Constante moteur
const uint8_t MAX_MOTEUR = 255 ;
const uint8_t MIN_MOTEUR = 0 ;

// Constante sonorite
const double FREQUENCE_LA = 440.0;
const double MIDI_110Hz = 45.0;
const double MIDI_440Hz = 69.0;
const double MIDI_880Hz = 81.0;
const uint8_t TEMPS_QUART = 63;
const uint8_t TEMPS_TIER = 83;
const uint8_t TEMPS_DEMI = 125;
const uint8_t TEMPS_PLEIN = 250;
const uint16_t TEMPS_DOUBLE = 500;

// Fonctions communes
void attendre(uint16_t millisecondes);
void initialisation ( uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD );

#endif
