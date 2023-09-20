#include "sections.hpp"

Sections::Sections(TRACKER_SENSOR *trackerSensor, Roues *roues, DEL_Manager *manager, Sonorite *sonorite, BoutonSection *boutonSection, SIRC *sirc) : trackerSensor_(trackerSensor), roues_(roues), manager_(manager), sonorite_(sonorite), boutonSection_(boutonSection), sirc_(sirc)
{
}

/**
 * \fn void Sections::section1().
 * \Brief fonction qui permet le controle du robot pour naviguer le trajet selon la section 1. 
 */
void Sections::section1()
{
    uint8_t commandeRecue = 0;
    uint8_t adresseRecue = 0;
    uint16_t temps = 0;
    bool receptionReussie = false;
    POS_ROBOT positionActuelle = HORSTRACK;

    suivreLigneNormal(VITESSE_ROUES);

    sonorite_->sonner(70);
    _delay_ms(350);
    sonorite_->arreter();

    sirc_->initialiserReceptionIR();
    receptionReussie = sirc_->receptionIR(commandeRecue, adresseRecue);

    if (receptionReussie)
    {
        sirc_->arreterReceptionIR();
        for (uint8_t i = 0; i < commandeRecue; i++)
        {
            manager_->eteindreDEL(1);
            manager_->eteindreDEL(2);
            manager_->eteindreDEL(3);
            manager_->eteindreDEL(4);
            manager_->eteindreDEL(5);
            _delay_ms(250);
            manager_->allumerDEL(1);
            manager_->allumerDEL(2);
            manager_->allumerDEL(3);
            manager_->allumerDEL(4);
            manager_->allumerDEL(5);
            _delay_ms(250);
            manager_->eteindreDEL(1);
            manager_->eteindreDEL(2);
            manager_->eteindreDEL(3);
            manager_->eteindreDEL(4);
            manager_->eteindreDEL(5);
            _delay_ms(250);
        }
    }
    else if (!receptionReussie)
    {
        sirc_->arreterReceptionIR();

        for (uint8_t i = 0; i < 3; i++)
        {
            for (uint8_t j = 1; j <= 5; j++)
            {
                manager_->allumerDEL(j);
                _delay_ms(25);
                manager_->eteindreDEL(j);
                _delay_ms(25);
            }
        }

        boutonSection_->initialiserBoutonSection();

        while (!demarrerSection)
            ;

        initialiserTimer();

        do
        {
            temps = getTimer();
        } while (temps < 15625); // temps < 2 seconde.

        arreterTimer();
        boutonSection_->arreterBoutonSection();

        commandeRecue = compteurReceptionIR;

        for (uint8_t i = 0; i < commandeRecue; i++)
        {
            manager_->eteindreDEL(1);
            manager_->eteindreDEL(2);
            manager_->eteindreDEL(3);
            manager_->eteindreDEL(4);
            manager_->eteindreDEL(5);
            _delay_ms(250);
            manager_->allumerDEL(1);
            manager_->allumerDEL(2);
            manager_->allumerDEL(3);
            manager_->allumerDEL(4);
            manager_->allumerDEL(5);
            _delay_ms(250);
            manager_->eteindreDEL(1);
            manager_->eteindreDEL(2);
            manager_->eteindreDEL(3);
            manager_->eteindreDEL(4);
            manager_->eteindreDEL(5);
            _delay_ms(250);
        }
    }
    sonorite_->sonner(70);
    _delay_ms(350);
    sonorite_->arreter();

    switch (commandeRecue)
    {
    case 1:
    case 2:
    case 3:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(65, 65, AVANT);
        _delay_ms(2100);
        roues_->arretPwmMoteur();
        _delay_ms(2000);
        roues_->tournerGauche90();
        trouverPoint(commandeRecue);
        break;
    }
    case 4:
    case 5:
    case 6:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(65, 65, AVANT);
        _delay_ms(1700);
        roues_->arretPwmMoteur();
        _delay_ms(2000);
        roues_->tournerGauche90();
        trouverPoint(commandeRecue);
        break;
    }
    case 7:
    case 8:
    case 9:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(65, 65, AVANT);
        _delay_ms(1200);
        roues_->arretPwmMoteur();
        _delay_ms(2000);
        roues_->tournerGauche90();
        trouverPoint(commandeRecue);
        break;
    }
    }

    roues_->trounerDroite90();
    sonorite_->sonner(70);
    _delay_ms(3000);
    sonorite_->arreter();
    roues_->trounerDroite90();
    sonorite_->sonner(70);
    _delay_ms(3000);
    sonorite_->arreter();

    roues_->demarrerPwmMoteur();
    roues_->ajustementRoues(60, 60, AVANT);
    _delay_ms(700);
    roues_->arretPwmMoteur();

    while (positionActuelle == HORSTRACK)
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        positionActuelle = lirePosEtDel();
    }
    suivreLigneNormal3(50);
}

