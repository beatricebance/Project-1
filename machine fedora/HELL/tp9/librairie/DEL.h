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
  void allumerDEL(uint8_t couleur);
	void allumerDelAmbre();
  void clignoter(uint8_t couleur, uint16_t dureeAllumee, uint16_t dureeEteinte);

};

#endif /* DEL_H */

