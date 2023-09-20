#include "trackersensor.hpp"

/**
 * \fn TRACKER_SENSOR::TRACKER_SENSOR(uint8_t posIR1, uint8_t posIR2, uint8_t posIR3, uint8_t posIR4, uint8_t posIR5)
 * \brief constructeur pour la classe trackersensor
 * \param[in] posIR1 position du premier capteur
 * \param[in] posIR2 position du deuxième capteur
 * \param[in] posIR3 position du troisième capteur
 * \param[in] posIR4 position du quatrième capteur
 * \param[in] posIR5 position du cinquième capteur
 */
TRACKER_SENSOR::TRACKER_SENSOR(uint8_t posIR1, uint8_t posIR2, uint8_t posIR3, uint8_t posIR4, uint8_t posIR5) : posIR_{posIR1, posIR2, posIR3, posIR4, posIR5}
{
    /* for (uint8_t i = 0; i < 5; i++)
    {
        min_[i] = 0xFFFF;
        max_[i] = 0;
    }*/
}

/**
 * \fn TRACKER_SENSOR::noirDetecte(uint8_t IR)
 * \brief Fonction qui retourne vrai si le capteur détecte du noir sous le capteur spécifié en paramètre
 * \param[in] IR l'index du capteur à tester
 * return un bool qui retourne vrai si le capteur détecte du noir
 */
bool TRACKER_SENSOR::noirDetecte(uint8_t IR)
{
    if (lecture(posIR_[IR - 1]) <= 0x1F0)
        return true;
    else
        return false;
}

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