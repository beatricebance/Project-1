// DESCRIPTION: DESCRIPTION: Programme contenant la definition de la classe          //
//              TRACKER_SENSOR qui permet le controle des trackers du robot pour     //
//              lui permettre de detecter les lignes noires.                         //
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _TRACKER_SENSOR_H_
#define _TRACKER_SENSOR_H_

#include "can.h"
#include "debug.hpp"
#include "def.hpp"

class TRACKER_SENSOR : private can
{
public:
  TRACKER_SENSOR(uint8_t posIR1, uint8_t posIR2, uint8_t posIR3, uint8_t posIR4, uint8_t posIR5);
  void debug(uint8_t IR);
  bool noirDetecte(uint8_t IR);

private:
  uint8_t posIR_[5];
};

#endif /* _TRACKER_SENSOR_H_ */