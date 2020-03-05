#include "meteo.h"

/**
* @file meteo.cpp
* @brief classe qui gere les requetes avec l'api
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.1
*/

/**
 * @brief constructeur de la classe Meteo
 *
 * @fn Meteo::Meteo
 * @param parent
 */
Meteo::Meteo(QObject *parent) : QObject(parent), temperature(0.), ressentie(0.), temperatureMin(0.), temperatureMax(0.), pression(0), humidite(0)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    //localiserAppareil();          //methode pour localiser sans GPS.
}

/**
 * @brief retourne la valeur de temperature
 *
 * @fn Meteo::getTemperature
 * @return double
 */
double Meteo::getTemperature() const
{
    return temperature;
}

/**
 * @brief retourne la valeur de ressentie
 *
 * @fn Meteo::getRessentie
 * @return double
 */
double Meteo::getRessentie() const
{
    return ressentie;
}

/**
 * @brief retourne la valeur de temperature Minimale en degre
 *
 * @fn Meteo::getTemperatureMin
 * @return double
 */
double Meteo::getTemperatureMin() const
{
    return temperatureMin;
}

/**
 * @brief retourne la valeur de temperature Maximale en degre
 *
 * @fn Meteo::getTemperatureMax
 * @return double
 */
double Meteo::getTemperatureMax() const
{
    return temperatureMax;
}

/**
 * @brief retourne la valeur de pression
 *
 * @fn Meteo::getPression
 * @return int
 */
int Meteo::getPression() const
{
    return pression;
}

/**
 * @brief retourne la valeur de humidité
 *
 * @fn Meteo::getHumidite
 * @return int
 */
int Meteo::getHumidite() const
{
    return humidite;
}

/**
 * @brief retourne la valeur de la ville
 *
 * @fn Meteo::getVille
 * @return QString
 */
QString Meteo::getVille() const
{
    return ville;
}


/**
 * @brief modifie la variable ville avec celle passée en paramètre
 *
 * @fn Meteo::setVille
 * @param ville
 */
void Meteo::setVille(QString ville)
{
    this->ville = ville;
}
/**
 * @brief modifie la variable température avec celle passée en paramètre
 *
 * @fn Meteo::setTemperature
 * @param temperature
 */
void Meteo::setTemperature(double temperature)
{
    this->temperature = temperature;
}

/**
 * @brief modifie la variable températureMax avec celle passée en paramètre
 *
 * @fn Meteo::setTemperatureMax
 * @param temperatureMax
 */
void Meteo::setTemperatureMax(double temperatureMax)
{
    this->temperatureMax = temperatureMax;
}

/**
 * @brief modifie la variable températureMin avec celle passée en paramètre
 *
 * @fn Meteo::setTemperatureMin
 * @param temperatureMin
 */
void Meteo::setTemperatureMin(double temperatureMin)
{
    this->temperatureMin = temperatureMin;
}

/**
 * @brief modifie la variable ressentie avec celle passée en paramètre
 *
 * @fn Meteo::setRessentie
 * @param ressentie
 */
void Meteo::setRessentie(double ressentie)
{
    this->ressentie = ressentie;
}

/**
 * @brief modifie la variable humidite avec celle passée en paramètre
 *
 * @fn Meteo::setHumidite
 * @param humidite
 */
void Meteo::setHumidite(int humidite)
{
    this->humidite = humidite;
}

/**
 * @brief modifie la variable pression avec celle passée en paramètre
 *
 * @fn Meteo::setPression
 * @param pression
 */
void Meteo::setPression(int pression)
{
    this->pression = pression;
}

/**
 * @brief methode qui localise l'appareil
 *
 * @fn Meteo::localiserAppareil
 */
void Meteo::localiserAppareil()
{
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source)
    {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionMiseAJour(QGeoPositionInfo)));
        source->startUpdates();    
    }
    source->setUpdateInterval(2000);
}

/**
 * @brief methode appelée quand la position est mise à jour
 *
 * @fn Meteo::positionMiseAJour
 * @param info
 */
void Meteo::positionMiseAJour(const QGeoPositionInfo &info)
{
    qDebug() << "Position Mise à jour :" << info.coordinate();

    QGeoCoordinate coordonner = QGeoCoordinate();
    coordonner = info.coordinate();

    creerUrlCoordonnerGps(coordonner.latitude(), coordonner.longitude());
}

/**
 * @brief methode qui cree un Url pour l'api avec une ville
 *
 * @fn Meteo::creerUrlCoordonnerGps
 * @param latitude
 * @param longitude
 */
void Meteo::creerUrlCoordonnerGps(double latitude, double longitude)
{
    recupererDonnerMeteo("http://api.openweathermap.org/data/2.5/weather?lat=" + QString::number(latitude) + "&lon=" + QString::number(longitude) + "&units=metric&APPID=" + API_KEY);
}

/**
 * @brief methode qui cree un Url pour l'api avec une longitude et latitude
 *
 * @fn Meteo::creerUrlVille
 * @param ville
 */
void Meteo::creerUrlVille(QString ville)
{
    recupererDonnerMeteo("http://api.openweathermap.org/data/2.5/weather?q=" + ville + ",FR&units=metric&APPID=" + API_KEY);
}

/**
 * @brief fonction qui fait une requête a l'api du site openweathermap en fonction de la ville choisie
 *
 * @fn Meteo::recupererDonnerMeteo
 * @param URL
 */
void Meteo::recupererDonnerMeteo(QString URL)
{
    QUrl url(URL);

    QNetworkRequest request;
    request.setUrl(url);

    request.setRawHeader("Accept", "application/json");
    qDebug() << Q_FUNC_INFO << request.url() << endl;
    manager->get(request);

}

/**
 * @brief Décompose le Json pour récupérer les différentes données
 *
 * @fn Meteo::replyFinished
 * @param reply
 */
void Meteo::replyFinished(QNetworkReply *reply)
{
    QString datas = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(datas.toUtf8());

    QJsonObject obj = doc.object();

    QJsonObject main = obj.value(QString("main")).toObject();

    setVille(obj.value(QString("name")).toString());
    setTemperature(main.value(QString("temp")).toDouble());
    setTemperatureMin(main.value(QString("temp_min")).toDouble());
    setTemperatureMax(main.value(QString("temp_max")).toDouble());
    setRessentie(main.value(QString("feels_like")).toDouble());
    setPression(main.value(QString("pressure")).toInt());
    setHumidite(main.value(QString("humidity")).toInt());

    emit donnerMeteoMiseAJour();

}
