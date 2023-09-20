/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  Fichier DEbug
  *
 */

#include "UART.h"
UART uart;
#ifdef DEBUG

# define DEBUG_PRINT(message) uart.afficherMessageDebogage(message) 

#else

# define DEBUG_PRINT(messsage) do {} while (0) // code mort

#endif

