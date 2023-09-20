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
//	arreterSonorite();
//	attendre(ATTENTE_LONG);
	if (note>=MIDI_110Hz && note<=MIDI_880Hz) {
		double frequence = FREQUENCE_LA*pow(2.0,((note-MIDI_440Hz)/12.0));
		ajustementPWM_sonorite(frequence);			
	}
}

// Compositions musicales
void SONORITE :: tune_NokiaRingtone () {
	jouer(76);		// mi
	attendre(TEMPS_DEMI);
	jouer(74);		// re
	attendre(TEMPS_DEMI);
	jouer(66);		// fa diese
	attendre(TEMPS_PLEIN);
	jouer(68);		// sol diese
	attendre(TEMPS_PLEIN);
	
	jouer(73);		// do diese
	attendre(TEMPS_DEMI);
	jouer(71);		// si
	attendre(TEMPS_DEMI);
	jouer(62);		// re
	attendre(TEMPS_PLEIN);
	jouer(64);		// mi
	attendre(TEMPS_PLEIN);
	
	jouer(71);		// si
	attendre(TEMPS_DEMI);
	jouer(69);		// la
	attendre(TEMPS_DEMI);
	jouer(61);		// do diese
	attendre(TEMPS_PLEIN);
	jouer(64);		// mi
	attendre(TEMPS_PLEIN);
	
	jouer(69);		// la
	attendre(TEMPS_DOUBLE);	
		
	arreterSonorite();
}

