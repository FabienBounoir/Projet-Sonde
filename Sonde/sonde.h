#ifndef SONDE_H
#define SONDE_H

#include <QObject>
#include <QString>
#include <QtDebug>

/**
 * @file sonde.h
 *
 * @brief Declaration de la classe Sonde
 *
 * @version 4.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @class Sonde sonde.h "sonde.h"
 *
 * @brief Declaration de la classe Sonde
*/
class Sonde : public QObject
{
    Q_OBJECT
public:
    explicit Sonde(QObject *parent = nullptr);          /** constructeur de la classe Sonde*/

    double getTemperature() const;                          /** recuperer la temperature */
    double getRessentie() const;                            /** recuperer le ressentie */
    QString getTemperatureUnite() const;                    /** recuperer l'unite de temperature */
    QString getRessentieUnite() const;                      /** recuperer l'unite du resssentie */
    int getHumidite() const;                                /** recuperer l'humidite */
    int getLuminosite() const;                              /** recuperer la luminosite */
    QString getHumiditeUnite() const;                       /** recuperer l'unite d'humidite */
    QString getLuminositeUnite() const;                     /** recuperer l'unite de luminosite */
    int getPression() const;                                /** recuperer la pression atmosphérique */
    QString getPressionUnite() const;                       /** recuperer l'unite de pression atmosphérique */
    int getAltitude() const;                                /** recuperer l'altitude */
    QString getAltitudeUnite() const;                       /** recuperer l'unite d'altitude */
    int getEtatLed() const;                                 /** recuperer l'etat de la led */


    void setTemperature(double temperature);                /** modifier la valeur de la temperature */
    void setRessentie(double ressentie);                    /** modifier la valeur de ressentie */
    void setTemperatureUnite(QString temperatureUnite);     /** modifier la valeur de l'uniter de temperature */
    void setRessentieUnite(QString ressentieUnite);         /** modifier la valeur de l'uniter de ressentie */
    void setHumidite(int humidite);                         /** modifier la valeur de l'humidite */
    void setLuminosite(int luminosite);                     /** modifier la valeur de luminosite */
    void setHumiditeUnite(QString humiditeUnite);           /** modifier la valeur de l'unite d'humidite */
    void setLuminositeUnite(QString luminositeUnite);       /** modifier la valeur de l'unite de luminosite */
    void setPression(int pression);                         /** modifier la valeur de la pression atmosphérique */
    void setPressionUnite(QString pressionUnite);           /** modifier la valeur de l'unite de pression atmosphérique */
    void setAltitude(int altitude);                         /** modifier la valeur d'altitude */
    void setAltitudeUnite(QString altitudeUnite);           /** modifier la valeur de l'unite altitude */
    void setCouleurLed(int couleur);                        /** modifier l'etat de la led */

private:
    double temperature;             //!<  variable qui stocke la temperature
    QString temperatureUnite;       //!<  variable qui stocke l'unite de la temperature

    double ressentie;               //!<  variable qui stocke le ressentie
    QString ressentieUnite;         //!<  variable qui stocke l'unite de ressentie

    int humidite;                   //!<  variable qui stocke l'humidite
    QString humiditeUnite;           //!<  variable qui stocke l'unite de l'humidite

    int luminosite;                 //!<  variable qui stocke la luminosite
    QString luminositeUnite;        //!<  variable qui stocke l'unite de la luminosite

    int pression;                   //!<  variable qui stocke la pression atmosphérique
    QString pressionUnite;          //!<  variable qui stocke l'unite de pression atmosphérique

    int altitude;                   //!<  variable qui stocke l'altitude
    QString altitudeUnite;          //!<  variable qui stocke l'unite de l'altitude

    int couleur;                //!<  variable qui stocke l'etat de la led (0 = eteint / 1 = rouge / 2 = vert / 3 = orange
};

#endif // SONDE_H
