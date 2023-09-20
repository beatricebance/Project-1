
#ifndef _PWM_H
#define _PWM_H
#include <util/delay.h>
#include <avr/io.h> 

extern const int CENTRE,DROITE,GAUCHE;
enum Couleur {eteint,vert,rouge};
void maj ();
void arret ();
void setPuissance (double p);
void accelerer (float a) ;
void tournerRayon (float r, int sens);
void attendre (int ms);
void tournerDegre (uint16_t degre, int sens);
void setColor(int couleur);
void verification(bool estOk);
void eteindreDel();
void initialisation ();
void clearPWM();
void setPWMA (int p);
void setPWMB (int p);
#endif