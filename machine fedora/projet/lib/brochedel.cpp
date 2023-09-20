#include "brochedel.hpp"

/**
 * \brief Constructeur par défaut.
 * \param[in] port le port utilise (port A, B, C ou D).
 * \param[in] posConnecteur  la position du connecteur.
 * \param[in] type le nombre de del gérées par le connecteur (1 ou 2)
 * \param[in] orientation l'orientation du connecteur..
 * \port[in] port auquel on connecte la del
 * \numero[in] numero de la del
 */
BROCHE_DEL::BROCHE_DEL(PORT_ENUM port, uint8_t posConnecteur, BROCHE_TYPE type, ORIENTATION_BROCHE orientation) : posConnecteur_(posConnecteur), orientation_(orientation), port_(port), type_(type), delUnAllume(false), delDeuxAllume(false)
{
    switch (port)
    {

    case PORT_A:
    {
        DDRA = ddrModifierPort(DDRA);
        break;
    }

    case PORT_B:
    {
        DDRB = ddrModifierPort(DDRB);
        break;
    }

    case PORT_C:
    {
        DDRC = ddrModifierPort(DDRC);
        break;
    }

    case PORT_D:
    {
        DDRD = ddrModifierPort(DDRD);
        break;
    }
    }
}

/**
 * \fn void BROCHE_DEL::eteindreDel(uint8_t numeroDEL)
 * \brief eteint la del en prenant son numero en paramètre et  en verifiant que le numero est valide
 * \param in] numeroDEL le numero de la del à éteindre
 */
void BROCHE_DEL::eteindreDel(uint8_t numeroDel)
{
    if (type_ == GND)
    {
        DEBUG_PRINT("Ne peux pas allumer cette broche de type GND.\n");
        return;
    }

    if (!(numeroDel == 1 || numeroDel == 2))
    {
        DEBUG_PRINT("Erreure: Numero de DEL invalide.\n");
        return;
    }

    if (numeroDel == 2 && type_ == UNDEL)
    {
        DEBUG_PRINT("Erreure: Ne peux pas manipuler DEL 2 avec cette broche.\n");
    }

    switch (port_)
    {

    case PORT_A:
    {
        PORTA = eteindreDelModifierPort(PORTA, numeroDel);
        break;
    }

    case PORT_B:
    {
        PORTB = eteindreDelModifierPort(PORTB, numeroDel);
        break;
    }

    case PORT_C:
    {
        PORTC = eteindreDelModifierPort(PORTC, numeroDel);
        break;
    }

    case PORT_D:
    {
        PORTD = eteindreDelModifierPort(PORTD, numeroDel);
        break;
    }
    }
}

/**
 * \fn void BROCHE_DEL::allumerDel(uint8_t numeroDel)
 * \brief allume la del en prenant son numero en paramètre et en vérifiant qu'il est valide
 * \param[in] numeroDel numero de la del à allumer
 */
void BROCHE_DEL::allumerDel(uint8_t numeroDel)
{
    if (type_ == GND)
    {
        DEBUG_PRINT("Ne peux pas allumer cette broche de type GND.\n");
        return;
    }

    if (!(numeroDel == 1 || numeroDel == 2))
    {
        DEBUG_PRINT("Erreure: Numero de DEL invalide.\n");
        return;
    }

    if (numeroDel == 2 && type_ == UNDEL)
    {
        DEBUG_PRINT("Erreure: Ne peux pas manipuler DEL 2 avec cette broche.\n");
        return;
    }

    switch (port_)
    {

    case PORT_A:
    {
        PORTA = allumerDelModifierPort(PORTA, numeroDel);
        break;
    }

    case PORT_B:
    {
        PORTB = allumerDelModifierPort(PORTB, numeroDel);
        break;
    }

    case PORT_C:
    {
        PORTC = allumerDelModifierPort(PORTC, numeroDel);
        break;
    }

    case PORT_D:
    {
        PORTD = allumerDelModifierPort(PORTD, numeroDel);
        break;
    }
    }
}

/**
 * \fn bool BROCHE_DEL::estAllumeDel(uint8_t numeroDel) const
 * \brief retourne le booleen delUnAllume ou delDeuxAllume en fonction du nombre de broches allumées et du nombre de del gérées par la broche 
 * \param[in] numeroDel numero dont le del dont ont veut vérifier l'état
 * \param[out] return retourne un bool qui dépend du nombre de del allumées
 */
bool BROCHE_DEL::estAllumeDel(uint8_t numeroDel) const
{
    switch (numeroDel)
    {
    case 1:
        return delUnAllume;
        break;

    case 2:
        return delDeuxAllume;
        break;

    default:
        DEBUG_PRINT("Erreure: Numero de DEL invalide.\n");
        break;
    }
    return false;
}

/**
 * \fn uint8_t BROCHE_DEL::eteindreDelModifierPort(uint8_t valeurPort, uint8_t numeroDel)
 * \brief éteint 
 */
uint8_t BROCHE_DEL::eteindreDelModifierPort(uint8_t valeurPort, uint8_t numeroDel)
{
    if (numeroDel == 1)
    {
        return valeurPort & ~(1UL << posConnecteur_);
    }
    else
    {
        return valeurPort & ~(1UL << (posConnecteur_ + orientation_));
    }
}

uint8_t BROCHE_DEL::allumerDelModifierPort(uint8_t valeurPort, uint8_t numeroDel)
{
    if (numeroDel == 1)
    {
        delUnAllume = true;
        return valeurPort | (1 << posConnecteur_);
    }
    else
    {
        delDeuxAllume = true;
        return valeurPort | (1 << (posConnecteur_ + orientation_));
    }
}

uint8_t BROCHE_DEL::ddrModifierPort(uint8_t valeurPort)
{
    return valeurPort | (1 << posConnecteur_) | (1 << (posConnecteur_ + orientation_));
}