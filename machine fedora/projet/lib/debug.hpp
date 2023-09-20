#include "uart.hpp"

#ifdef DEBUG
#define DEBUG_PRINT(message) UART::afficherMessageDebogage(message);
#define DEBUG_NOMBRE(nombre) UART::transmissionNombre8(nombre)
#define DEBUG_NOMBRE16(nombre) UART::transmissionNombre16(nombre)
#else
#define DEBUG_PRINT(message) do {} while (0)
#define DEBUG_NOMBRE(nombre) do {} while (0)
#define DEBUG_NOMBRE16(nombre) do {} while (0)
#endif