#include "transmission.h"

/**
* @file transmission.cpp
*
* @brief programme qui s'occupe de la parti trame (configuration, reception / envoie de trame)
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.0
*
*/

/**
 * @brief constructeur de la classe Transmission
 *
 * @fn Transmission::Transmission
 * @param parent
 */
Transmission::Transmission(QObject *parent) : QObject(parent), trame("")
{
    esp32 = new Esp32(this);
    port = new QSerialPort(this);
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
    deconnecterAppareilBluetooth();
}

/**
 * @brief return la trame stockée
 *
 * @fn Transmission::getTrame
 * @return QString
 */
QString Transmission::getTrame() const
{
    return trame;
}

/**
 * @brief return l'objet Esp32
 *
 * @fn Transmission::getEsp32
 * @return Esp32
 */
Esp32* Transmission::getEsp32() const
{
    return esp32;
}

/**
 * @brief return une liste des appareil bluetooth disponible
 *
 * @fn Transmission::getAppareilDisponible
 * @return QStringList
 */
QStringList Transmission::getAppareilDisponible() const
{
    return appareilDisponible;
}

/**
 * @brief return la statut de la connexion avec l'appareil bluetooth
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
 * @brief ajoute un appareil a la liste des appareilDisponible
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
    port->open(QIODevice::ReadWrite);
    if(port->isOpen())
    {
        qDebug() << __FUNCTION__ << ": " <<"Le port est ouvert";

        connect(port, SIGNAL(readyRead()), this, SLOT(recevoir()));
        emit portOuvert();
    }
    else
    {
        qDebug() << __FUNCTION__ << ": " << "Erreur, le port n'a pas pu être ouvert";
    }
}

/**
 * @brief configurer le port de communication
 *
 * @fn Transmission::configurerPort
 */
void Transmission::configurerPort(QString portCommunication, QString DebitBaud, QString BitsDonnees, QString BitsStop)
{
    port = new QSerialPort(portCommunication);

    port->setBaudRate(DebitBaud.toInt());
    port->setDataBits(QSerialPort::DataBits(BitsDonnees.toInt()));
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::StopBits(BitsStop.toInt()));
    port->setFlowControl(QSerialPort::NoFlowControl);

    ouvrirPort();
}

/**
 * @brief cette methode ferme le port serie
 *
 * @fn Transmission::fermerPort
 */
void Transmission::fermerPort()
{
    if(port->isOpen())
    {
        port->close();

        qDebug() << __FUNCTION__ << ": " <<"port fermer" <<endl;

        emit portFerme();
    }
}

/**
 * @brief   Décompose la trame reçue
 *
 * @fn Transmission::decomposer
 */
void Transmission::decomposer()
{
    if(trame.startsWith("SONDE") && trame.endsWith("\r\n"))
    {
        esp32->setTemperature(trame.section(";",1,1).toDouble());
        esp32->setTemperatureUnite(trame.section(";",2,2));
        esp32->setRessentie(trame.section(";",3,3).toDouble());
        esp32->setRessentieUnite(trame.section(";",4,4));
        esp32->setHumidite(trame.section(";",5,5).toInt());
        esp32->setHumiditeUnite(trame.section(";",6,6));
        esp32->setLuminosite(trame.section(";",7,7).toInt());
        esp32->setLuminositeUnite(trame.section(";",8,8));
        esp32->setPression(trame.section(";",9,9).toInt());
        esp32->setPressionUnite(trame.section(";",10,10));
        esp32->setAltitude(trame.section(";",11,11).toInt());
        esp32->setAltitudeUnite(trame.section(";",12,12));
        esp32->setCouleurLed(trame.section(";",17,17).toInt());
    }
    emit trameRecue();
}

/**
 * @brief Récupérer la trame émise
 *
 * @fn Transmission::recevoir
 */
void Transmission::recevoir()
{
        //trame = "$GPGGA,221938.000,4354.1123,N,00448.9145,E,2,08,1.15,26.9,M,49.2,M,0000,0000*55 \
        $GPGSA,A,3,20,26,31,29,10,21,16,27,,,,,1.93,1.15,1.55*02 \
        $GPRMC,221938.000,A,4354.1123,N,00448.9145,E,0.02,20.76,150120,,,D*58 \
        $GPVTG,20.76,T,,M,0.02,N,0.04,K,D*0D"

    QByteArray donnees;
        qDebug() << Q_FUNC_INFO;
        while(port->waitForReadyRead(10))
        {
            donnees += port->readAll();
        }
        trame = QString(donnees.data());

        if(trame.startsWith("SONDE") && trame.endsWith("\r\n"))
        {
            qDebug() << "trame Port serie reçu : " << trame << endl;

            this->decomposer();
        }

        if(trame.startsWith("$GPGGA") && trame.endsWith("\r\n"))    /** @todo decomposer la trame Gps = https://www.generationrobots.com/fr/401920-adafruit-ultimate-gps-breakout-66-canaux-avec-mise-a-jour10-hz-v3.html**/
        {
            qDebug() << "trame Gps reçu : " << trame << endl;
            this->decomposer();  /** @todo a changer**/
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
    if(port->isOpen())
    {
        const char* trame = envoyerTrame.toStdString().c_str();
        port->write(trame);

        qDebug() << __FUNCTION__ << ": " << trame << endl;
    }
    else if(socket->isOpen())
    {
        const char* trame = envoyerTrame.toStdString().c_str();
        socket->write(trame);

        qDebug() << __FUNCTION__ << ": " << trame << endl;
    }
    else
    {
        qDebug() << __FUNCTION__ << " port non ouvert" << endl;
        qDebug() << __FUNCTION__ << " connexion bluetooth non ouvert" <<endl;
        emit portFerme();
    }
}

/**
 * @brief cette fonction scan les appareils disponible
 *
 * @fn Transmission::demarrerScan
 */
void Transmission::demarrerScan()
{
    appareilDisponible.clear();
    scan->start();
}

/**
 * @brief ajout les appareil trouver dans une list pour les afficher dans l'IHM
 *
 * @fn Transmission::ajouterAppareil
 * @param info
 */
void Transmission::ajouterAppareil(const QBluetoothDeviceInfo &info)
{
    //QString appareilDisponible = QString("%1 %2").arg(info.address().toString()).arg(info.name());
    QString appareilDisponible = info.address().toString();

    qDebug() << "Appareil Bluetooth trouvé :" << QString("%1 %2").arg(info.address().toString()).arg(info.name()) << endl;

    setAppareilDisponible(appareilDisponible);
}

/**
 * @brief fonction appeler quand le scan est fini
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
 * @brief Permets de se connecter à un appareil.
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
 * @brief methode qui deconnecte l'appareil bluetooth connecter
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
    QString message = QString::fromUtf8("Périphérique déconnecté");
    qDebug() << message;
    setStatutBluetooth(message);
    emit deconnecter();
}

/**
 * @brief methode appeler quand une trame est disponible
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

