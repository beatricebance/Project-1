#include "UART.h"
#include "memoire_24.h"
#define F_CPU 8000000
#include <util/delay.h>


int main()
{

    /*
        * Instantiation des classes
    */ 
    Memoire24CXXX maMemoire; // on declare un objet de type memoire
    UART uart; //on declare un objet de type usart


    /*
        * Initialisation des instances (memeoire et uart)
    */ 
      maMemoire.init();
      uart.initialisationUART();



  /*
        * Creation et initialisation des variables
   */ 

    uint8_t donnee;   // donnee lue
    uint8_t tableau[1]; // tableau qui contient les instructions
    uint8_t adresseInit = 0x00; // on initialise la position a l'adresse 0
    uint16_t tailleFichier=0; // taille du fichier
    


    tableau[0] = uart.lectureUART();
    maMemoire.ecriture(adresseInit, tableau[0]);
    tailleFichier =(tableau[0] << 8);
    tableau[0] = uart.lectureUART();
    _delay_ms(15);
    maMemoire.ecriture(adresseInit, tableau[0]);
    _delay_ms(15);
    tailleFichier |=tableau[0];


// A partir de l'adresse 2, on lit jusqu'a la fin du fichier
// car les deux premeier bits sont juste la taille du fichier
    for (uint16_t i=2; i < tailleFichier;i++) 
    {
        donnee = uart.lectureUART();
        _delay_ms(5);
        maMemoire.ecriture(i, donnee);
         _delay_ms(5);
    }
}
