/**************************************/
/**************************************/
/* files:    soundGenerator.h         */
/* authors: *Ursule Joelle Kanmegne   */
/*          *Aymen-Alaeddine Zeghaida */
/*          *Michelle Sepkap Sime     */
/*          *Khadija Rekik            */
/* Date:     November 04, 2019        */
/*                                    */
/**************************************/
/*                                    */
/* Spécifications : Timer0 utilisé et */
/*  génération du PWM sur la broche 4 */
/*  du PORTB                          */
/*                                    */  
/**************************************/
/**************************************/

#ifndef SOUND_H
#define SOUND_H

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include <util/delay_basic.h>

// Réalise une partie de l'initialisation nécessaire 
// pour générer le son
void initialisationSound();

// Ajuste le registre OCR0A
void note(uint8_t noteMIDI);
void stopSound();

#endif /* PWM_H */
