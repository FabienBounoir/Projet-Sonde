#include "transmission.h"

/**
* @file transmission.cpp
*
* @brief classe qui s'occupe de la parti trame (configuration, reception / envoie de trame)
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.1
*
*/

/**
 * @brief constructeur de la classe Transmission
 *
 * @fn Transmission::Transmission
 * @param parent
 */
Transmission::Transmission(QObject *parent) : QObject(parent), trame(""), trameGps(""), donneeLatDms(""), donneeLongDms(""), donneLatDD(0.), donneLongDD(0.),\
  signeLat(""), signeLong("")
{
    sonde = new Sonde(this);
    gps = new Gps();
    portSonde = new QSerialPort(this);
    portGps = new QSerialPort(this);
    scan = new QBluetoothDeviceDiscoveryAgent(this);
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(scan, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(ajouterAppareil(QBluetoothDeviceInfo)));
    connect(scan, SIGNAL(finished()), this, SLOT(scanTerminer()));

    demarrerScan();
}

/**
 * @brief destructeur de la classe Transmission
 *
 * @fn Transmission::~Transmission
 */
Transmission::~Transmission()
{
    this->fermerPort();
    delete gps;
    deconnecterAppareilBluetooth();
}

/**
 * @brief retourne la trame stockée
 *
 * @fn Transmission::getTrame
 * @return QString
 */
QString Transmission::getTrame() const
{
    return trame;
}

/**
 * @brief retourne l'objet Sonde
 *
 * @fn Transmission::getSonde
 * @return sonde
 */
Sonde* Transmission::getSonde() const
{
    return sonde;
}

/**
 * @brief retourne l'objet gps
 *
 * @fn Transmission::getGps
 * @return gps
 */
Gps* Transmission::getGps() const
{
    return gps;
}

/**
 * @brief retourne une liste des appareils bluetooth disponibles
 *
 * @fn Transmission::getAppareilDisponible
 * @return QStringList
 */
QStringList Transmission::getAppareilDisponible() const
{
    return appareilDisponible;
}

/**
 * @brief retourne la statut de la connexion avec l'appareil bluetooth
 *
 * @fn Transmission::getStatutBluetooth
 * @return QString
 */
QString Transmission::getStatutBluetooth() const
{
    return statutBluetooth;
}

/**
 * @brief permet de modifier le statut de la connexion avec l'appareil bluetooth
 *
 * @fn Transmission::setStatutBluetooth
 * @param statutBluetooth
 */
void Transmission::setStatutBluetooth(QString statutBluetooth)
{
    this->statutBluetooth = statutBluetooth;
}

/**
 * @brief ajoute un appareil a la liste des appareils disponibles
 *
 * @fn Transmission::setAppareilDisponible
 * @param appareilDisponible
 */
void Transmission::setAppareilDisponible(QString appareilDisponible)
{
    this->appareilDisponible << appareilDisponible;

}

/**
 * @brief configure le port serie
 *
 * @fn Transmission::configurerPort
 */
void Transmission::ouvrirPort()
{
    portSonde->open(QIODevice::ReadWrite);
    if(portSonde->isOpen())
    {
        qDebug() << __FUNCTION__ << ": " <<"Le port est ouvert";

        connect(portSonde, SIGNAL(readyRead()), this, SLOT(recevoir()));
        emit portOuvert();
    }
    else
    {
        qDebug() << __FUNCTION__ << ": " << "Erreur, le port serie de la Sonde n'a pas pu être ouvert";
    }
}

/**
 * @brief configure le port serie pour le Gps
 *
 * @fn Transmission::configurerPortGps
 */
void Transmission::ouvrirPortGps()
{
    portGps->open(QIODevice::ReadWrite);
    if(portGps->isOpen())
    {
        qDebug() << __FUNCTION__ << ": " <<"Le port est ouvert";

        connect(portGps, SIGNAL(readyRead()), this, SLOT(recevoirGps()));
        emit portOuvertGps();
    }
    else
    {
        qDebug() << __FUNCTION__ << ": " << "Erreur, le port serie du GPS n'a pas pu être ouvert";
    }
}

/**
 * @brief configure le port de communication
 *
 * @fn Transmission::configurerPort
 */
void Transmission::configurerPort(QString portCommunication, QString DebitBaud, QString BitsDonnees, QString BitsStop)
{
    portSonde = new QSerialPort(portCommunication);

    portSonde->setBaudRate(DebitBaud.toInt());
    portSonde->setDataBits(QSerialPort::DataBits(BitsDonnees.toInt()));
    portSonde->setParity(QSerialPort::NoParity);
    portSonde->setStopBits(QSerialPort::StopBits(BitsStop.toInt()));
    portSonde->setFlowControl(QSerialPort::NoFlowControl);

    ouvrirPort();
}

/**
 * @brief configure le port de communication Gps
 *
 * @fn Transmission::configurerPortGps
 */
