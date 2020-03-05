#include "gps.h"
/**
* @file gps.cpp
*
* @brief classe qui contient les valeurs du GPS (latitude / longitude)
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.1
*
*/


/**
 * @brief constructeur de la classe Gps
 *
 * @fn Gps::Gps
 */
Gps::Gps(): latitude(0.), longitude(0.)
{

}

/**
 * @brief destructeur de la classe Gps
 *
 * @fn Gps::~Gps
 */
Gps::~Gps()
{

}

/**
 * @brief retourne la valeur de la longitude
 *
 * @fn Gps::getLongitude
 * @return double
 */
double Gps::getLongitude() const
{
    return longitude;
}

/**
 * @brief retourne la valeur de la latitude
 *
 * @fn Gps::getLatitude
 * @return double
 */
double Gps::getLatitude() const
{
    return latitude;
}

/**
 * @brief modifie la valeur de la latitude
 *
 * @fn Gps::setLatitude
 * @param latitude
 */
void Gps::setLatitude(double latitude)
{
    this->latitude = latitude;
}

/**
 * @brief modifie la valeur de la longitude
 *
 * @fn Gps::setLongitude
 * @param longitude
 */
void Gps::setLongitude(double longitude)
{
    this->longitude = longitude;
}
