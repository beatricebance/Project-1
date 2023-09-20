#include "couloir.h"

void Couloir::couloir()
{
        bool debut = true;
        SuiveurLigne suiveur;
        Roues roues;
        //boostDepart();
        // roues.ajustementRoues(35,35,AVANT);
        //_delay_ms(5);

        for (;;)
        {
                //ligne t-v
                while (US(1) || US(2) || US(3) || US(4) || US(5))
                {

                        suiveur.suiveurLigne();
                }

                while (US(3) == 0){
                while(US(2) == 0 || US(4) == 0){
                
                        if (debut)
                        {
                                roues.ajustementRoues(35, 0, GAUCHE);
                                _delay_ms(250);
                                debut = false;
                        }
                        roues.ajustementRoues(51, 61, AVANT);
                        _delay_ms(100);
                        if (US(5))
                        {
                                roues.ajustementRoues(70, 0, GAUCHE);
                                _delay_ms(250);
                        }

                        if (US(1))
                        {
                                roues.ajustementRoues(0, 70, DROITE);
                                _delay_ms(250);
                        }
                
                }
                }
                       // _delay_ms(100);
                //suiveur.suiveurLigne();
                        /* //roues.ajustementRoues(0,0,AVANT);
        //_delay_ms(300);
        //boostDepart;
        roues.ajustementRoues(25, 25, AVANT);
        _delay_ms(25);

        //ligne w-y
        while (US(1) || US(2) || US(3) || US(4) || US(5))
        {

                suiveur.suiveurLigne();
        }
        while (US(3) == 0)
        {
                roues.ajustementRoues(40, 0, GAUCHE);
                _delay_ms(25);
        }
        roues.ajustementRoues(25, 25, AVANT);
        _delay_ms(25);
        //boostDepart;
        //roues.ajustementRoues(60,60,AVANT);
        //_delay_ms(50);*/
                
        }
}