void Transmission::configurerPortGps(QString portCommunication, QString DebitBaud, QString BitsDonnees, QString BitsStop)
{
    portGps = new QSerialPort(portCommunication);

    portGps->setBaudRate(DebitBaud.toInt());
    portGps->setDataBits(QSerialPort::DataBits(BitsDonnees.toInt()));
    portGps->setParity(QSerialPort::NoParity);
    portGps->setStopBits(QSerialPort::StopBits(BitsStop.toInt()));
    portGps->setFlowControl(QSerialPort::NoFlowControl);

    ouvrirPortGps();
}

/**
 * @brief cette methode ferme le port serie
 *
 * @fn Transmission::fermerPort
 */
void Transmission::fermerPort()
{
    if(portSonde->isOpen())
    {
        portSonde->close();

        qDebug() << __FUNCTION__ << ": " <<"port Sonde fermer" <<endl;

        emit portFerme();
    }
}

/**
 * @brief cette methode ferme le port serie
 *
 * @fn Transmission::fermerPortGps
 */
void Transmission::fermerPortGps()
{
    if(portGps->isOpen())
    {
        portGps->close();

        qDebug() << __FUNCTION__ << ": " <<"port Gps fermer" <<endl;

        emit portFermeGps();
    }
}

/**
 * @brief Décompose la trame reçue
 *
 * @fn Transmission::decomposer
 */
void Transmission::decomposer()
{
    if(trame.startsWith("SONDE") && trame.endsWith("\r\n"))
    {
        sonde->setTemperature(trame.section(";",1,1).toDouble());
        sonde->setTemperatureUnite(trame.section(";",2,2));
        sonde->setRessentie(trame.section(";",3,3).toDouble());
        sonde->setRessentieUnite(trame.section(";",4,4));
        sonde->setHumidite(trame.section(";",5,5).toInt());
        sonde->setHumiditeUnite(trame.section(";",6,6));
        sonde->setLuminosite(trame.section(";",7,7).toInt());
        sonde->setLuminositeUnite(trame.section(";",8,8));
        sonde->setPression(trame.section(";",9,9).toInt());
        sonde->setPressionUnite(trame.section(";",10,10));
        sonde->setAltitude(trame.section(";",11,11).toInt());
        sonde->setAltitudeUnite(trame.section(";",12,12));
        sonde->setCouleurLed(trame.section(";",17,17).toInt());
    }
    emit trameSondeRecue();
}

/**
 * @brief   Décompose la trame gps pour avoir la latitude et la longitude
 *
 * @fn Transmission::decomposerDonneeGps
 */
void Transmission::decomposerDonneeGps()
{
    if(trameGps.startsWith("$GPGGA") && trameGps.endsWith("\r\n"))
    {
        donneeLatDms = trameGps.section(",",2,2);
        donneeLongDms = trameGps.section(",",4,4);
        signeLat = trameGps.section(",",3,3);
        signeLong = trameGps.section(",",5,5);

        if(signeLat == "N")
        {
            donneLatDD = donneeLatDms.left(2).toDouble() + donneeLatDms.mid(2,2).toDouble()/60 + donneeLatDms.mid(5,2).toDouble()/3600;
            qDebug() << "latitude DD:" << donneLatDD << endl;
            gps->setLatitude(donneLatDD);
        }
        else if(signeLong == "S")
        {
            donneLatDD = donneeLatDms.left(2).toDouble() + donneeLatDms.mid(2,2).toDouble()/60 + donneeLatDms.mid(5,2).toDouble()/3600;
            qDebug() << "latitude DD:" << donneLatDD * -1 << endl;
            gps->setLatitude(donneLatDD * -1);
        }

        if(signeLong == "E")
        {
            donneLongDD = donneeLongDms.left(3).toDouble() + donneeLongDms.mid(2,2).toDouble()/60 + donneeLongDms.mid(5,2).toDouble()/3600;
            qDebug() << "longitude DD:" << donneLongDD << endl;
            gps->setLongitude(donneLongDD);
        }
        else if(signeLat == "W")
        {
            donneLongDD = donneeLongDms.left(3).toDouble() + donneeLongDms.mid(2,2).toDouble()/60 + donneeLongDms.mid(5,2).toDouble()/3600;
            qDebug() << "longitude DD:" << donneLongDD * -1 << endl;
            gps->setLongitude(donneLongDD * -1);
        }
    }
    emit trameGpsRecue();
}

/**
 * @brief Récupérer les données reçues sur le port série
 *
 * @fn Transmission::recevoir
 */
void Transmission::recevoir()
{
    QByteArray donnees;

        while(portSonde->waitForReadyRead(10))
        {
            donnees += portSonde->readAll();
        }
        trame = QString(donnees.data());

        if(trame.startsWith("SONDE") && trame.endsWith("\r\n"))
        {
            qDebug() << Q_FUNC_INFO << "trame Port serie reçu : " << trame << endl;

            this->decomposer();
        }else if(trame.startsWith("$GPGGA") && trame.endsWith("\r\n"))
        {
            qDebug() << Q_FUNC_INFO << "mauvais module connecté" << endl;
            emit erreurConnectionPortSerieSonde("Erreur Appareil Connecté");
        }

}

