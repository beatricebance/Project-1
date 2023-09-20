/**
*   File: pb2.cpp
*   Date: 24/01/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/

/*   State table:
    State   Button  State+  DEL
    E0      1       E1      AMBER
    E0      0       E0      RED
    E1      1       E1      AMBER
    E1      0       E2      GREEN
    E2      1       E3      RED
    E2      0       E2      GREEN
    E3      1       E3      RED
    E3      0       E4      NONE
    E4      1       E5      GREEN
    E4      0       E4      NONE
    E5      1       E5      GREEN
    E5      0       E0      RED
*/



#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

bool isPressed(){
    bool state1 = PIND & 0x04;
    _delay_ms(10);
     bool state2 = PIND & 0x04;
     return state1 && state2;
}

enum Color{NONE, GREEN, RED, AMBER};

void changeLEDColor(Color c){
    if(c != AMBER){
        PORTA = c;        
    }
    else
    {
        PORTA = RED;
        _delay_ms(11);
        PORTA = GREEN;
        _delay_ms(1);// here we wait less than 11ms because we will already wait 10ms for the next isPressed to execute
      
    }
}

int main(){

    DDRD = 0x00; //Port D is an input (Button)
    DDRA = 0xff; //Port A is an output (LED+ connected to A1 and LED- connected to A2)

    enum DELState{
        E0, E1, E2, E3, E4, E5
    };
    
    DELState delState = E0;
    changeLEDColor(RED);


    while(true){

        switch(delState){
            case E0:
                if(isPressed()){
                    delState = E1;
                    changeLEDColor(AMBER);
                }
                break;
            case E1:
                if(!isPressed()){
                    delState = E2;
                    changeLEDColor(GREEN);
                }
                else changeLEDColor(AMBER); //We must repeat to get amber color
                break;
            case E2:
                if(isPressed()){
                    delState = E3;
                    changeLEDColor(RED);
                }
                break;
            case E3:
                if(!isPressed()){
                    delState = E4;
                    changeLEDColor(NONE);
                }
                break;
            case E4:
                if(isPressed()){
                    delState = E5;
                    changeLEDColor(GREEN);
                }
                break;
            case E5:
                if(!isPressed()){
                    delState = E0;
                    changeLEDColor(RED);
                }
                break;
        }
    }

    return 0;
}