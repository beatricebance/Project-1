// DESCRIPTION: Fichier contenant la definition de la classe SIRC       //
//              qui permet le controle du signal infrarouge par les deux robots,     //
//              c'est-a-dire la reception et la transmission du signal.              //
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _SIRC_H_
#define _SIRC_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.hpp"

enum COMMANDE : uint8_t
{
  C1 = 0x01,
  C2,
  C3,
  C4,
  C5,
  C6,
  C7,
  C8,
  C9
};
enum ADRESSE : uint8_t
{
  ROBOT = 0x01
};

class SIRC
{
public:
  SIRC();
  void initialiserTransmissionIR();
  void arreterTransmissionIR();
  void transmissionIR(const COMMANDE commande, const ADRESSE adresse);
  void initialiserReceptionIR();
  void arreterReceptionIR();
  bool receptionIR(uint8_t &commandeRecue, uint8_t &adresseRecue);
};

#endif /* _SIRC_H_ */