/**
 * @brief Récupérer la trame émise par le Gps
 *
 * @fn Transmission::recevoirGps
 */
void Transmission::recevoirGps()
{
    QByteArray donnees;

        while(portGps->waitForReadyRead(10))
        {
            donnees += portGps->readAll();
        }
        trameGps = QString(donnees.data());

        if(trameGps.startsWith("$GPGGA") && trameGps.endsWith("\r\n"))
        {
            qDebug() << Q_FUNC_INFO << "trame Gps reçu : " << trameGps << endl;
            this->decomposerDonneeGps();
        }else if(trameGps.startsWith("SONDE") && trameGps.endsWith("\r\n"))
        {
            qDebug() << Q_FUNC_INFO << "mauvais module connecté" << endl;
            emit erreurConnectionPortSerieGps("Erreur Appareil Connecté");
        }
}

/**
 * @brief envoyer les données par le port serie ou bluetooth suivant le mode choisie
 *
 * @fn Transmission::envoyerDonnees
 * @param envoyerTrame
 */
void Transmission::envoyerDonnees(QString envoyerTrame)
{
    if(portSonde->isOpen())
    {
        const char* trame = envoyerTrame.toStdString().c_str();
        portSonde->write(trame);

        qDebug() << __FUNCTION__ << ": " << trame << endl;
    }

    if(socket->isOpen())
    {
        const char* trame = envoyerTrame.toStdString().c_str();
        socket->write(trame);

        qDebug() << __FUNCTION__ << ": " << trame << endl;
    }

    if(!socket->isOpen() && !portSonde->isOpen())
    {
        emit portFerme();
    }
}

/**
 * @brief cette fonction recherche les appareils disponibles
 *
 * @fn Transmission::demarrerScan
 */
void Transmission::demarrerScan()
{
    qDebug() << "scan en cours..." << endl;
    appareilDisponible.clear();
    scan->start();
}

/**
 * @brief ajoute les appareils trouvés dans une liste pour les afficher dans l'IHM
 *
 * @fn Transmission::ajouterAppareil
 * @param info
 */
void Transmission::ajouterAppareil(const QBluetoothDeviceInfo &info)
{
    QString appareilDisponible = info.address().toString();

    qDebug() << "Appareil Bluetooth trouvé :" << QString("%1 %2").arg(info.address().toString()).arg(info.name()) << endl;

    setAppareilDisponible(appareilDisponible);
}

/**
 * @brief fonction appelée quand le scan est fini
 *
 * @fn Transmission::scanTerminer
 */
void Transmission::scanTerminer()
{
    qDebug() << "scan terminé";
    emit scanfini();
    emit nouvelleAppareilDisponible();
}

/**
 * @brief Permet de se connecter à un appareil
 *
 * @fn Transmission::connecterAppareilBluetooth
 * @param appareil
 */
void Transmission::connecterAppareilBluetooth(QString appareil)
{
    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
        [=](QBluetoothSocket::SocketError error)
    {
        qDebug() <<__FUNCTION__ << error;
        setStatutBluetooth("Erreur");
        emit socketErreur();
    });

    QBluetoothAddress adresse = QBluetoothAddress(appareil);
    QBluetoothUuid uuid = QBluetoothUuid(QBluetoothUuid::SerialPort);
    socket->connectToService(adresse, uuid);
    socket->open(QIODevice::ReadWrite);
}

/**
 * @brief methode qui deconnecte l'appareil bluetooth connecté
 *
 * @fn Transmission::deconnecterAppareilBluetooth
 */
void Transmission::deconnecterAppareilBluetooth()
{
    if (socket->isOpen())
        {
            socket->close();
        }
}

/**
 * @brief fonction appelée quand l'appareil est connecté
 *
 * @fn Transmission::socketConnected
 */
void Transmission::socketConnected()
{
    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Périphérique connecté ") + socket->peerName() + " [" + socket->peerAddress().toString() + "]";
    QString message = "connecter à " + socket->peerName();
    setStatutBluetooth(message);
    emit connecter();
}

/**
 * @brief fonction appelée quand l'appareil est deconnecté
 *
 * @fn Transmission::socketDisconnected
 */
void Transmission::socketDisconnected()
{
    qDebug() << Q_FUNC_INFO;
    QString message = "Périphérique déconnecté";
    qDebug() << message;
    setStatutBluetooth(message);
    emit deconnecter();
}

/**
 * @brief methode appelée quand une trame est disponible
 *
 * @fn Transmission::socketReadyRead
 */
void Transmission::socketReadyRead()
{
    qDebug() << Q_FUNC_INFO;
    QByteArray donnees;

    while (socket->bytesAvailable())
    {
        donnees += socket->readAll();
        usleep(150000); // cf. timeout
    }
    trame = QString(donnees);
    qDebug() << "Données bluetooth reçues :" << QString(donnees);

    if(trame.startsWith("SONDE") && trame.endsWith("\r\n"))
    {
        decomposer();
    }
}

