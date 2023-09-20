#ifndef _DEL_MANAGER_H_
#define _DEL_MANAGER_H_

#include "brochedel.hpp"
#include "def.hpp"

class BROCHE_DEL;

class DEL_Manager
{
public:
  DEL_Manager();
  void allumerDEL(uint8_t numero);
  void eteindreDEL(uint8_t numero);
  void ajouterBROCHE(BROCHE_DEL *broche);
  bool delEstAllume(uint8_t numero) const;

private:
  BROCHE_DEL *listeBROCHE[4];
  uint8_t nbBroches = 0;
};

#endif /* _DEL_MANAGER_H_ */