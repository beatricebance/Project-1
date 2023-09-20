#include "USART.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
/**************************************/
/* files:    debug.h                  */
/* authors: *Ursule Joelle Kanmegne   */
/*          *Aymen-Alaeddine Zeghaida */
/*          *Michelle Sepkap Sime     */
/*          *Khadija Rekik            */
/* Date:     October 30, 2019         */
/*                                    */
/* Description : définition sur       */
/*  commande d'une macro utilisée     */
/*  à des fins de débogage            */
/**************************************/

#ifdef DEBUG
# define DEBUG_PRINT(x) transmissionUARTChaine(*x)
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif