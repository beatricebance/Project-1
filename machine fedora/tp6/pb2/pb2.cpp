/* 
 * Nom du fichier : Probleme2.cpp
 * Auteur : Hakim Mektoub (1956925), Malek Demdoum (1887467)
 * Date : 11 Octobre 2019
 * Description : On doit changer la couleur de la DEL pour qu'elle reagisse a la photoresistance. Si la lumiere est faible, la DEL est verte, si elle est ambiante elle est ambre
 * et si elle est forte elle est rouge
 *  notre del libre est liee aux PORTS 0 et 1 de PORTB
 *Notre fil rouge/noir est lie comme suit: rouge -> Vcc, noir -> Ground
 *Notre fil bleu/brun est lie au Ports A0 et A1
 *On a trouve nos valeurs minimales et maximales avec une methode experimentale. On a converti les voltages qu'on a trouve en une valeur sur 255(vu que c'est sur 8 bits) avec les formules suivantes
 *MIN = 1.87 V donc 1.87/5 * 255 = 95
 *MAX = 4.4  V donc 4.4/5 *255 = 224
*/


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"


const uint8_t ENTREE = 0x00;
const uint8_t SORTIE = 0xff;
const uint8_t VERTE = 0b01;
const uint8_t ROUGE = 0b10;
const uint8_t ETEINTE = 0b00;

const uint8_t VOLTAGE = 5;

int main() {
	
    DDRA = ENTREE; // on initialise nos ports, le A en entree et le B en sortie
    DDRB = SORTIE;

	can Convertisseur; // On cree un objet de type can
	
	while (1) {
		
		//On decalle de 2 bits vu que la lecture nous donne 10 bits mais on veut seulement les 8 les plus significatifs, Ce sont les bits de poids faible qui sont significatifs
		uint8_t i = (Convertisseur.lecture( PINA ) >> 2 );
		
		// La DEL devient verte lorsque la lumière est faible.
		if (i < 110) // On considere tout ce qui est plus petit que 110 comme etant faible vu que la valeur minimale qu'on peut avoir est de 95


        
			PORTB = VERTE; 
		
		// La DEL devient ambrée lorsqu'il s'agit de la lumière ambiante.
		else if (i >= 110 && i < 223) {
			PORTB = ROUGE;
			_delay_ms(5);
			PORTB = VERTE;
			_delay_ms(10);
		}
		
		// La DEL devient rouge lorsque la lumière est trop forte (i > 223).
		else
			PORTB = ROUGE;
	}
}