/*
 * Auteurs: Alexandre D'AMBOISE , Bineta DIENG, Olivier LEBEL,Papa Demba TALL
 * Nom: moteur.h
 * Date 1 Novembre 2015
 * Description:  Cette classe represente le moteur
 */

#ifndef DEF_MOTEUR
#define DEF_MOTEUR
#include <util/delay.h>
#include <avr/io.h> 
#define F_CPU 8000000UL

class Moteur
{
public :
    
    void moteur();
    void ajustementPWM(double vitesseDroite, double vitesseGauche);
    void avancer(double vitesseDroite, double vitesseGauche);
    void reculer(double vitesseDroite, double vitesseGauche);
    void tournerGauche(double vitesseGauche);
    void tournerDroite(double vitesseDroite);
    void arreterMoteur();
    
    
private :
    
    double vitesseRoueDroite_;
    double vitesseRoueGauche_;

};
#endif



