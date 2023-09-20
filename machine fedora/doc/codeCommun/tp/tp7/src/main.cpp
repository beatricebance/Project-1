/*
  * Nom: BANCE HALIMA DEDE BEATRICE [1926066] et BOCAR DIALLO [1859433] et ...
  * 
  *Description : 
 */

/*
  UTILISATION DE LA LIBRAIRIE 
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include "DEL.h"

int main()
{
DDRB = 0Xff;
  for (;;)
  {
    DEL del;

     del.allumerDelAmbre();
 }    
      
 
  
  return 0;
}