/**
 * \fn void Sections::section2().
 * \Brief fonction qui permet le controle du robot pour naviguer le trajet selon la section 2. 
 */
void Sections::section2()
{
    suivreLigneNormal2(VITESSE_ROUES_LENT);
}

/**
 * \fn void Sections::section3().
 * \Brief fonction qui permet le controle du robot pour naviguer le trajet selon la section 3.
 */
void Sections::section3()
{
    suivreLigneNormal(VITESSE_ROUES);
    sonorite_->sonner(70);
    _delay_ms(350);
    sonorite_->arreter();
    boutonSection_->initialiserBoutonSection();
    while (!demarrerSection)
        ;
    boutonSection_->arreterBoutonSection();
    suivreLigneD();
    boutonSection_->initialiserBoutonSection();
    while (!demarrerSection)
        ;
    boutonSection_->arreterBoutonSection();
    finirTrajet();
}

/**
 * \fn void Sections::section4().
 * \Brief fonction qui permet le controle du robot pour naviguer le trajet selon la section 3. 
 */
void Sections::section4()
{
    for (uint8_t i = 0; i < 3; i++)
    {
        suivreLigneNormal(43);
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(40, 40, AVANT);
        sonorite_->sonner(70);
        _delay_ms(350);
        sonorite_->arreter();
        naviguerRectangle();
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(40, 40, AVANT);
        sonorite_->sonner(70);
        _delay_ms(350);
        sonorite_->arreter();
    }
    finirTrajet();
}

/**
 * \fn POS_ROBOT Sections::lirePosEtDel().
 * \Brief fonction qui permet de lire la position du robot en allumant les lumiere des Dels correspondant.
 * \return POS_ROBOT la position du robot.
 */
POS_ROBOT Sections::lirePosEtDel()
{
    POS_ROBOT position = HORSTRACK;
    bool delAllumes[5] = {};
    uint8_t nbrDelAllumes = 0;
    for (uint8_t i = 1; i <= 5; i++)
    {
        if (trackerSensor_->noirDetecte(i))
        {
            manager_->allumerDEL(i);
            position = (POS_ROBOT)i;
            nbrDelAllumes++;
            delAllumes[i - 1] = true;
        }
        else if (!trackerSensor_->noirDetecte(i))
            manager_->eteindreDEL(i);
    }

    if (nbrDelAllumes == 5)
        return TOUTES;
    else if (nbrDelAllumes == 2 && delAllumes[1] && delAllumes[2])
        return IR2_ET_3;
    else if (nbrDelAllumes == 2 && delAllumes[3] && delAllumes[2])
        return IR4_ET_3;
    else if (nbrDelAllumes == 3 && delAllumes[2] && delAllumes[3] && delAllumes[4])
        return IR3_ET_4_ET_5;
    else if (nbrDelAllumes == 3 && delAllumes[2] && delAllumes[1] && delAllumes[0])
        return IR3_ET_2_ET_1;
    else
        return position;
}
/**
 * \fn void Sections::suivreLigneD().
 * \Brief fonction qui permet de calculer le temps que cela prend pour que le
 *        robot avance en ligne droite. Ceci est utilise pour la section 3 pour differencier 
 *        les 4 trajets (D1,D2,D3 et D4). De plus, on assure que le robot reste centre durant
 *        sont parcours en ligne droite(pour que le temps soit respecte).
 */
