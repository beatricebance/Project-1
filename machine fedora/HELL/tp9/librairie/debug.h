/*
  * Nom: 
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

# define DEBUG_PRINT(x) uart.afficherMessageDebogagee(char *x) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort

#endif

