/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139] 
  *Description :  DEbug permet de debugger le code en  faisant des affichages sur 
                    l'ecran de l'ordinarteur grace uart 
  *
 */

#include "UART.h"

// instanciation de la classe UART 
//qui permet de faire des affichage via RS32

UART uart;

#ifdef DEBUG

# define DEBUG_PRINT(message) uart.afficherMessageDebogage(message) 

#else

# define DEBUG_PRINT(messsage) do {} while (0) // code mort

#endif

