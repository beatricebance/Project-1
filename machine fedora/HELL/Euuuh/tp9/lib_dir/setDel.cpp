//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
/**************************************/
/* files:    setDel.cpp               */
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

#include "setDel.h"


/******************************************************************************/
/* Modifie l etat eteint + couleur de la Del sur le port B aux broches 1 et 2 */        
/* Param  :   delState                                                        */
/*            Etat allumé ou eteint de la Del                                 */
/* Aucune valeur de retour                                                    */
/******************************************************************************/
void setDel(DelState delState){
  switch (delState){
    case off :
      PORTB = 0x00;
      break;

    case green :
      PORTB = GREEN;
      break;

    case red :
      PORTB = RED;
      break;

    case amber :
      PORTB = GREEN;
      _delay_ms(10);
      PORTB = RED;
      _delay_ms(10);
      break;
  }
}  

/******************************************************************************/
/* Allume plusieurs DELs à la fois                                            */        
/* Param  : delPosition                                                       */
/*            chacun de ses bits à '1' correspond à une DEL à allumer         */
/*            Exemple : 7 --> DELs 1, 2 et 3                                  */
/* Aucune valeur de retour                                                    */
/******************************************************************************/
void setManyDelOn(uint8_t delPosition ){
  PORTA |= delPosition;
}

/******************************************************************************/
/* Éteint plusieurs DELs à la fois                                            */        
/* Param  : delPosition                                                       */
/*            chacun de ses bits à '1' correspond à une DEL à éteindre        */
/*            Exemple : 7 --> DELs 1, 2 et 3                                  */
/* Aucune valeur de retour                                                    */
/******************************************************************************/
void setManyDelOff(uint8_t delPosition ){
  PORTA &= ~(delPosition);
}
