#include "UART.h"


#ifdef DEBUG
UART uart;
#define DEBUG_PRINT(message) uart.afficherMessageDebogage((char*)message);
#else
#define DEBUG_PRINT(message) do {} while (0)
#endif
