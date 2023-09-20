/**
*   File: pb1.cpp
*   Date: 24/01/2018
*   Authors: Hamdi Mansour 1889278 , Marc-Antoine Jacob 1889638
*/

/*   State table:
    State   Button  State+  DEL
    E0      1       E1      0
    E0      0       E0      0
    E1      1       E2      0
    E1      0       E1      0
    E2      1       E3      0
    E2      0       E2      0
    E3      1       E4      0
    E3      0       E3      0
    E4      1       EON     1
    E4      0       E4      0
    EON     X       E0      1
*/

/*  to avoid problems with the button held for a long time, we created a pulse generator
    state table:
    State   Button  State+
    E0      1       E1
    E0      0       E0
    E1      1       E1
    E1      0       E0 
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

int main(){

    DDRD = 0x00; //Port D is an input (Button)
    DDRA = 0xff; //Port A is an output (LED+ connected to A1 and LED- connected to A2)

    enum DELState{
        OFF,ON
    };

    enum ButtonState{
        PRESSED, RELEASED
    };
    
    DELState delState = OFF;
    ButtonState buttonState = RELEASED;
    uint8_t pressCount = 0;


    while(true){

        switch(buttonState){
            case RELEASED:
                if(isPressed()){
                    pressCount++;
                    buttonState = PRESSED;
                }
                break;
            case PRESSED:
                if(!isPressed()){
                    buttonState = RELEASED;
                }
                break;
        }

        switch(delState){
            case OFF:
                if(pressCount==5){
                    delState = ON;
                    PORTA = 0x01;
                }
                break;
            case ON:
                _delay_ms(1000);
                PORTA = 0x00;
                delState = OFF;
                pressCount = 0;
                break;
        }
    }

    return 0;
}