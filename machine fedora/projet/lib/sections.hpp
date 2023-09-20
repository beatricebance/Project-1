// DESCRIPTION: DESCRIPTION: Programme contenant la definition de la classe Sections //
//              qui permet le controle du robot lors des differents sections.        //
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _SECTIONS_H_
#define _SECTIONS_H_

#include "def.hpp"
#include "trackersensor.hpp"
#include "delmanager.hpp"
#include "roues.hpp"
#include "sirc.hpp"
#include "sonorite.hpp"
#include "boutonSection.hpp"

class Sections
{
  public:
    Sections(TRACKER_SENSOR *trackerSensor, Roues *roues, DEL_Manager *manager, Sonorite* sonorite, BoutonSection* boutonSection, SIRC *sirc);
    void section1();
    void section2();
    void section3();
    void section4();
    void initialiserTimer();
    void arreterTimer();
    uint16_t getTimer();


  private:
    TRACKER_SENSOR *trackerSensor_;
    Roues *roues_;
    DEL_Manager *manager_;
    Sonorite* sonorite_;
    BoutonSection* boutonSection_; 
    SIRC* sirc_;
    POS_ROBOT lirePosEtDel();
    void suivreLigneNormal(const uint8_t& vitesse);
    void suivreLigneNormal2(const uint8_t& vitesse);
    void suivreLigneNormal3(const uint8_t &vitesse);
    void naviguerRectangle();
    void finirTrajet();
    void suivreLigneD();
    void trouverPoint(uint8_t commandeRecue);
    const uint8_t VITESSE_ROUES = 60;
    const uint8_t VITESSE_ROUES_S2 = 85;
    const uint8_t VITESSE_ROUES_FIX = 75;
    const uint8_t VITESSE_ROUES_LENT = 50;
    const uint8_t VITESSE_MAX = 100;
    const uint8_t COEF_VIRAGE = 11;
};

#endif