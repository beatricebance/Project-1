#include "Robot.h"
//Parcourt
enum PARCOURT{
    INITIAL,//search for closest wall
    FOLLOW,
    JUMPING,
    FOLLOW_LOCKED,
    TURN_AROUND
};
/******************* PROTOTYPES AND GLOBAL VARIABLES *******************/
//Mode parcourt
Robot robot;
uint16_t delais = 1;
bool detection = false;
bool mur = false;
uint8_t state = INITIAL;
Side* current = &robot.left; // current side
Side* next = &robot.right;    // the other side
void jump();
void permuter();
/***********************************************************************/

int main()
{
    //mode logiciel
    robot.uart.enableReception(true);
    while (robot.mode == LOGICIEL)
    {
        robot.update();
    }
    //mode parcourt
    robot.uart.enableReception(false); // We do not need to communicate with the computer
    while (robot.mode == PARCOURT)
    {
        switch(state){
			// le robot commence par trouver de quel coter est le mur
			// et change d'etat lorsqu'il a trouver un mur
            case INITIAL:
                if(next == robot.searchClosesthWall()){
                    permuter();
                    state = FOLLOW;
                    robot.led.changeColor(GREEN);
                } else if(current == robot.searchClosesthWall()){
                    state = FOLLOW;
                    robot.led.changeColor(GREEN);
                }
            break;
            // le robot suit le mur "current". En meme temps, il cherche un mur
            // de l'autre cote "next".  s'il en trouve un, il jump de coter.
            // Si le mur "current" fini, le robot attent un peu avant de faire le tour
            // du mur.
            case FOLLOW:
                robot.follow(current);
                if(robot.searchWall(next)){
                    jump();
                }
                else if( !robot.searchWall(current)){
                    robot.led.changeColor(RED);
                    robot.move(NORMAL_SPEED,FORWARD); //avancer un peu 
                    _delay_ms(800);
                    delais = 0;
                    mur = false;
                    state = TURN_AROUND;
                }
            break;
            // lorsque le robot change de coter, il commence par verifier si le mur est plus pres
            // que 20cm.  si oui, il ne fait que suivre lautre coter et le robot va s'ajuster seul
            // a la bonne distance.  si le mur est a plus de 20cm, le robot pivote d'environs 45
            // degree.  Par la suite, le robot continue en ligne droite jusqu'a ce que le robot soit
            // a moins de 20cm du mur, et il pivot de 45 degree afin de se raligner et changer d'etat.
            case JUMPING:
                robot.led.changeColor(RED);
                if (current->sensor->getStableDistance() <= 20){
					state = FOLLOW_LOCKED;
					break;
				}
				
                if(!robot.searchWall(current)){
                    robot.spin(next,45);
                }
                else if(current->sensor->getStableDistance()>=20){
                    //robot.spin(current,45);
                    current->wheel->set(LOW_SPEED, FORWARD);
                    current->o_wheel->set(NORMAL_SPEED + 25, FORWARD);
                    _delay_ms(1000);
                    robot.move(NORMAL_SPEED,FORWARD);
                    while(current->sensor->getStableDistance() >= 20);
                    {
                    }
                    next->wheel->set(LOW_SPEED, FORWARD);
                    next->o_wheel->set(NORMAL_SPEED + 25, FORWARD);
                    _delay_ms(1000);
                }
                else state = FOLLOW_LOCKED;
            break;
            // comme dans FOLLOW, le robot suit le mur "current" et si le mur se termine il le contourne.
            // par contre, au lieu de verifier s'il y a un autre mur de lautre coter afin de changer de coter,
            // il chercher quand est-ce que le mur de lautre coter se terminer afin de retourner dans letat FOLLOW
            case FOLLOW_LOCKED:
                if(!robot.searchWall(next))
                {
                    state = FOLLOW;
                }
                else if( !robot.searchWall(current)){
                    robot.led.changeColor(RED);
                    robot.move(NORMAL_SPEED,FORWARD); //avancer un peu 
                    _delay_ms(800);
                    delais = 0;
                    mur = false;
                    state = TURN_AROUND;
                }
                robot.follow(current);
            break;
            // le robot tourne du cote du mur qu'il suivait.
            case TURN_AROUND:
				robot.led.changeColor(RED);
				// dans le but de detecter des poteau en meme temps sans
				// perde de temps dans les delay..
				
				// sil y a un mur de lautre coter au debut du virement, ne pas considerer
				if (delais == 0){
					if (robot.searchWall(next)){
						mur = true;
					}
					delais = 1;
				}
				
				// sil y avait un mur, et quil nest plus la, on peut commencer a 
				// considerer les poteaux
				if (!robot.searchWall(next) && mur == true){
					mur = false;
				}
				
				if(robot.searchWall(next) && mur == false){
					detection = true;
                }
                // au cas ou le poteau arretais, on veux continuer a compter
                // jusqua 500
				if (detection){
					delais++;
				}
				// une fois le delais achever
				if (delais%500 == 0){
					detection = false;
					delais = 1;
					// si le mur n'est plus la
					if (!robot.searchWall(next)){
						// faire sonner le buzzer
						jump();
					}
				}
				//////////////////////////////////////////////////////////////
                //tourner du coté du mur
				if (current == &robot.right){
					current->wheel->set(LOW_SPEED + 20,FORWARD);
					current->o_wheel->set(HIGH_SPEED,FORWARD);
				}
				else {
					current->wheel->set(LOW_SPEED,FORWARD);
					current->o_wheel->set(HIGH_SPEED,FORWARD);
				}
				//continuer de longer le mur si on le détecte
                if(current->sensor->getStableDistance()<=20)
					state = FOLLOW;
            break;
        }
    }
    return 0;
}

/**************************** INTERRUPTS *******************************/

//instruction received
ISR(USART0_RX_vect)
{
    //USART reception complete
    uint8_t request = robot.uart.receive();
    //on éxécute la requete
    switch (request)
    {
    case REQUETE_ENVOI: //Transmission initiale
        robot.identify();
        break;
    case VITESSE_GAUCHE: //vitesse gauche
        robot.left.wheel->set(robot.uart.receive());
        break;
    case VITESSE_DROIT: //vitesse droite
        robot.right.wheel->set(robot.uart.receive());
        break;
    case COULEUR_DEL: //LED COLOR
        robot.led.changeColor(robot.uart.receive());
        break;
    }
}

//button state changed
ISR(INT0_vect)
{
    robot.button.update();

    //dans le mode parcourt on fait un virage à 180 degre seulement lorsque la lumiere est verte
    if((robot.mode == PARCOURT) && robot.button.isPressed() && ((PORTB & 0b00000011) == 0b00000001) ){
        robot.led.changeColor(RED);
        robot.spin(next,180);
        permuter();
        state = FOLLOW;
    }
}
/***********************************************************************/


// le robot verifie si ce qu'il capte de lautre coter est un mur ou un poteau
void jump(){
	if (state == TURN_AROUND){
		for (uint8_t i = 0; i < 3; i++)
        {
            robot.buzzer.playNote(BUZZER_NOTE);
            _delay_ms(200);
            robot.buzzer.stop();
            _delay_ms(100);
        }
	}
	
    else if (!robot.isWall(next))
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            robot.buzzer.playNote(BUZZER_NOTE);
            _delay_ms(200);
            robot.buzzer.stop();
            _delay_ms(100);
        }
    } else{
        permuter();
        state = JUMPING;
    }
}

// changer le coter dont nous suivons le mur "current" et lautre coter "next"
void permuter(){
    Side* temp = current;
    current = next;
    next = temp;
}
