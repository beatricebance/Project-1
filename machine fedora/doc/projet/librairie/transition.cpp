#include "transition.h"



void Transition :: TransitionSection(){


 if( (CAP_1 && CAP_2 && CAP_3) || (CAP_3 && CAP_4 && CAP_5) || (CAP_1 && CAP_2 && CAP_3 && CAP_4 && CAP_5)  || (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)) ){
                                        
       while ((CAP_1 && CAP_2 && CAP_3) || (CAP_3 && CAP_4 && CAP_5) || (CAP_1 && CAP_2 && CAP_3 && CAP_4 && CAP_5)  || (!(CAP_1) && !(CAP_2) && !(CAP_3) && !(CAP_4) && !(CAP_5)) ){
                ajustementRoues(40,0,AVANT);
                _delay_ms(400);
        }
        

    sectionParcouru ++;

                                            
 }

}