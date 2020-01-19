#include "esp32.h"

/**
* @file esp32.cpp
*
* @brief programme qui contient les valeur des different capteur
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.0
*
*/

/**
 * @brief contructeur de la classe Esp32
 *
 * @fn Esp32::Esp32
 * @param parent
 */
Esp32::Esp32(QObject *parent) : QObject(parent), temperature(0.), temperatureUnite("°C"), ressentie(0.), ressentieUnite("°C"),\
    humidite(0), humiditeUnite("%"), luminosite(0), luminositeUnite("Lux"), pression(0), pressionUnite("hPa"), altitude(0), altitudeUnite("Mètre"), couleur(0)
{

}

/**
 * @brief retourne la valeur de temperature
 *
 * @fn Esp32::getTemperature
 * @return double ...
 */
double Esp32::getTemperature() const
{
    return temperature;
}

/**
 * @brief retourne la valeur de ressentie
 *
 * @fn Esp32::getRessentie
 * @return double
 */
double Esp32::getRessentie() const
{
    return ressentie;
}

/**
 * @brief retourne l'uniter de la valeur de temperature
 *
 * @fn Esp32::getTemperatureUnite
 * @return QString
 */
QString Esp32::getTemperatureUnite() const
{
    return temperatureUnite;
}

/**
 * @brief retourne l'uniter de la valeur de ressentie
 *
 * @fn Esp32::getRessentieUnite
 * @return QString
 */
QString Esp32::getRessentieUnite() const
{
    return ressentieUnite;
}

/**
 * @brief retourne la valeur d'humiditer
 *
 * @fn Esp32::getHumidite
 * @return int
 */
int Esp32::getHumidite() const
{
    return humidite;
}

/**
 * @brief retourne la valeur de luminositer
 *
 * @fn Esp32::getLuminosite
 * @return int
 */
int Esp32::getLuminosite() const
{
    return luminosite;
}

/**
 * @brief retourne l'uniter de la valeur d'humidite
 *
 * @fn Esp32::getHumiditeUnite
 * @return QString
 */
QString Esp32::getHumiditeUnite() const
{
    return humiditeUnite;
}

/**
 * @brief retourne l'uniter de la valeur de luminosite
 *
 * @fn Esp32::getLuminositeUnite
 * @return QString
 */
QString Esp32::getLuminositeUnite() const
{
    return luminositeUnite;
}

/**
 * @brief retourne la valeur de pression
 *
 * @fn Esp32::getPression
 * @return int
 */
int Esp32::getPression() const
{
    return pression;
}

/**
 * @brief retourne l'uniter de la valeur de pression
 *
 * @fn Esp32::getPressionUnite
 * @return QString
 */
QString Esp32::getPressionUnite() const
{
    return pressionUnite;
}

/**
 * @brief retourne la valeur de l'altitude
 *
 * @fn Esp32::getAltitude
 * @return int
 */
int Esp32::getAltitude() const
{
    return altitude;
}

/**
 * @brief retourne l'uniter de la valeur de l'altitude
 *
 * @fn Esp32::getAltitudeUnite
 * @return QString
 */
QString Esp32::getAltitudeUnite() const
{
    return altitudeUnite;
}

/**
 * @brief retourne l'etat de la led
 *
 * @fn Esp32::getEtatLed
 * @return int
 */
int Esp32::getEtatLed() const
{
    return couleur;
}

/**
 * @brief modifie la variable température avec celle-ci passer en paramètre
 *
 * @fn Esp32::setTemperature
 * @param temperature
 */
void Esp32::setTemperature(double temperature)
{
    this->temperature = temperature;
}

/**
 * @brief modifie la variable ressentie avec celle-ci passer en paramètre
 *
 * @fn Esp32::setRessentie
 * @param ressentie
 */
void Esp32::setRessentie(double ressentie)
{
    this->ressentie = ressentie;
}

/**
 * @brief modifie la variable de l'uniter utiliser pour la temperature
 *
 * @fn Esp32::setTemperatureUnite
 * @param temperatureUnite
 */
void Esp32::setTemperatureUnite(QString temperatureUnite)
{
    this->temperatureUnite = "°" + temperatureUnite;
}

/**
 * @brief modifie la variable de l'uniter utiliser pour le ressentie
 *
 * @fn Esp32::setRessentieUnite
 * @param ressentieUnite
 */
void Esp32::setRessentieUnite(QString ressentieUnite)
{
    this->ressentieUnite = "°" + ressentieUnite;
}

/**
 * @brief modifie la variable de l'humidite
 *
 * @fn Esp32::setHumidite
 * @param humidite
 */
void Esp32::setHumidite(int humidite)
{
    this->humidite = humidite;
}

/**
 * @brief modifie la variable de la luminosite
 *
 * @fn Esp32::setLuminosite
 * @param luminosite
 */
void Esp32::setLuminosite(int luminosite)
{
    this->luminosite = luminosite;
}

/**
 * @brief modifie la variable de l'uniter utiliser pour l'humidite
 *
 * @fn Esp32::setHumiditeUnite
 * @param humiditeUnite
 */
void Esp32::setHumiditeUnite(QString humiditeUnite)
{
    this->humiditeUnite = humiditeUnite;
}

/**
 * @brief modifie la variable de l'uniter utiliser pour la luminosite
 *
 * @fn Esp32::setLuminositeUnite
 * @param luminositeUnite
 */
void Esp32::setLuminositeUnite(QString luminositeUnite)
{
    this->luminositeUnite = luminositeUnite;
}

/**
 * @brief modifie la variable de la pression
 *
 * @fn Esp32::setPression
 * @param pression
 */
void Esp32::setPression(int pression)
{
    this->pression = pression;
}

/**
 * @brief modifie la variable de l'uniter utiliser pour la pression
 *
 * @fn Esp32::setPressionUnite
 * @param pressionUnite
 */
void Esp32::setPressionUnite(QString pressionUnite)
{
    this->pressionUnite = pressionUnite;
}

/**
 * @brief modifie la variable altitude passer en paramètre
 *
 * @fn Esp32::setAltitude
 * @param altitude
 */
void Esp32::setAltitude(int altitude)
{
    this->altitude = altitude;
}

/**
 * @brief modifie la variable de l'uniter utiliser pour l'altitude
 *
 * @fn Esp32::setAltitudeUnite
 * @param altitudeUnite
 */
void Esp32::setAltitudeUnite(QString altitudeUnite)
{
    this->altitudeUnite = altitudeUnite;
}
/**
 * @brief modifie la variable de l'etat de la led
 *
 * @fn Esp32::setCouleurLed
 * @param couleur
 */
void Esp32::setCouleurLed(int couleur)
{
    this->couleur = couleur;
}