void SONORITE :: tune_StarWars () {
	for (uint8_t i = 0; i < 3; i++) {
		jouer(43);		// SOL
		attendre(TEMPS_TIER*2);
	}	
	for (uint8_t i = 0; i < 2; i++ ) {
		jouer(60);		// do
		attendre(TEMPS_DOUBLE*2);
		jouer(67);		// sol
		attendre(TEMPS_DOUBLE*2);
		
		for (uint8_t j = 0; j < 2; j++) {		
			jouer(65);	// fa
			attendre(TEMPS_TIER*2);
			jouer(64);	// mi
			attendre(TEMPS_TIER*2);
			jouer(62);	// ré
			attendre(TEMPS_TIER*2);
			jouer(72);	// do^
			attendre(TEMPS_DOUBLE*2);
			jouer(67);	// sol
			attendre(TEMPS_PLEIN*2);
		}
		jouer(65);		// fa
		attendre(TEMPS_TIER*2);
		jouer(64);		// mi
		attendre(TEMPS_TIER*2);
		jouer(65);		// fa
		attendre(TEMPS_TIER*2);
		jouer(62);		// ré
		attendre(TEMPS_DOUBLE*2);
		jouer(43);		// SOL
		attendre(TEMPS_PLEIN*2);
		jouer(43);		// SOL
		attendre(TEMPS_DEMI*2);		
	}
	jouer(45);			// LA
	attendre((TEMPS_PLEIN+TEMPS_DEMI)*2);
	jouer(45);			// LA
	attendre(TEMPS_DEMI*2);
	jouer(65);			// fa
	attendre(TEMPS_QUART*2);
	jouer(64);			// mi
	attendre(TEMPS_QUART*2);
	jouer(62);			// ré
	attendre(TEMPS_QUART*2);
	jouer(60);			// do
	attendre(TEMPS_QUART*2);
	
	jouer(60);			// do
	attendre(TEMPS_TIER*2);
	jouer(62);			// ré
	attendre(TEMPS_TIER*2);
	jouer(64);			// mi
	attendre(TEMPS_TIER*2);	
	jouer(62);			// ré
	attendre(TEMPS_PLEIN*2);
	jouer(45);			// LA
	attendre(TEMPS_DEMI*2);
	jouer(47);			// SI
	attendre(TEMPS_PLEIN*2);
	jouer(43);			// SOL
	attendre(TEMPS_PLEIN*2);
	jouer(43);			// SOL
	attendre(TEMPS_DEMI*2);
	
	jouer(45);			// LA
	attendre((TEMPS_PLEIN+TEMPS_DEMI)*2);
	jouer(45);			// LA
	attendre(TEMPS_DEMI*2);
	jouer(65);			// fa
	attendre(TEMPS_QUART*2);
	jouer(64);			// mi
	attendre(TEMPS_QUART*2);
	jouer(62);			// ré
	attendre(TEMPS_QUART*2);
	jouer(60);			// do
	attendre(TEMPS_QUART*2);
	
	jouer(67);			// sol
	attendre(TEMPS_PLEIN*2);
	jouer(62);			// ré
	attendre(TEMPS_DOUBLE*2);
	arreterSonorite();
	attendre(TEMPS_PLEIN*2);
	jouer(43);			// SOL
	attendre(TEMPS_DEMI*2);
	
	jouer(45);			// LA
	attendre((TEMPS_PLEIN+TEMPS_DEMI)*2);
	jouer(45);			// LA
	attendre(TEMPS_DEMI*2);
	jouer(65);			// fa
	attendre(TEMPS_QUART*2);
	jouer(64);			// mi
	attendre(TEMPS_QUART*2);
	jouer(62);			// ré
	attendre(TEMPS_QUART*2);
	jouer(60);			// do
	attendre(TEMPS_QUART);
	
	jouer(60);			// do
	attendre(TEMPS_TIER*2);
	jouer(62);			// ré
	attendre(TEMPS_TIER*2);
	jouer(64);			// mi
	attendre(TEMPS_TIER*2);	
	jouer(62);			// ré
	attendre(TEMPS_PLEIN*2);
	jouer(45);			// LA
	attendre(TEMPS_DEMI*2);
	jouer(47);			// SI
	attendre(TEMPS_PLEIN*2);
	jouer(43);			// SOL
	attendre(TEMPS_PLEIN*2);
	jouer(43);			// SOL
	attendre(TEMPS_DEMI*2);
	
	jouer(72);			// do^
	attendre(TEMPS_PLEIN*2);
	jouer(70);			// si bemol
	attendre(TEMPS_DEMI*2);
	jouer(68);			// la bemol
	attendre(TEMPS_PLEIN*2);
	jouer(67);			// sol
	attendre(TEMPS_DEMI*2);
	jouer(65);			// fa
	attendre(TEMPS_PLEIN*2);
	jouer(63);			// mi bemol
	attendre(TEMPS_DEMI*2);
	jouer(62);			// ré
	attendre(TEMPS_PLEIN*2);
	jouer(60);			// do
	attendre(TEMPS_DEMI*2);
	
	jouer(67);			// sol
	attendre(TEMPS_PLEIN*2);
	for (uint8_t i = 0; i < 3; i++) {
		jouer(43);		// SOL
		attendre(TEMPS_TIER*2);
	}	
	jouer(43);			// SOL
	attendre(TEMPS_PLEIN*2);
	jouer(43);			// SOL
	attendre(TEMPS_DEMI*2);	
	for (uint8_t i = 0; i < 2; i++) {
		jouer(43);		// SOL
		attendre(TEMPS_QUART*2);
	}	
		
	jouer(45);			// LA
	attendre((TEMPS_PLEIN+TEMPS_DEMI)*2);
	jouer(48);			// DO
	attendre(TEMPS_PLEIN*2);
	jouer(65);			// fa
	attendre(TEMPS_PLEIN*2);
	jouer(62);			// ré
	attendre(2*TEMPS_DOUBLE*2);
	for (uint8_t i = 0; i < 3; i++) {
		jouer(43);		// SOL
		attendre(TEMPS_TIER*2);
	}
	
	for (uint8_t i = 0; i < 2; i++ ) {
		jouer(60);		// do
		attendre(TEMPS_DOUBLE*2);
		jouer(67);		// sol
		attendre(TEMPS_DOUBLE*2);
		
		for (uint8_t j = 0; j < 2; j++) {		
			jouer(65);	// fa
			attendre(TEMPS_TIER*2);
			jouer(64);	// mi
			attendre(TEMPS_TIER*2);
			jouer(62);	// ré
			attendre(TEMPS_TIER*2);
			jouer(72);	// do^
			attendre(TEMPS_DOUBLE*2);
			jouer(67);	// sol
			attendre(TEMPS_PLEIN*2);
		}
		jouer(65);		// fa
		attendre(TEMPS_TIER*2);
		jouer(64);		// mi
		attendre(TEMPS_TIER*2);
		jouer(65);		// fa
		attendre(TEMPS_TIER*2);
		jouer(62);		// ré
		attendre(TEMPS_DOUBLE*2);
		jouer(43);		// SOL
		attendre(TEMPS_PLEIN*2);
		jouer(43);		// SOL
		attendre(TEMPS_DEMI*2);		
	}
	
	jouer(60);			// do
	attendre(5*TEMPS_PLEIN*2);
	for (uint8_t i = 0; i < 3; i++) {
		jouer(60);		// do
		attendre(TEMPS_TIER*2);
	}
	jouer(60);			// do
	attendre(TEMPS_PLEIN*2);
	
	arreterSonorite();		
}
