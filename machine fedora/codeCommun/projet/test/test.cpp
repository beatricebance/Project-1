/*
  * Noms: 
  * BANCE HALIMA DEDE BEATRICE [1926066] 
  * BOCAR DIALLO [1859433] 
  * Ramzi Belbahri [1963293]
  * Haddouni Abderraouf [1958139]
  *Description :  test de la librairie
  *
 */

#define F_CPU 8000000UL
#define CycleParSeconde 7813 
#define DEMO_DDR	DDRC // `Data Direction Register' AVR occup� par l'aff.
#define DEMO_PORT	PORTC // Port AVR occup� par l'afficheur

#include <stdlib.h>
#include <avr/io.h>
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#include <math.h> 
#include "DEL.h"
#include "communication.h"
#include "moteur.h"
#include "Bouton.h"


int main()
{

  DEL del;
  COMMUNICATION com;
  Moteur moteur;
  BOUTON bouton;


   //com.initialisation (com.PORT_SORTIE, com.PORT_SORTIE, com.PORT_SORTIE, com.PORT_ENTREE);
     //del.Couleur(com.VERT);

DDRD =0xff;
  // com.attendre(10000);
  // del.Couleur(com.ROUGE);

  // com.attendre(1000);
  // del.Couleur(com.ROUGE);
  // com.attendre(1000);
  // del.clignoter(2,com.VERT);
  // del.Couleur(com.ETEINT);
  // com.attendre(1000);
  // del.clignoter(2,com.ROUGE);
  // com.attendre(1000);
  // del.Couleur(com.ETEINT); 

     
//   moteur.moteur();
//   moteur.avancer(128.0,128.0);
//  com.attendre(5000);
//   moteur.reculer(128.0,128.0);
//   com.attendre(5000);
  // moteur.tournerGauche(128.0);
  // com.attendre(5000);
  // moteur.tournerDroite(128.0);
  // com.attendre(5000);
  // moteur.arreterMoteur();


	// Cr�ation de l'objet (l'afficheur est connect� sur le port DEMO_PORT)
	LCM disp(&DEMO_DDR, &DEMO_PORT);
	// Affichage d'une cha�ne sur la premi�re ligne, � la case 2
	disp.write("COULOIR:",1);



  // Ajout d'une sous-cha�ne � la suite
	disp << "Distance";

// 	//com.attendre(10000);

// 	// Nettoyage de l'affichage
// //	disp.clear();




 
  return 0; 
}


