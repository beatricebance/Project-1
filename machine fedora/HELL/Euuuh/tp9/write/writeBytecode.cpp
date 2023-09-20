#include <avr/io.h>
#define F_CPU 8000000
#include <../lib_dir/debug.h>
#include <../lib_dir/memoire_24.h>
#include <../lib_dir/USART.h>
#include <avr/interrupt.h>

//l'octet recu
volatile uint8_t readByte;
Memoire24CXXX memory;
//addresse de debut d'ecriture dans la memoire
volatile uint8_t startAddress;

/*routine appelee des qu il y a un octet qui est pret a etre recu 
et cette valeur est donc reçue et ecrite en memoire
*/
ISR(USART0_RX_vect){
    readByte = receptionUART();
    memory.ecriture(startAddress, readByte);
    ++startAddress;
}

void initialisation ( void ) {

    // cli est une routine qui bloque toutes les interruptions.
    cli ();

    // Initialiser l'adresse à partir de laquelle on va écrire dans la mémoire
    startAddress = 0;

    // Ajuster le registre UCSR0B pour générer une interruption
    // lorsqu'un octet est prêt à être reçu 
    UCSR0B |= (1 << RXCIE0);

    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

int main(){
    initialisation();
    initialisationUART();
    for(;;){}
}
