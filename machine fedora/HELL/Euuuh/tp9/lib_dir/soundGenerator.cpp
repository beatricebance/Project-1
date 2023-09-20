/***************************************/
/**************************************/
/* files:    soundGenerator.cpp       */
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

#include "soundGenerator.h"
#include <math.h>
#define NUMERATOR 3906.25  // Voir fonction note pour plus de précision

/* Commence l'initialisation des registres du Timer0 
** afin de produire un PWM qui permettra de générer un son
**
** Aucun pramètre
** Aucune valeur de retour
*/
void initialisationSound(){
    // Mode CTC du Timer0 avec TOP à OCRA 
    // avec génération de PWM
    TCCR0A |= (1 << WGM01) | (1 << COM0A0);

    // Une broche adjacente à celle du PWM (ici la broche 3 du PORTB)
    // est mise à 0 et connecté au fil noir
    PORTB &= ~(1 << 2);

}

/* Calcule la valeur à affecter à OCR0A pour 
** produire le PWM générant le son voulu
**                     
** param : la note MIDI d'une sonorité
** Aucune valeur de retour
**
** OCR0A = ( NUMERATOR / frequency) ) - 1 
** Avec NUMERATOR = F_CPU / (2 * prescaler)
** formule tirée de la documentation
**
** calcul de frequency à partir de la note MIDI 
** trouvé sur wikipedia
**
** NUMERATOR = 8000000 / ( 2 * 1024) = 3906.25
*/
void note(uint8_t noteMIDI){
    // Mettre le prescaler à 1024
    TCCR0B |= (1 << CS02) | (1 << CS00);

    double frequency = pow( 2, (( noteMIDI - 69 ) / 12 ) ) * 440;
    OCR0A = (uint8_t) (NUMERATOR / frequency) - 1;
}

/* Arrêter la sonorité en cours
**
** Aucun pramètre
** Aucune valeur de retour
*/
void stopSound() {
    // Pas de source d'horloge, le compteur s'arrête
    TCCR0B &= ~ ((1 << CS02) | (1 << CS00));
}