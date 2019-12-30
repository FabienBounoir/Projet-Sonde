#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <unistd.h>
#include "esp32.h"

class Esp32;

/**
 * @file transmission.h
 * @brief Declaration de la classe Transmission
 *
 * @version 2.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @class Transmission transmission.h "transmission.h"
 */

class Transmission : public QObject
{
    Q_OBJECT
public:
    explicit Transmission(QObject *parent = nullptr);   /** constructeur de la classe Transmission*/
    ~Transmission();    /** destructeur de la classe Transmission*/

    QString getTrame() const;     /** recuperer la trame */
    Esp32 *getEsp32() const;      /** recuperer l'objet */

    void configurerPort(QString portCommunication, QString DebitBaud, QString BitsDonnees, QString BitsStop);  /** configurer le port de transmission*/
    void fermerPort();      /** fermer le port de transmission */
    void envoyerDonnees(QString envoyerTrame);  /** envoyer donner sur le port serie */
    void ouvrirPort();      /** Méthode appelée pour ouvrir le port série */

signals:
    void trameRecue();      /** signal emit quand une nouvelle trame est recu*/
    void portOuvert();      /** signal emit quand le port est ouvert */
    void portFerme();      /** signal emit quand le port est fermer */

public slots:
    void recevoir();        /** methode appeler quand une nouvelle trame et disponible  */

private:

    Esp32* esp32;           /** objet esp32 */
    QSerialPort *port;      /** objet port */

    QString trame;          /** stockage de la trame recu */
    void decomposer();      /** decomposition de la trame recu */
};

#endif // TRANSMISSION_H
