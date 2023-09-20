/*
  * Nom: 
  *BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  classe du bouton poussoir 
  *
 */

#ifndef DEL_H
#define DEL_H

#include <avr/io.h>

class DEL {
public:
	DEL();
  void allumerDEL(uint8_t couleur);
	void allumerDelAmbre();
	void clignoterDel(uint8_t nbRepetition, uint8_t couleur);


};

#endif /* DEL_H */

