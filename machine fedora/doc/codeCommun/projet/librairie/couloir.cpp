#include "couloir.h"

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupe par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupe par l'afficheur

void Couloir::Le_couloir()
{

        // Creation de l'objet
	LCM disp(&DEMO_DDR, &DEMO_PORT);


        SuiveurLigne suiveur;
        Roues R;


 // ligne A B
        while (US(1) || US(2) || US(3) || US(4) || US(5)){
                suiveur.suiveurLigneCouloire();
                      disp.clear();
                disp.write("A B",1);
        }
// ligne B G

       while ( !US(2) && !US(3) && !US(4)){
               while (debut)
                {
                        R.ajustementRoues(35, 0, AVANT);
                        _delay_ms(250);
                        debut = false;
                 disp.clear();
                disp.write("DEBUT",1);
                }
                 while (US(5))
                {
                        R.ajustementRoues(50, 0, AVANT);
                        _delay_ms(200); //250
                        disp.clear();
                disp.write("CAPTEUR5",1);
                }
                while (US(1))
                {
                        R.ajustementRoues(0, 50, AVANT);
                        _delay_ms(200); //250
                         disp.clear();
                disp.write("CAPTEUR1",1);
                }

       }

// G H
  while (US(1) || US(2) || US(3) || US(4) || US(5)){

        disp.clear();
        disp.write("GH",1);

        if (US(5) && US(1)){
                while (!US(3)){

                        R.ajustementRoues(0,40,AVANT);
                } 

                
        }
        R.ajustementRoues(0,0,AVANT); 
                _delay_ms(900);

        while (US(1) || US(2) || US(3) || US(4) || US(5)){
                disp.clear();
                disp.write("Ajustement",1);        

               suiveur.suiveurLigneCouloire();
        }
                            
  }


R.ajustementRoues(0,0,AVANT);

disp.clear();
disp.write("THE END",1);
}