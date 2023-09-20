
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
#include <PWM.h>



bool allumer = false;
uint8_t increment = 0;
uint16_t adressMemTemp = 0x0;
uint16_t adress= 0x0;


void dbc(uint8_t val){
	if (allumer) {
		increment = val;
		adressMemTemp = adress;
	}
}

void fbc(){
	if (allumer) {
		if (increment > 0) {
			increment--;
			adress = adressMemTemp;
		}
	}
  
}

void dbt(){
  allumer = true;
  
  initialisation(); //initialisation du PWM
}

void att(uint8_t val){
  if(allumer){
    for(int i = 0; i < val; i++){
      _delay_ms(25);
    }
  }
}

void dal(uint8_t val){
  if(allumer){
    setColor(vert);
  }
}

void det(uint8_t val){
  if(allumer){
    eteindreDel();
  }
}

void mar(){
  if(allumer){
    arret();
  }
}

void mav(uint8_t val){
  if(allumer){
    setPuissance(val/255);
  }
}

void mre(uint8_t val){
  if(allumer){
    setPuissance(-val/255);
  }
}

void trd() {
  if(allumer){
    tournerDegre(90, DROITE);
  }
}

void trg() {
  if(allumer){
    tournerDegre(90,GAUCHE);
  }
}

void sgo(uint8_t val){
  if(allumer){
    switch(val){
      case 45: setPWMA(142); break;
      case 46: setPWMA(134); break;
      case 47: setPWMA(127); break;
      case 48: setPWMA(119); break;
      case 49: setPWMA(113); break;
      case 50: setPWMA(106); break;
      case 51: setPWMA(100); break;
      case 52: setPWMA(95); break;
      case 53: setPWMA(90); break;
      case 54: setPWMA(85); break;
      case 55: setPWMA(80); break;
      case 56: setPWMA(75); break;
      case 57: setPWMA(71); break;
      case 58: setPWMA(67); break;
      case 59: setPWMA(63); break;
      case 60: setPWMA(60); break;
      case 61: setPWMA(56); break;
      case 62: setPWMA(53); break;
      case 63: setPWMA(50); break;
      case 64: setPWMA(47); break;
      case 65: setPWMA(45); break;
      case 66: setPWMA(42); break;
      case 67: setPWMA(40); break;
      case 68: setPWMA(38); break;
      case 69: setPWMA(36); break;
      case 70: setPWMA(34); break;
      case 71: setPWMA(32); break;
      case 72: setPWMA(30); break;
      case 73: setPWMA(28); break;
      case 74: setPWMA(27); break;
      case 75: setPWMA(25); break;
      case 76: setPWMA(24); break;
      case 77: setPWMA(22); break;
      case 78: setPWMA(21); break;
      case 79: setPWMA(20); break;
      case 80: setPWMA(19); break;
      case 81: setPWMA(18); break;
    }
  }
}

void sar() {
  if(allumer){
    clearPWM();
  }
  
}

void fin() {
  det(0);
  mar();
  sar();
  allumer = false;
}

void effOper(uint8_t code, uint8_t val){
  switch(code){
    case 0x01: dbt();     break; //-
    case 0x02: att(val);  break; //-
    case 0x44: dal(val);  break; //-
    case 0x45: det(val);  break; //-
    case 0x48: sgo(val);  break; //-
    case 0x09: sar();     break; //-
    case 0x60:
    case 0x61: mar();     break; //-
    case 0x62: mav(val);  break; //-
    case 0x63: mre(val);  break; //-
    case 0x64: trd();     break; //-
    case 0x65: trg();     break; //-
    case 0xC0: dbc(val);  break; //-
    case 0xC1: fbc();     break; //- 
    case 0xFF: fin();     break; //-
  }
}

int main() {
  
  uint8_t instr = 0;
  uint8_t oper = 0;
  //uint8_t nbOctets = 0;
  Memoire24CXXX memoire;

  adress = 0x02; //On saute les deux premiers octets desginant la taille du fichier

   do // tant qu on ne trouve pas le code de fin on continue a executer des operations
   {
     Memoire24CXXX().lecture(adress, &instr); 
     adress++;
     _delay_ms(5);
      
     Memoire24CXXX().lecture(adress, &oper);
     adress++;
     _delay_ms(5);

     effOper(instr, oper);
     allumer=false;
   } while(instr != 0xFF); // 0xFF --> code dinstruction de fin
    fin();
}
