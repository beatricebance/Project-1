#include "Robot.h"

// la classe robot est construit comme ayant : une led, deux roues, deux sensor, un buzzer, et un bouton.
// et ayant deux construction, le coter droit et gaucher, qui contiennent chacun : sa roue, son capteur,
// la roue de lautre coter (o_wheel) et le capteur de lautre coter (o_sensor)
Robot::Robot() : led(LED_PORT, LED_LSP, LED_MSP),
                 rightWheel(RIGHT_WHEEL_PORT, RIGHT_WHEEL_PWM, RIGHT_WHEEL_DIR,0),
                 leftWheel(LEFT_WHEEL_PORT, LEFT_WHEEL_PWM, LEFT_WHEEL_DIR),
                 button(BUTTON_PORT, BUTTON_PIN),
                 rightSensor(RIGHT_SENSOR_PORT,RIGHT_SENSOR_PIN),
                 leftSensor(LEFT_SENSOR_PORT, LEFT_SENSOR_PIN),
                 buzzer(BUZZER_PORT, BUZZER_LSP, BUZZER_MSP)
{
    right.sensor = &rightSensor;
    right.wheel = &rightWheel;
    left.sensor = &leftSensor;
    left.wheel = &leftWheel;

    right.o_sensor = &leftSensor;
    right.o_wheel = &leftWheel;
    left.o_sensor = &rightSensor;
    left.o_wheel = &rightWheel;

    //initialisation
    cli();
    //SREG |= (1 << 7); //enabling global interrupts
    // enabling external interrupts
    EICRA |= (1 << INT0);
    sei();
    toggle_mode();
}

void Robot::toggle_mode()
{
    //lecture du mode en memoire 0x00
    memoire.lecture(MODE_BYTE_ADRESS, &mode);
    //Changer de mode a chaque RESET ou alimentation
    mode = (mode != 0x01);
    memoire.ecriture(MODE_BYTE_ADRESS, mode);
}

// le robot regarde s'il detecte quelque chose a une distance de moins
// de 60cm
bool Robot::searchWall(Side* s)
{
    //if we detect something no far then 60 cm
    uint8_t distance = s->sensor->getStableDistance();
    if (distance <= 60)
    {
            return true;
    }
    return false;
}

// le robot cherche lequel du mur a droite ou a gauche est le plus pres.
// utiliser dans l'etat initialisation du parcours au cas ou le robot 
// capterait par erreur quelque chose de lautre coter.
Side* Robot::searchClosesthWall()
{
    bool leftWall = searchWall(&left);
    bool rightWall = searchWall(&right);
    if (leftWall)
    {
        return &left;
    } else if (rightWall)
    { //we turn to search in other directions
        return &right;
    }
    return 0;
}

// le robot suit un mur (current ou next) passer en paramettre.  si la distance du mur
// est en dehors de linterval de 13 a 17 cm, le robot alume la led de couleur rouge et
// s'ajuste en consequence.
void Robot::follow(Side* s)
{
    uint8_t distance = s->sensor->getStableDistance();
    if (!isValid(distance, 15))
    {
        led.changeColor(RED);
        if (distance > 15)
        { //if getting far from the wall
			if (s == &right){
				s->o_wheel->set(NORMAL_SPEED, FORWARD);
				s->wheel->set(LOW_SPEED + 20, FORWARD);
			}
			else {
				s->o_wheel->set(NORMAL_SPEED + 20, FORWARD);
				s->wheel->set(LOW_SPEED, FORWARD);
			}
        }
        else
        { //if too close to wall
            s->wheel->set(NORMAL_SPEED, FORWARD);
            s->o_wheel->set(LOW_SPEED, FORWARD);
        }
    }
    else
    {
        led.changeColor(GREEN);
        move(NORMAL_SPEED, FORWARD); // continue
    }
}

// permet d'envoyer les informations sur le robot lors du mode logiciel
void Robot::update()
{
    uart.send(ETAT_BOUTON, button.isPressed() ? 0 : 1);
    uart.send(DISTANCE_DROIT, rightSensor.getStableDistance());
    uart.send(DISTANCE_GAUCHE, leftSensor.getStableDistance());
}

// envoie les information d'identification du robot.
void Robot::identify()
{
    char nomRobot[7] = "UTOPIA";
    char numeroEquipe[5] = "0911";
    uint8_t numeroSection = 0x01;
    char session[5] = "18-1";
    uint8_t couleurBase = 1;

    uart.send(NOM_ROBOT, nomRobot);
    uart.send(NUMERO_EQUIPE, numeroEquipe);
    uart.send(NUMERO_SECTION, numeroSection);
    uart.send(SESSION, session);
    uart.send(COULEUR_BASE, couleurBase);
}

// verifie si ce qui est capter est un mur ou un poteau.
bool Robot::isWall(Side* s)
{

    //TODO: return true if wall false if its just an obstacle
    _delay_ms(500);
    bool w1 = searchWall(s);
    _delay_ms(500);
    bool w2 = searchWall(s);
    if (w1 && w2)
        return true;
    return false;
}

// permet au robot d'avancer a un vitesse donner en ligne droit ou 
// a reculons.  cependant, le moteur de gauche est plus rapide que celui
// de droite alors nous devons le ralentir un peu
void Robot::move(uint8_t speed, Direction dir)
{
    rightWheel.set(speed, dir);
    leftWheel.set(speed - 20, dir);
}

// permet au robot de tourner en arretant l'une de ses roues.
void Robot::turn(Side* s)
{
    for (uint8_t i = 0; i < 3; i++)
        {
            buzzer.playNote(BUZZER_NOTE);
            _delay_ms(200);
            buzzer.stop();
            _delay_ms(100);
            uart.send('t');
            uart.send('\n');
        }
    s->wheel->set(0);    //0%
    s->o_wheel->set(70); //70%
}

// permet au robot de tourner sur place plus rapidement en faisant avancer
// l'une des roues, et en faisant reculer l'autre.
void Robot::spin(Side* s, uint16_t angle)
{
    s->wheel->set(-65); //backward
    s->o_wheel->set(65); //forward
    for (uint16_t i = 0; i < (angle*_90_SPIN_MS) ; i++)
        _delay_ms(2);
    stop();
}

// arrete les roues du robot.
void Robot::stop()
{
    rightWheel.set(0, FORWARD);
    leftWheel.set(0, FORWARD);
}
