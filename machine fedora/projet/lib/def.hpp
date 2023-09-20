// DESCRIPTION: Ce fichier contient toutes les declarations communes aux      //
//              autres fichiers .h ou .hpp                                    //
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEF_HPP_
#define _DEF_HPP_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum COULEUR
{
    ETEINT,
    ROUGE,
    VERT
};
enum PORT_ENUM
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D
};
enum ORIENTATION_BROCHE
{
    VERTICALE = 0x1,
    HORIZONTALE = 0x2
};
enum BROCHE_TYPE
{
    UNDEL,
    DEUXDELS,
    GND
};
enum POS_ROBOT
{
    HORSTRACK,
    IR1,
    IR2,
    IR3,
    IR4,
    IR5,
    IR4_ET_3,
    IR2_ET_3,
    IR3_ET_4_ET_5,
    IR3_ET_2_ET_1,
    TOUTES
};

#endif /* _DEF_HPP_ */