#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <unistd.h>

#include <qbluetoothaddress.h>
#include <qbluetoothservicediscoveryagent.h>
#include <QLowEnergyController>
#include <QBluetoothLocalDevice>
#include <QBluetoothSocket>

#include "sonde.h"
#include "gps.h"

class Sonde;
class Gps;

/**
 * @file transmission.h
 * @brief Declaration de la classe Transmission
 *
 * @version 4.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @todo Implémenter la communication WiFi avec la sonde
 */

/**
* @class Transmission transmission.h "transmission.h"
*
* @brief Declaration de la classe Transmission (Liaison série et Bluetooth)
*/
class Transmission : public QObject
{
    Q_OBJECT
public:
    explicit Transmission(QObject *parent = nullptr);        /** constructeur de la classe Transmission */
    ~Transmission();                                         /** destructeur de la classe Transmission */

    QString getTrame() const;                                /** recuperer la trame */
    Sonde *getSonde() const;                                 /** recuperer l'objet sonde */
    Gps *getGps() const;                                     /** recuperer l'objet gps */
    QStringList getAppareilDisponible() const;               /** recuperer les appareils disponibles */
    QString getStatutBluetooth() const;                      /** recuperer les message de statut de la connexion */
    void setStatutBluetooth(QString statutBluetooth);        /** modifier le statut de la connexion Bluetooth */
    void setAppareilDisponible(QString appareilDisponible);  /** modifier la liste des appareils Bluetooth disponibles */

    void configurerPort(QString portCommunication, QString DebitBaud, QString BitsDonnees, QString BitsStop);  /** configurer le port de transmission de la sonde */
    void configurerPortGps(QString portCommunication, QString DebitBaud, QString BitsDonnees, QString BitsStop);  /** configurer le port de transmission pour le GPS */
    void fermerPort();                                   /** fermer le port de transmission de la sonde */
    void fermerPortGps();                                /** fermer le port GPS de transmission */
    void envoyerDonnees(QString envoyerTrame);           /** envoyer des données sur le port serie */
    void ouvrirPort();                                   //!< ouvrir le port série de la Sonde
    void ouvrirPortGps();                                //!< ouvrir le port série pour le GPS
    void demarrerScan();                                 /** demarrer la recherche de périphériques Bluetooth */
    void connecterAppareilBluetooth(QString appareil);   /** connecter un appareil bluetooth */
    void deconnecterAppareilBluetooth();                 /** déconnecter l'appareil bluetooth */

signals:
    void trameSondeRecue();                              //!< signal émis quand une nouvelle trame de l'ESP32 est recue
    void trameGpsRecue();                                //!< signal émis quand une nouvelle trame GPS est recue
    void portOuvert();                                   //!< signal émis quand le port série de la Sonde est ouvert
    void portOuvertGps();                                //!< signal émis quand le port serie du GPS est ouvert
    void portFerme();                                    //!< signal émis quand le port serie de la Sonde est fermé
    void portFermeGps();                                 //!< signal émis quand le port serie du GPS est fermé
    void nouvelleAppareilDisponible();                   //!< signal émis quand un nouvelle appareil est disponible
    void scanfini();                                     //!< signal émis quand le scan est terminé
    void connecter();                                    //!< signal émis quand l'appareil est connecté
    void deconnecter();                                  //!< signal émis quand l'appareil est deconnecté
    void socketErreur();                                 //!< signal émis quand il y a une erreur avec la communication
    void erreurConnectionPortSerieGps(QString message);  //!< signal émis quand il y a une erreur de connexion
    void erreurConnectionPortSerieSonde(QString message);//!< signal émis quand il y a une de connexion

public slots:
    void recevoir();                                             /** methode appelée quand une nouvelle trame et disponible  */
    void recevoirGps();                                          /** methode appelée quand une nouvelle trame du GPS et disponible  */
    void ajouterAppareil(const QBluetoothDeviceInfo &info);      /** methode appelée quand un nouveau appareil est disponible */
    void scanTerminer();                                         /** methode appelée quand le scan est terminé */
    void socketConnected();                                      /** methode appelée quand l'appareil est connecté */
    void socketDisconnected();                                   /** methode appelée quand l'appareil est deconnecté */
    void socketReadyRead();                                      /** methode appelée quand une trame est disponible */

private:
    QString trame;               //!<  stockage de la trame de l'ESP32 recue
    QString trameGps;            //!<  stockage de la trame GPS recue
    QString donneeLatDms;        //!<  stockage des données de latitude en DMS
    QString donneeLongDms;       //!<  stockage des données de longitude en DMS
    double donneLatDD;           //!<  stockage des données de latitude en DD
    double donneLongDD;          //!<  stockage des données de longitude en DD
    QString signeLat;            //!<  stockage du signe de la latitude
    QString signeLong;           //!<  stockage du signe de la longitude

    Sonde* sonde;                           //!< objet sonde
    Gps* gps;                               //!< objet gps
    QSerialPort *portSonde;                 //!< objet portSonde
    QSerialPort *portGps;                   //!< objet portGps
    QBluetoothDeviceDiscoveryAgent *scan;   //!< objet scan
    QLowEnergyController *m_controller;     //!< objet m_controller
    QBluetoothSocket *socket;               //!< objet socket

    QString statutBluetooth;        //!<  stockage du statut de la connexion bluetooth
    void decomposer();              /** decomposition de la trame recue */
    void decomposerDonneeGps();     /** decomposition de la trame GPS recue */
    QStringList appareilDisponible; //!< stockage des appareil bluetooth disponible

};

#endif // TRANSMISSION_H
