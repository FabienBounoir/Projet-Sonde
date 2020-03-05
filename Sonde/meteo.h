#ifndef METEO_H
#define METEO_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QGeoPositionInfoSource>
#include <QGeoCoordinate>

#define API_KEY "a2157cdc4a03c47c79e8414161c59762"          //!< clé de l'API d'Openweather

/**
 * @file meteo.h
 * @brief Declaration de la classe Meteo
 *
 * @version 4.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
* @class Meteo meteo.h "meteo.h"
*
* @brief Declaration de la classe Meteo
*/
class Meteo : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @fn Meteo
     * @param parent
     */
    explicit Meteo(QObject *parent = nullptr);

    double getTemperature() const;                          /** recuperer la temperature */
    double getRessentie() const;                            /** recuperer le ressentie */
    double getTemperatureMin() const;                       /** recuperer la temperature minimale */
    double getTemperatureMax() const;                       /** recuperer la temperature maximale */
    int getPression() const;                                /** recuperer la pression atmosphérique */
    int getHumidite() const;                                /** recuperer l'humidité */
    QString getVille() const;                               /** recuperer le nom de la ville */

    void setTemperature(double temperature);                /** modifier la valeur de la temperature */
    void setTemperatureMin(double temperatureMin);          /** modifier la valeur de la temperature minimale */
    void setTemperatureMax(double temperatureMax);          /** modifier la valeur de la temperature maximale */
    void setRessentie(double ressentie);                    /** modifier la valeur de ressentie */
    void setPression(int pression);                         /** modifier la valeur de la pression */
    void setHumidite(int humidite);                         /** modifier la valeur de l'humidite */
    void setVille(QString ville);                           /** modifier la valeur de la ville */

    void recupererDonnerMeteo(QString URL);                 /** envoie une requete à l'API de openweather  */
    void creerUrlVille(QString ville);                                  /** cree l'URl pour l'API avec une ville */
    void creerUrlCoordonnerGps(double latitude, double longitude);    /** cree l'URl pour l'API avec les coordonnée de longitude et latitude */

private:
    QNetworkAccessManager *manager;                         //!< objet manager

signals:
    void donnerMeteoMiseAJour();                            /** signal emis quand le JSON est decomposé */

private slots:
    void replyFinished(QNetworkReply *reply);               /** fonction appelée quand un nouveau Json est recu */
    void positionMiseAJour(const QGeoPositionInfo &info);   /** fonction appelée quand la position est mise à jour */

private:
    double temperature;                                     //!<  variable qui stocke la temperature
    double ressentie;                                       //!<  variable qui stocke le ressentie
    double temperatureMin;                                  //!<  variable qui stocke a temperature minimale
    double temperatureMax;                                  //!<  variable qui stocke la temperature maximale

    int pression;                                           //!<  variable qui stocke la pression atmosphérique
    int humidite;                                           //!<  variable qui stocke l'humidité

    QString ville;                                          //!<  variable qui stocke la ville

    void localiserAppareil();                               //!<  fonction qui localise l'appareil
};

#endif // METEO_H
