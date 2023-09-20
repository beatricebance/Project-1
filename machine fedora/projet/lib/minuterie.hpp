#ifndef _MINUTERIE_H_
#define _MINUTERIE_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile bool minuterieExpiree;

class Minuterie
{
   public:
     Minuterie();
     void partirMinuterie(uint16_t duree);
     void delaisMinuterie_cs(uint16_t duree_cs);
     void arreterMinuterie();
};

#endif /* _MINUTERIE_H_ */