#include "communication.h"
#include "UART.h"
#include "memoire_24.h"


int main()
{
  
    Memoire24CXXX maMemoire; // on declare un objet de type memoire
    UART uart; //on declare un objet de type usart
    uint8_t donnee;
    uint16_t tableau[2];
    uint8_t adresseInit = 0x00; // on initialise la position a l'adresse 0
    uint8_t tailleFichier; 
    
    // on lit les 2 premiers octets pour connaitre la taille du fichier
    tableau[0] = uart.receptionUART();
    tableau[1] = uart.receptionUART();
    
    tailleFichier = tableau[1]; // donne la taille du fichier

    for (uint8_t i= adresseInit; i < tailleFichier;i++) // A partir de l'adresse 0, on lit jusqu'a la fin du fichier
    {
        donnee = uart.receptionUART();
        //_delay_ms(5);
        maMemoire.ecriture(i, donnee);
    }
}
