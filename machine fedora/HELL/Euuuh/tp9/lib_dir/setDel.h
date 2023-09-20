//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
/**************************************/
/* files:    setDel.h                 */
/* authors: *Ursule Joelle Kanmegne   */
/*          *Aymen-Alaeddine Zeghaida */
/*          *Michelle Sepkap Sime     */
/*          *Khadija Rekik            */
/* Date:     October 21, 2019         */
/*                                    */
/**************************************/
/*                                    */
/* Spécifications : PORT A utilisé    */
/* pour allumer ou éteindre plusieurs */
/* DELs à la fois                     */
/* La DEL 1 est connectée aux         */
/* broches 1 et 2 de ce port.         */  
/**************************************/
/**************************************/

#ifndef SET_DEL_H
#define SET_DEL_H

#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#define RED 0x02
#define GREEN 0x01


/** 
* Etats de la del
*/
enum DelState{ off, green, red, amber};

// Modifie l'état de la DEL
void setDel(DelState delState);

// Allume plusieurs DELs à la fois
void setManyDelOn(uint8_t delPosition );

// Éteint plusieurs DELs à la fois
void setManyDelOff(uint8_t delPosition );


#endif /* SET_DEL_H */