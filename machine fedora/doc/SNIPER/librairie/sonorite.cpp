/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description : Implementation des fonctions pour la sonorite
  *
 */
#include <avr/io.h>
#include <sonorite.h>


/* Constructeur de la classe Del */
SONORITE::SONORITE() {
}

// Fonctions permettant d'ajuster le pwm
void SONORITE :: ajustementPWM_sonorite (double frequence) {
	DDRB |= 0x04;
	double periode_active = 8000000/(2*frequence*256);
	OCR0A = periode_active;
	// mise à sortie OC0A sur comparaison
	// réussie en mode CTC, division d'horloge par 256
	TCCR0A |= (1<<WGM01) | (1<<COM0A0);
	TCCR0B |= (1<<CS02) ;
	TCNT0 = 0;
}

void SONORITE :: arreterSonorite () {
	OCR0A = 0;
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0 = 0;
}

void SONORITE :: jouer(uint8_t note) {
	if (note>=MIDI_110Hz && note<=MIDI_880Hz) {
		double frequence = FREQUENCE_LA*pow(2.0,((note-MIDI_440Hz)/12.0));
		ajustementPWM_sonorite(frequence);			
	}
}

// Compositions musicales
void SONORITE :: son_grave() {
	jouer(45);		
		
}

void SONORITE :: son_aigu() {
	jouer(81);

}