void Sections::suivreLigneD()
{
    POS_ROBOT positionActuelle = HORSTRACK;
    uint16_t temps = 0;
    bool grandeLigneFranchie = false;
    bool continuerDroit = false;
    bool D[4] = {};
    initialiserTimer();
    while (1)
    {
        switch (positionActuelle)
        {
        case HORSTRACK:
        {
            roues_->arretPwmMoteur();
            break;
        }
        case IR1:
        {
            if (continuerDroit)
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, AVANT);
            }
            else
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, GAUCHE);
            }
            break;
        }
        case IR2:
        {
            if (continuerDroit)
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, AVANT);
            }
            else
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, GAUCHE);
            }
            break;
        }
        case IR3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(VITESSE_ROUES_FIX, VITESSE_ROUES_FIX, AVANT);
            break;
        }
        case IR4:
        {
            if (continuerDroit)
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, AVANT);
            }
            else
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, DROITE);
            }
            break;
        }
        case IR5:
        {
            if (continuerDroit)
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, AVANT);
            }
            else
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, DROITE);
            }
            break;
        }
        case IR2_ET_3:
        {
            if (continuerDroit)
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, AVANT);
            }
            else
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(0, VITESSE_ROUES, GAUCHE);
            }
            if ((temps < 6000) && grandeLigneFranchie)
            {
                D[0] = true;
                grandeLigneFranchie = false;
            }
            else if ((temps >= 8000) && grandeLigneFranchie)
            {
                D[1] = true;
                grandeLigneFranchie = false;
            }
            break;
        }
        case IR4_ET_3:
        {
            if (continuerDroit)
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, VITESSE_ROUES, AVANT);
            }
            else
            {
                roues_->demarrerPwmMoteur();
                roues_->ajustementRoues(VITESSE_ROUES, 0, DROITE);
            }
            if ((temps < 6000) && grandeLigneFranchie)
            {
                D[2] = true;
                grandeLigneFranchie = false;
            }
            else if ((temps >= 8000) && grandeLigneFranchie)
            {
                D[3] = true;
                grandeLigneFranchie = false;
            }
            break;
        }
        case IR3_ET_2_ET_1:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(VITESSE_ROUES_FIX, VITESSE_ROUES_FIX, AVANT);
            break;
        }
        case IR3_ET_4_ET_5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(VITESSE_ROUES_FIX, VITESSE_ROUES_FIX, AVANT);
            break;
        }
        case TOUTES:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(VITESSE_ROUES_FIX, VITESSE_ROUES_FIX, AVANT);
            temps = getTimer();
            arreterTimer();
            grandeLigneFranchie = true;
            continuerDroit = true;
            break;
        }
        }
        if (temps != 0 && positionActuelle == HORSTRACK)
        {
            for (uint8_t i = 0; i < 4; i++)
            {
                if (D[i])
                    manager_->allumerDEL(i + 1);
            }
            break;
        }
        positionActuelle = lirePosEtDel();
    }
}
/**
 * \fn void Sections::suivreLigneNormal(const uint8_t& vitesse).
 * \Brief fonction qui permet au robot de suivre une ligne tout en restant
 *        centre sur lignes noires. Ceci permet au robot de ne pas aller hors trajet.
 * \param[in] vitesse qui represente la vitesse du robot
 */
