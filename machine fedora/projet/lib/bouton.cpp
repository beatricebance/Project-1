#include "bouton.hpp"

volatile uint8_t compteur = 0;

ISR(INT0_vect)
{
     _delay_ms(30); // delais entirebond.
     if (PIND & 0x04)
     {
          if (compteur == 9)
               compteur = 1;
          else
               compteur++;

          TCNT1 = 0; // Compter à partir de 0
     }
     EIFR |= (1 << INTF0); // si une seconde interruption intervient durant celle courante,
                           // l'AVR s'en souvient et ISR sera executée après l'interruption courante.
}

/**
 * \brief constructeur de la classe boutton
 */

Bouton::Bouton()
{
     DDRD &= ~(1 << PORTD2); // PORT D2 est en mode entree
     cli();
     EIMSK |= (1 << INT0);                 // activation de l'interruption externe du bouton poussoir (INT0 = port D2).
     EICRA |= (1 << ISC00) | (1 << ISC01); // seulement front montant du port D2 provoque une interruption.
     sei();
}

/**
 *\fn void Boutton::IRControl()
 *\brief fonction qui gère l'état du bouton en envoyant un signal infrarouge après 2 secondes si l'utilisateur n'a pas réappuyé sur le boutton
*/

void Bouton::IRControl()
{
     while (1)
     {
          switch (etat_)
          {
          case INIT:
          {
               if (compteur != etat_)
               {
                    etat_ = ATTENTE;
                    temps_.partirMinuterie(0x3D09); // Partir la minuterie pour 2 secondes.
                    break;
               }
               break;
          }
          case ATTENTE:
          {
               if (minuterieExpiree)
               {
                    temps_.arreterMinuterie();
                    sirc_.initialiserTransmissionIR();
                    sirc_.transmissionIR((COMMANDE)compteur, ROBOT);
                    compteur = 0;
                    etat_ = INIT;
                    return;
               }
               break;
          }
          }
     }
}