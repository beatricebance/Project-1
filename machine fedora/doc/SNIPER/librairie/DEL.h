/*
  * Noms:
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe DEL
  *
 */
#ifndef DEL_H
#define DEL_H
#define F_CPU 8000000UL
#include <avr/io.h>

class DEL {
public:
    void Del();
    void couleurAmbre(); 
    void couleurVerte(); 
    void couleurRouge(); 
    void delEteinte(); 

};

#endif 

