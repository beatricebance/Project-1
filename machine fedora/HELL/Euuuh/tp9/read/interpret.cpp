#include <avr/io.h>
#include <../lib_dir/debug.h>
#include <../lib_dir/memoire_24.h>
#include <../lib_dir/USART.h>
#include <../lib_dir/setDel.h>
#include <../lib_dir/PWMgenerator.h>
#include <../lib_dir/soundGenerator.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define INSTRUCTION_SIZE 0x02 

Memoire24CXXX memory;
uint16_t instructionAdress = 0x02;
/*
definition des opcodes du bytecode
*/
enum instructions{
    dbt = 0x01,
    att = 0x02,
    dal = 0x44,
    det = 0x45,
    sgo = 0x48,
    sar = 0x09,
    mar1 = 0x60,
    mar2 = 0x61,
    mav = 0x62,
    mre = 0x63,
    trd = 0x64,
    trg = 0x65,
    dbc = 0xC0,
    fbc = 0xC1,
    fin = 0xFF
};

// Prototype de la fonction interpret pour permettre à loop de l'appeler
uint8_t interpret(uint16_t& address);

/*
** fonction qui permet d'interpréter une boucle 
** et toutes les instructions contenues dans la boucle
** depuis le bytecode
** 
** param : address
**          Addresse courante, celle de la boucle;
            Contient l'adresse de fbc à la fin de la boucle
** param : count
**          Nombre d'iterations de la boucle - 1
** Aucune valeur de retour
*/
void loop (uint16_t& address, uint8_t count) {
	uint8_t loopAddress = address + 2;  // Sauvegarde de l'addresse de la premiàre instruction de la boucle
	uint8_t iterations = count + 1;
	for (uint8_t i = iterations; i > 0; --i) {
		address = loopAddress;
		while (interpret(address) != fbc) {
			address += 2;
		}
	}
}

/*
** Fonction permettant d'interpréter une instruction du bytecode
** param : address
**         Adresse de l'instruction à interpréter
** retour : uint8_t
**         L'instruction qui vient d'être interprétée
*/
uint8_t interpret(uint16_t& address){

    uint8_t instruction[INSTRUCTION_SIZE];
    memory.lecture(address, (uint8_t*)instruction, INSTRUCTION_SIZE);
    uint8_t opcode = instruction[0];
    uint8_t operand = instruction[1];

    switch(opcode){
                case att:
                    for(uint8_t i =0; i < operand ;i++)
                        _delay_ms(25);
                    break;
                case dal:
                    setManyDelOn(operand);
                    break;
                case det:
                    setManyDelOff(operand);
                    break;
                case sgo:
                    note(operand);
                    break;
                case sar:
                    stopSound();
                    break;
                case mar1:  
                case mar2:
                    stopMotion();
                    break;
                case mav:
                    goForward(operand, operand);
                    break;
                case mre:
                    goBackward(operand, operand);
                    break;
                case trd:
                    turnRight(90);
                    break;
                case trg:
                    turnLeft(90);
                    break;  
                case dbc:
                    loop(address, operand);                    
                    break;
                case fbc:
                    break;
                case fin:
                    break;
                default: break;    
            };
    
    return opcode;
}

int main(){
    //le port B est utilise pour la generation du son plus precisement les broche 3(0) et 4(PWM) veuillez voir soundGenerator.cpp pour plus de details
    DDRB = 0xff;
    //le port A est utilise pour allumer les 8 dels possibles dans notre robot la del existante est lie aux broche 1 et 2 veuillez voir setDel.cpp pour plus de details
    DDRA = 0xff;
    //le port D est utilise pour la generation du PWM plus precisement les broches 5, 6, 7 et 8 veuillez voir PWMWgenerator.cpp pour plus de details
    DDRD = 0xff;
    //initialisation des registres de generation de son
    initialisationSound();
    //addresse de lecture 
    uint16_t currentAddress = 0x02;
    uint8_t unexecutedInstruction[INSTRUCTION_SIZE];

    do{
       memory.lecture(currentAddress, (uint8_t*)unexecutedInstruction, INSTRUCTION_SIZE);
       currentAddress += 2;
    }while(unexecutedInstruction[0] != dbt);
    do{
		currentAddress += 2;
    } while(interpret(currentAddress) !=  fin);
    
    return 0;
}