void Sections::suivreLigneNormal(const uint8_t &vitesse)
{
    POS_ROBOT positionActuelle = HORSTRACK;
    while (1)
    {
        switch (positionActuelle)
        {
        case HORSTRACK:
        {
            roues_->arretPwmMoteur();
            break;
        }
        case IR1:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, GAUCHE);
            break;
        }
        case IR2:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, GAUCHE);
            break;
        }
        case IR3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, AVANT);
            break;
        }
        case IR4:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, DROITE);
            break;
        }
        case IR5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, DROITE);
            break;
        }
        case IR2_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, vitesse, GAUCHE);
            break;
        }
        case IR4_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, 0, DROITE);
            break;
        }
        case IR3_ET_2_ET_1:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, vitesse, GAUCHE);
            break;
        }
        case IR3_ET_4_ET_5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, 0, DROITE);
            break;
        }
        case TOUTES:
        {
            roues_->arretPwmMoteur();
            break;
        }
        }
        if (positionActuelle == TOUTES)
            break;
        positionActuelle = lirePosEtDel();
    }
}

/**
 * \fn void Sections::naviguerRectangle().
 * \Brief fonction qui permet au robot de naviguer lorsqu'il trouve un trajet en
 *        rectangle.
 */
void Sections::naviguerRectangle()
{
    POS_ROBOT positionActuelle;
    do
    {
        positionActuelle = lirePosEtDel();
        switch (positionActuelle)
        {
        case HORSTRACK:
        case IR3:
        case TOUTES:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 40, AVANT);
            break;
        }
        case IR1:
        case IR2:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 40, DROITE);
            break;
        }
        case IR4:
        case IR5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 40, GAUCHE);
            break;
        }
        case IR3_ET_2_ET_1:
        case IR2_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 0, DROITE);
            break;
        }
        case IR3_ET_4_ET_5:
        case IR4_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, 40, GAUCHE);
            break;
        }
        }
    } while (positionActuelle != TOUTES);
}

/**
 * \fn void Sections::finirTrajet().
 * \Brief fonction qui permet de naviguer jusqu'a la fin du trajet, et d'arreter le robot
 *        quand il se trouve hors de la ligne noire.
 */
void Sections::finirTrajet()
{
    POS_ROBOT positionActuelle;
    do
    {
        positionActuelle = lirePosEtDel();
        switch (positionActuelle)
        {
        case HORSTRACK:
        case IR1:
        case IR5:
        {
            roues_->arretPwmMoteur();
            break;
        }
        case IR2:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 40, GAUCHE);
            break;
        }
        case IR3:
        case IR3_ET_2_ET_1:
        case TOUTES:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 40, AVANT);
            break;
        }
        case IR4:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 40, DROITE);
            break;
        }
        case IR2_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(40, 0, GAUCHE);
            break;
        }
        case IR3_ET_4_ET_5:
        case IR4_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, 40, DROITE);
            break;
        }
        }
    } while (positionActuelle != TOUTES && positionActuelle != HORSTRACK);
}

/**
 * \fn void Sections::initialiserTimer().
 * \Brief fonction qui permet d'initialiser la minuterie du robot.
 */
void Sections::initialiserTimer()
{
    TCCR1B |= (1 << CS12) | (1 << CS10); // diviser l'horloge par 1024
    TCNT1 = 0;
}

/**
 * \fn void Sections::arreterTimer().
 * \Brief fonction qui permet d'arreter la minuterie du robot. Il remet le registre conerne
 *        a sa valeur par defaut.
 */
void Sections::arreterTimer()
{
    TCCR1B &= ~(1 << CS12) & ~(1 << CS10); // No clock.
}

/**
 * \fn void Sections::getTimer().
 * \Brief fonction qui permet de retourne le temps passe apres avoir appele la methode
 *        initialiserTimer(); Il faut multiplier cette valeur par 128 pour obtenir le t
 *        temps reel en micro-secondes.
 * \return Lr temps passe.
 */
uint16_t Sections::getTimer()
{
    return TCNT1;
}

/**
 * \fn void Sections::trouverPoint(uint8_t commandeRecue)
 * \Brief fonction qui permet de se placer a un point precis dans la section un selon
 *        la commande envoyee par IR.
 * \param[in]   commandeRecue    La commande recue par IR.
 */
