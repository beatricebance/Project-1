#ifndef COMMUN_H
#define COMMUN_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t PORT_ENTREE = 0x00;
const uint8_t PORT_SORTIE = 0xff;

const uint8_t ROUGE = 2;
const uint8_t VERT = 1;
const uint8_t NOIR = 0;

const uint8_t ATTENTE_COURT = 3;	// Choix arbitaire de valeur
const uint8_t ATTENTE_LONG = 10;	// Choix arbitaire de valeur

const uint8_t ATTENTE_REBOND = 10;	// Choix arbitaire de valeur


void attendre(uint16_t millisecondes);
void initialisation ( uint8_t pA, uint8_t pB, uint8_t pC, uint8_t pD );

#endif