#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif


#define CAP_1  PINA & 1<<0
#define CAP_2  PINA & 1<<1
#define CAP_3  PINA & 1<<2
#define CAP_4  PINA & 1<<3
#define CAP_5  PINA & 1<<4


#include <avr/io.h>
#include <util/delay.h> 
#include "roues.h"


class Transition : public Roues {  // heritage multiple de suiveuligne et roues donc pas besoin d'instance

public:
         void TransitionSection();
         volatile uint8_t sectionParcouru = 0 ;
};
#endif