void Sections::trouverPoint(uint8_t commandeRecue)
{
    switch (commandeRecue)
    {
    case 1:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(2400);
        roues_->arretPwmMoteur();
        break;
    }
    case 2:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(1700);
        roues_->arretPwmMoteur();
        break;
    }
    case 3:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(1000);
        roues_->arretPwmMoteur();
        break;
    }
    case 4:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(2400);
        roues_->arretPwmMoteur();
        break;
    }
    case 5:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(1700);
        roues_->arretPwmMoteur();
        break;
    }
    case 6:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(1000);
        roues_->arretPwmMoteur();
        break;
    }
    case 7:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(2400);
        roues_->arretPwmMoteur();
        break;
    }
    case 8:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(1700);
        roues_->arretPwmMoteur();
        break;
    }
    case 9:
    {
        roues_->demarrerPwmMoteur();
        roues_->ajustementRoues(60, 60, AVANT);
        _delay_ms(1000);
        roues_->arretPwmMoteur();
        break;
    }
    }
}

/**
 * \fn void Sections::suivreLigneNormal2(const uint8_t& vitesse).
 * \Brief fonction qui fait avancer le robot tout en suivant la ligne en noir.
 * \param[in]  vitesse  Vitese par laquelle le robot se deplacera.
 */
void Sections::suivreLigneNormal2(const uint8_t &vitesse)
{
    uint8_t vitesseVariables = vitesse;
    POS_ROBOT positionActuelle = HORSTRACK;
    uint16_t temps = 0;
    bool estHorsTrack = false;
    bool vitesseRapide = false;
    initialiserTimer();
    while (1)
    {
        switch (positionActuelle)
        {
        case HORSTRACK:
        {
            roues_->arretPwmMoteur();
            estHorsTrack = true;
            break;
        }
        case IR1:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR2:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesseVariables, vitesseVariables, AVANT);
            estHorsTrack = false;
            vitesseRapide = true;
            break;
        }
        case IR4:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR2_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR4_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, 0, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR3_ET_2_ET_1:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR3_ET_4_ET_5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, 0, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case TOUTES:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, 0, DROITE);
            estHorsTrack = false;
            vitesseRapide = true;
            break;
        }
        }

        temps = getTimer();

        if (temps > 15625)
        {
            arreterTimer();
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(60, 60, AVANT);
            _delay_ms(700);
            roues_->arretPwmMoteur();
            break;
        }
        else if (!estHorsTrack)
        {
            initialiserTimer();
        }
        else if (vitesseRapide)
        {
            vitesseVariables = 65;
        }
        positionActuelle = lirePosEtDel();
    }
}

void Sections::suivreLigneNormal3(const uint8_t &vitesse)
{
    uint8_t vitesseVariables = vitesse;
    POS_ROBOT positionActuelle = HORSTRACK;
    uint16_t temps = 0;
    bool estHorsTrack = false;
    bool vitesseRapide = false;
    initialiserTimer();
    while (1)
    {
        switch (positionActuelle)
        {
        case HORSTRACK:
        {
            roues_->arretPwmMoteur();
            estHorsTrack = true;
            break;
        }
        case IR1:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR2:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesseVariables, vitesseVariables, AVANT);
            estHorsTrack = false;
            vitesseRapide = true;
            break;
        }
        case IR4:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR2_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR4_ET_3:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, 0, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR3_ET_2_ET_1:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(0, vitesse, GAUCHE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case IR3_ET_4_ET_5:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, 0, DROITE);
            estHorsTrack = false;
            vitesseRapide = false;
            break;
        }
        case TOUTES:
        {
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(vitesse, vitesse, AVANT);
            estHorsTrack = false;
            vitesseRapide = true;
            break;
        }
        }

        temps = getTimer();

        if (temps > 15625)
        {
            arreterTimer();
            roues_->demarrerPwmMoteur();
            roues_->ajustementRoues(60, 60, AVANT);
            _delay_ms(700);
            roues_->arretPwmMoteur();
            break;
        }
        else if (!estHorsTrack)
        {
            initialiserTimer();
        }
        else if (vitesseRapide)
        {
            vitesseVariables = 65;
        }
        positionActuelle = lirePosEtDel();
    }
}