#pragma once
#include "Configuration.h"
#include "memoire_24.h"
#include "PushButton.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "Buzzer.h"
#include "Sensor.h"
#include "UART.h"
#include "Wheel.h"
#include "can.h"
#include "LED.h"

enum Mode
{
    LOGICIEL,
    PARCOURT
};

struct Side{
    Sensor* sensor;
    Wheel* wheel;
    Sensor* o_sensor;
    Wheel*  o_wheel;
};

enum PROTOCOL
{
    NOM_ROBOT = 0xf0,
    NUMERO_EQUIPE,
    NUMERO_SECTION,
    SESSION,
    COULEUR_BASE,
    ETAT_BOUTON,
    DISTANCE_GAUCHE,
    DISTANCE_DROIT,
    VITESSE_GAUCHE,
    VITESSE_DROIT,
    COULEUR_DEL,
    REQUETE_ENVOI
};

class Robot
{
  public:
    Robot();
    void identify();
    void update();
    bool searchWall(Side* s);
    Side* searchClosesthWall();
    void follow(Side* s);
    void move(uint8_t speed, Direction dir);
    void turn(Side* s);
    void spin(Side* s, uint16_t angle);
    void stop();

    bool isWall(Side* s);

    LED led;
    UART uart;
    Memoire24CXXX memoire;
    PushButton button;
    Buzzer buzzer;
    Side right;
    Side left;

    uint8_t mode;

  private:
    Wheel rightWheel;
    Wheel leftWheel;
    Sensor rightSensor;
    Sensor leftSensor;
    void toggle_mode();
    
};