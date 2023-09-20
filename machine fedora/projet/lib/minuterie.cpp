#include "minuterie.hpp"

volatile bool minuterieExpiree = false;

/**
 * \brief Constructeur par défaut.
 */
Minuterie::Minuterie()
{
}

/**
 * \fn void Minuterie::partirMinuterie(uint16_t duree)
 * \brief Fonction qui permet de configurer et partir la minuterie interne du MCU.
 * \param[in] duree la duree de la minuterie que l'on veut avant le déclenchement de l'interruption.
 */
void Minuterie::partirMinuterie(uint16_t duree)
{
     TCNT1 = 0; // Compter à partir de 0.
     OCR1A = duree;
     TCCR1A |= (1 << COM1A1) | (1 << COM1A0);            // Quand TCNT1 = OCR1A => OC1A =  1.
     TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); //activer le mode CTC + déviser l'horloge par 1024.
     TIMSK1 |= (1 << OCIE1A);                            // un masque pour activer l'interruption quand OC1A = 1.
}

ISR(TIMER1_COMPA_vect) // routine d'interruption liée à la minuterie.
{
     minuterieExpiree = true;
}

/**
 * \fn void Minuterie::delaisMinuterie_cs(uint16_t duree_cs)
 * \brief Fonction qui permet d'insérer un délais en cs.
 * \param[in] duree_cs la duree en cs du délais que l'on veut insérer dans le programme. 
 */
void Minuterie::delaisMinuterie_cs(uint16_t duree_cs)
{
     partirMinuterie(duree_cs * 0x4E); // 0x4E = 1 cs (centiseconde) avec une horloge à 8 MHz/1024.
     do
     {
     } while (!minuterieExpiree);
}

/**
 * \fn void Minuterie::arreterMinuterie(void)
 * \brief Fonction qui permet d'arrêter les interruptions liées à la minuetrie.
 */
void Minuterie::arreterMinuterie()
{
     minuterieExpiree = false;
     TCNT1 = 0;
     OCR1A = 0;
     TCCR1A &= ~(1 << COM1A1) & ~(1 << COM1A0);
     TCCR1B &= ~(1 << WGM12) & ~(1 << CS12) & ~(1 << CS10);
     TIMSK1 &= ~(1 << OCIE1A);
}