// DESCRIPTION: Programme contenant la definition de la classe BROCHE_DEL qui //
//              permet de changer la couleur de la DEL (eteint, rouge, vert   //
//				et ambre) peu importe le port et l'orientation de branchement //
//				du connecteur.												  //
////////////////////////////////////////////////////////////////////////////////

#ifndef _BROCHE_DEL_H_
#define _BROCHE_DEL_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "delmanager.hpp"
#include "debug.hpp"
#include "def.hpp"

class BROCHE_DEL
{
  public:
	BROCHE_DEL(PORT_ENUM port, uint8_t posConnecteur, BROCHE_TYPE type, ORIENTATION_BROCHE orientation = VERTICALE);
	void eteindreDel(uint8_t numeroDel);
	void allumerDel(uint8_t numeroDel);
	bool estAllumeDel(uint8_t numeroDel) const;

  private:
	uint8_t posConnecteur_;
	ORIENTATION_BROCHE orientation_;
	PORT_ENUM port_;
	BROCHE_TYPE type_;
	bool delUnAllume, delDeuxAllume;
	uint8_t eteindreDelModifierPort(uint8_t valeurPort, uint8_t numeroDel);
	uint8_t allumerDelModifierPort(uint8_t valeurPort, uint8_t numeroDel);
	uint8_t ddrModifierPort(uint8_t valeurPort);
};

#endif /* _BROCHE_DEL_H_ */