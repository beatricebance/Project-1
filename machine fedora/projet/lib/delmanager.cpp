#include "delmanager.hpp"

/**
 * \brief Constructeur par défaut.
 */
DEL_Manager::DEL_Manager()
{
}

/**
 * \fn void DEL_Manager::allumerDEL(uint8_t numero)
 * \brief Fonction qui permet d'allumer une del selon son numero.
 * \param[in] numero le numero de la del à allumer.
 */
void DEL_Manager::allumerDEL(uint8_t numero)
{
    switch (numero)
    {
    case 1:
    {
        listeBROCHE[0]->allumerDel(1);
        break;
    }

    case 2:
    {
        listeBROCHE[0]->allumerDel(2);
        break;
    }

    case 3:
    {
        listeBROCHE[1]->allumerDel(1);
        break;
    }

    case 4:
    {
        listeBROCHE[1]->allumerDel(2);
        break;
    }

    case 5:
    {
        listeBROCHE[2]->allumerDel(1);
        break;
    }

    default:
    {
        DEBUG_PRINT("Erreure: NUméro de DEL invalide. Doit etre entre 1 et 5.\n");
        return;
    }
    }
}

/**
 * \fn void DEL_Manager::eteindreDEL(uint8_t numero)
 * \brief Fonction qui permet d'eteindre une del selon son numero.
 * \param[in] numero le numero de la del à eteindre.
 */
void DEL_Manager::eteindreDEL(uint8_t numero)
{
    switch (numero)
    {
    case 1:
    {
        listeBROCHE[0]->eteindreDel(1);
        break;
    }

    case 2:
    {
        listeBROCHE[0]->eteindreDel(2);
        break;
    }

    case 3:
    {
        listeBROCHE[1]->eteindreDel(1);
        break;
    }

    case 4:
    {
        listeBROCHE[1]->eteindreDel(2);
        break;
    }

    case 5:
    {
        listeBROCHE[2]->eteindreDel(1);
        break;
    }

    default:
    {
        DEBUG_PRINT("Erreure: Numéro de DEL invalide.");
        return;
    }
    }
}

/**
 *\fn bool DEL_Manager::delEstAllume(uint8_t numero)
 *\brief Fonction qui retourne l'état d'une del(éteinte/alluméée) selon son numero
 *\param[in] numero le numero de la del dont on veut connaitre l'état
 *\param[out] return retourne un bool qui dépend de l'état de la del ciblée (vrai pour allumée, faux pour éteinte)
 */
bool DEL_Manager::delEstAllume(uint8_t numero) const
{
    switch (numero)
    {
    case 1:
    {
        return listeBROCHE[0]->estAllumeDel(1);
        break;
    }

    case 2:
    {
        return listeBROCHE[0]->estAllumeDel(2);
        break;
    }

    case 3:
    {
        return listeBROCHE[1]->estAllumeDel(1);
        break;
    }

    case 4:
    {
        return listeBROCHE[1]->estAllumeDel(2);
        break;
    }

    case 5:
    {
        return listeBROCHE[2]->estAllumeDel(1);
        break;
    }

    default:
    {
        DEBUG_PRINT("Erreure: Numéro de DEL invalide.");
        return false;
    }
    }
}

/**
 * \fn void DEL_Manager::ajouterBROCHE(BROCHE_DEL *broche)
 * \brief Fonction qui permet d'ajouter une broche au gestionnaire de del
 * \param[in] broche pointeur vers la broche à ajouter
 */
void DEL_Manager::ajouterBROCHE(BROCHE_DEL *broche)
{
    listeBROCHE[nbBroches++] = broche;
}