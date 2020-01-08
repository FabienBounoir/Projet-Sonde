#ifndef ESP32_H
#define ESP32_H

#include <QObject>
#include <QString>
#include <QtDebug>

/**
 * @file esp32.h
 *
 * @brief Declaration de la classe Esp32
 *
 * @version 3.0
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @class Esp32 esp32.h "esp32.h"
 *
 * @brief Declaration de la classe Esp32
*/
class Esp32 : public QObject
{
    Q_OBJECT
public:
    explicit Esp32(QObject *parent = nullptr);

    double getTemperature() const;                          /** recuperer la temperature */
    double getRessentie() const;                            /** recuperer le ressentie*/
    QString getTemperatureUnite() const;                    /** recuperer l'unite de temperature*/
    QString getRessentieUnite() const;                      /** recuperer l'unite du resssentie*/
    int getHumidite() const;                                /** recuperer l'humidite*/
    int getLuminosite() const;                              /** recuperer la luminosite*/
    QString getHumiditeUnite() const;                       /** recuperer l'unite d'humidite*/
    QString getLuminositeUnite() const;                     /** recuperer l'unite de luminosite*/
    int getPression() const;                                /** recuperer la pression*/
    QString getPressionUnite() const;                       /** recuperer l'unite de pression*/
    int getAltitude() const;                                /** recuperer l'altitude*/
    QString getAltitudeUnite() const;                       /** recuperer l'unite d'altitude*/
    int getEtatLed() const;                                 /** recuperer l'etat de la led*/


    void setTemperature(double temperature);                /** modifier la valeur de la temperature*/
    void setRessentie(double ressentie);                    /** modifier la valeur de ressenti */
    void setTemperatureUnite(QString temperatureUnite);     /** modifier la valeur de l'uniter de temperature */
    void setRessentieUnite(QString ressentieUnite);         /** modifier la valeur de l'uniter de ressenti */
    void setHumidite(int ressentieUnite);                   /** modifier la valeur de l'humidite */
    void setLuminosite(int luminosite);                     /** modifier la valeur de luminosite */
    void setHumiditeUnite(QString humiditeUnite);           /** modifier la valeur de l'unite d'humidite */
    void setLuminositeUnite(QString luminositeUnite);       /** modifier la valeur de l'unite de luminosite */
    void setPression(int pression);                         /** modifier la valeur de la pression */
    void setPressionUnite(QString pressionUnite);           /** modifier la valeur de l'unite de pression */
    void setAltitude(int altitude);                         /** modifier la valeur d'altitude */
    void setAltitudeUnite(QString altitudeUnite);           /** modifier la valeur de l'unite altitude */
    void setCouleurLed(int couleur);                        /** modifier l'etat de la led */

private:
    double temperature;             /** variable qui stocke la temperature*/
    QString temperatureUnite;       /** variable qui stocke l'unite de la temperature*/

    double ressentie;               /** variable qui stocke le ressenti*/
    QString ressentieUnite;         /** variable qui stocke l'unite de ressenti*/

    int humidite;                   /** variable qui stocke l'humidite*/
    QString humiditeUnite;           /** variable qui stocke l'unite de l'humidite*/

    int luminosite;                 /** variable qui stocke la luminosite*/
    QString luminositeUnite;        /** variable qui stocke l'unite de la luminosite*/

    int pression;                   /** variable qui stocke la pression*/
    QString pressionUnite;          /** variable qui stocke l'unite de pression*/

    int altitude;                   /** variable qui stocke l'altitude*/
    QString altitudeUnite;          /** variable qui stocke l'unite de l'altitude*/

    int couleur;                /** variable qui stocke l'etat de la led (0 = eteint / 1 = rouge / 2 = vert / 3 = orange*/
};

#endif // ESP32_H
