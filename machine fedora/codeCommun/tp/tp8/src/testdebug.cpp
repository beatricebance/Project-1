/*
 * Nom: TP8 
  *	BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  implemtation des fonctions de la classe UART
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */



/*


+--------------+----+-----------------+----------+
| etat present | A  | etat suivant    |sortie Z1 |  
+--------------+----+-----------------+----------+
| init         |  0 | init            | 0x01     |  
| init         |  1 | etat1           | 0x00     |  
| etat1        |  1 | etat2           | 0x00     |  
| etat2        |  1 | etat3           | 0x00     |  
| etat3        |  1 | etat4           | 0x00     |  
| etat4        |  1 | etat5           | 0x01     |  
+--------------+----+-----------------+----------+



*/
#define 	F_CPU   8000000UL
#define eteint 0x00
#define rouge 0x01 
#define vert 0x02
#include "UART.h"
#include "debug.cpp"
#include "DEL.h"
#include <avr/io.h>
#include <util/delay.h>


unsigned long compteur=0; // le compteur est initialise a 0.
                            // c'est un compteur de 32 bits

// Fonction qui effectue une lecture du bouton-poussoir avec l'antirebond 
 bool estappuyer(){
      if (PIND & 0x04){
        _delay_ms(10);
        return PIND & 0x04;
      }
      return false;
    };

enum ETAT{Rouge_1, Ambre, Vert_1, Rouge_2, ETEINT, Vert_2 } ;


int main()
{
  DDRB = 0xff; // PORT B est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  

   enum ETAT EtatCourant =  Rouge_1 ;

for(;;)  // boucle sans fin
  {
        switch (EtatCourant) {

            case Rouge_1 :
             PORTB = rouge;
             if (estappuyer()){
              EtatCourant = Ambre; 
              DEBUG_PRINT("Rouge_1\n");
                }
                                     
            break;

            case Ambre :
 
             while (estappuyer()){
                PORTB = vert;
                _delay_ms(10);
                PORTB = rouge;
                _delay_ms(5);
               
              }
              EtatCourant = Vert_1;  
              DEBUG_PRINT("Ambre\n");   
              break;
      
            case Vert_1 :
                PORTB = vert;
                if (estappuyer()){
                  EtatCourant = Rouge_2;
                  DEBUG_PRINT("Vert_1\n");
                }
                 
              break;
            
            case Rouge_2 :
               PORTB = rouge;
                 if (!estappuyer()){
                    EtatCourant = ETEINT;
                    DEBUG_PRINT("rouge\n");
                 };            

              break;

            case ETEINT :
                PORTB = eteint;
                if (estappuyer()){
                  EtatCourant = Vert_2;
                  DEBUG_PRINT("eteint\n");
                }
                 
              break;

            case Vert_2 :
               PORTB = vert;
               if (!estappuyer()){
                   EtatCourant = Rouge_1;
                   DEBUG_PRINT("Rouge_1\n");
                }
        }

  } 
  

  return 0; 
}

