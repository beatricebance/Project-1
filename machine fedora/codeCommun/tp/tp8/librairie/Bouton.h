/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du bouton poussoir 
  *
 */
#ifndef BOUTON_H
#define BOUTON_H

#include <avr/io.h> 

class BOUTON {
public:
	BOUTON();
	bool estAppuyer();
  void initialisation(void);


};
#endif