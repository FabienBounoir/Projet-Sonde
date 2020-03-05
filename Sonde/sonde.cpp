#include "sonde.h"

/**
* @file sonde.cpp
*
* @brief classe qui contient les valeurs des differents capteurs
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.1
*
*/

/**
 * @brief contructeur de la classe Sonde
 *
 * @fn Sonde::Sonde
 * @param parent
 */
Sonde::Sonde(QObject *parent) : QObject(parent), temperature(0.), temperatureUnite("°C"), ressentie(0.), ressentieUnite("°C"),\
    humidite(0), humiditeUnite("%"), luminosite(0), luminositeUnite("Lux"), pression(0), pressionUnite("hPa"), altitude(0), altitudeUnite("Mètre"), couleur(0)
{

}

/**
 * @brief retourne la valeur de temperature
 *
 * @fn Sonde::getTemperature
 * @return double ...
 */
double Sonde::getTemperature() const
{
    return temperature;
}

/**
 * @brief retourne la valeur de ressentie
 *
 * @fn Sonde::getRessentie
 * @return double
 */
double Sonde::getRessentie() const
{
    return ressentie;
}

/**
 * @brief retourne l'unité de la valeur de temperature
 *
 * @fn Sonde::getTemperatureUnite
 * @return QString
 */
QString Sonde::getTemperatureUnite() const
{
    return temperatureUnite;
}

/**
 * @brief retourne l'unité de la valeur de ressentie
 *
 * @fn Sonde::getRessentieUnite
 * @return QString
 */
QString Sonde::getRessentieUnite() const
{
    return ressentieUnite;
}

/**
 * @brief retourne la valeur d'humidité
 *
 * @fn Sonde::getHumidite
 * @return int
 */
int Sonde::getHumidite() const
{
    return humidite;
}

/**
 * @brief retourne la valeur de luminosité
 *
 * @fn Sonde::getLuminosite
 * @return int
 */
int Sonde::getLuminosite() const
{
    return luminosite;
}

/**
 * @brief retourne l'unité de la valeur d'humidite
 *
 * @fn Sonde::getHumiditeUnite
 * @return QString
 */
QString Sonde::getHumiditeUnite() const
{
    return humiditeUnite;
}

/**
 * @brief retourne l'unité de la valeur de luminosite
 *
 * @fn Sonde::getLuminositeUnite
 * @return QString
 */
QString Sonde::getLuminositeUnite() const
{
    return luminositeUnite;
}

/**
 * @brief retourne la valeur de pression
 *
 * @fn Sonde::getPression
 * @return int
 */
int Sonde::getPression() const
{
    return pression;
}

/**
 * @brief retourne l'unité de la valeur de pression
 *
 * @fn Sonde::getPressionUnite
 * @return QString
 */
QString Sonde::getPressionUnite() const
{
    return pressionUnite;
}

/**
 * @brief retourne la valeur de l'altitude
 *
 * @fn Sonde::getAltitude
 * @return int
 */
int Sonde::getAltitude() const
{
    return altitude;
}

/**
 * @brief retourne l'unité de la valeur de l'altitude
 *
 * @fn Sonde::getAltitudeUnite
 * @return QString
 */
QString Sonde::getAltitudeUnite() const
{
    return altitudeUnite;
}

/**
 * @brief retourne l'etat de la led
 *
 * @fn Sonde::getEtatLed
 * @return int
 */
int Sonde::getEtatLed() const
{
    return couleur;
}

/**
 * @brief modifie la variable température avec celle passée en paramètre
 *
 * @fn Sonde::setTemperature
 * @param temperature
 */
void Sonde::setTemperature(double temperature)
{
    this->temperature = temperature;
}

/**
 * @brief modifie la variable ressentie avec celle passée en paramètre
 *
 * @fn Sonde::setRessentie
 * @param ressentie
 */
void Sonde::setRessentie(double ressentie)
{
    this->ressentie = ressentie;
}

/**
 * @brief modifie la variable de l'unité utilisée pour la temperature
 *
 * @fn Sonde::setTemperatureUnite
 * @param temperatureUnite
 */
void Sonde::setTemperatureUnite(QString temperatureUnite)
{
    this->temperatureUnite = "°" + temperatureUnite;
}

/**
 * @brief modifie la variable de l'unité utilisée pour le ressentie
 *
 * @fn Sonde::setRessentieUnite
 * @param ressentieUnite
 */
void Sonde::setRessentieUnite(QString ressentieUnite)
{
    this->ressentieUnite = "°" + ressentieUnite;
}

/**
 * @brief modifie la variable de l'humidite
 *
 * @fn Sonde::setHumidite
 * @param humidite
 */
void Sonde::setHumidite(int humidite)
{
    this->humidite = humidite;
}

/**
 * @brief modifie la variable de la luminosite
 *
 * @fn Sonde::setLuminosite
 * @param luminosite
 */
void Sonde::setLuminosite(int luminosite)
{
    this->luminosite = luminosite;
}

/**
 * @brief modifie la variable de l'unité utilisée pour l'humidite
 *
 * @fn Sonde::setHumiditeUnite
 * @param humiditeUnite
 */
void Sonde::setHumiditeUnite(QString humiditeUnite)
{
    this->humiditeUnite = humiditeUnite;
}

/**
 * @brief modifie la variable de l'unité utilisée pour la luminosite
 *
 * @fn Sonde::setLuminositeUnite
 * @param luminositeUnite
 */
void Sonde::setLuminositeUnite(QString luminositeUnite)
{
    this->luminositeUnite = luminositeUnite;
}

/**
 * @brief modifie la variable de la pression
 *
 * @fn Sonde::setPression
 * @param pression
 */
void Sonde::setPression(int pression)
{
    this->pression = pression;
}

/**
 * @brief modifie la variable de l'unité utilisée pour la pression
 *
 * @fn Sonde::setPressionUnite
 * @param pressionUnite
 */
void Sonde::setPressionUnite(QString pressionUnite)
{
    this->pressionUnite = pressionUnite;
}

/**
 * @brief modifie la variable altitude passée en paramètre
 *
 * @fn Sonde::setAltitude
 * @param altitude
 */
void Sonde::setAltitude(int altitude)
{
    this->altitude = altitude;
}

/**
 * @brief modifie la variable de l'unité utilisée pour l'altitude
 *
 * @fn Sonde::setAltitudeUnite
 * @param altitudeUnite
 */
void Sonde::setAltitudeUnite(QString altitudeUnite)
{
    this->altitudeUnite = altitudeUnite;
}
/**
 * @brief modifie la variable de l'etat de la led
 *
 * @fn Sonde::setCouleurLed
 * @param couleur
 */
void Sonde::setCouleurLed(int couleur)
{
    this->couleur = couleur;
}

