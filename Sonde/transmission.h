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

#include "esp32.h"

class Esp32;

/**
 * @file transmission.h
 * @brief Declaration de la classe Transmission
 *
 * @version 4.0
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
* @class Transmission transmission.h "transmission.h"
*
* @brief Declaration de la classe Transmission
*/
class Transmission : public QObject
{
    Q_OBJECT
public:
    explicit Transmission(QObject *parent = nullptr);    /** constructeur de la classe Transmission*/
    ~Transmission();                                     /** destructeur de la classe Transmission*/

    QString getTrame() const;                            /** recuperer la trame */
    Esp32 *getEsp32() const;                             /** recuperer l'objet */
    QStringList getAppareilDisponible() const;               /** recuperer les appareil disponible */
    QString getStatutBluetooth() const;                      /** recuperer les message de statut de la connexion */
    void setStatutBluetooth(QString statutBluetooth);        /** modifier le statut de la connexion bluetooth */
    void setAppareilDisponible(QString appareilDisponible);  /** modifier la liste des appareil bluetooth disponible*/

    void configurerPort(QString portCommunication, QString DebitBaud, QString BitsDonnees, QString BitsStop);  /** configurer le port de transmission*/
    void fermerPort();                                   /** fermer le port de transmission */
    void envoyerDonnees(QString envoyerTrame);           /** envoyer donner sur le port serie */
    void ouvrirPort();                                   /** Méthode appelée pour ouvrir le port série */
    void demarrerScan();                                 /** methode appelée pour demarrer le scan*/
    void connecterAppareilBluetooth(QString appareil);   /** methode appelée pour connecter un appareil bluetooth */
    void deconnecterAppareilBluetooth();                 /** methode appelée pour deconnecter l'appareil bluetooth**/

signals:
    void trameRecue();                                   /** signal emit quand une nouvelle trame est recu*/
    void portOuvert();                                   /** signal emit quand le port est ouvert */
    void portFerme();                                    /** signal emit quand le port est fermer */
    void nouvelleAppareilDisponible();                   /** signal emit quand un nouvelle appareil est disponible */
    void scanfini();                                     /** signal emit quand le scan est terminé*/
    void connecter();                                    /** signal emit quand l'appareil est connecté*/
    void deconnecter();                                  /** signal emit quand l'appareil est deconnecté*/
    void socketErreur();                                 /** signal emit quand il y a une erreur avec la communication*/


public slots:
    void recevoir();                                             /** methode appeler quand une nouvelle trame et disponible  */
    void ajouterAppareil(const QBluetoothDeviceInfo &info);      /** methode appeler quand de nouveau appareil son disponible */
    void scanTerminer();                                         /** methode appeler quand le scan est terminé */
    void socketConnected();                                      /** methode appeler quand l'appareil est connecté */
    void socketDisconnected();                                   /** methode appeler quand l'appareil est deconnecté*/
    void socketReadyRead();                                      /** methode appeler quand une trame est disponible */

private:

    Esp32* esp32;                           //!< objet esp32
    QSerialPort *port;                      //!< objet port
    QBluetoothDeviceDiscoveryAgent *scan;   //!< objet scan
    QLowEnergyController *m_controller;     //!< objet m_controller
    QBluetoothSocket *socket;               //!< objet socket

    QString trame;                  /** stockage de la trame recu */
    QString statutBluetooth;        /** stockage du statut de la connexion bluetooth */
    void decomposer();              /** decomposition de la trame recu */
    QStringList appareilDisponible; /** stockage des appareil bluetooth disponible*/

};

#endif // TRANSMISSION_H
