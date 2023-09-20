// DESCRIPTION: Programme contenant la definition de la classe UART qui     //
//              permet la transmission ou la reception d'une donnee de/vers // 
//              la carte de/vers le PC.                                     //
//////////////////////////////////////////////////////////////////////////////

#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>
#include <string.h>
#include "def.hpp"

class UART
{
   public:
     UART();
     static void transmission(uint8_t donnee);
     static void transmissionNombre8(uint8_t nombre8);
     static void transmissionNombre16(uint16_t nombre16);
     uint8_t telechargement();
     static void afficherMessageDebogage(const char *message);
};

#endif /* _UART_H_ */