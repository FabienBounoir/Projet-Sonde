#include "ihm.h"
#include "ui_ihm.h"

#include <QDebug>

/**
* @file ihm.cpp
*
* @brief classe qui s'occupe de l'affichage dans l'ihm
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.1
*
*/

/**
 * @brief constructeur de la classe Ihm
 *
 * @fn Ihm::Ihm
 * @param parent
 */
Ihm::Ihm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ihm)
{
    ui->setupUi(this);

    initialiserInterface();
    initialiserAffichage();

    transmission = new Transmission(this);
    meteo = new Meteo(this);
    graphique = new Graphique();
    proc = new QProcess();

    initialiserConnect();
}

/**
 * @brief destructeur de la classe Ihm
 *
 * @fn Ihm::~Ihm
 */
Ihm::~Ihm()
{
    enregistrerConfigurationPort();
    delete graphique;
    delete ui;
}

/**
 * @brief initialise les connects
 *
 * @fn Ihm::initialiserConnect
 */
void Ihm::initialiserConnect()
{
    connect(transmission, SIGNAL(trameSondeRecue()), this, SLOT(actualiserTrame()));
    connect(transmission, SIGNAL(trameSondeRecue()), this, SLOT(actualiserDonnee()));
    connect(transmission, SIGNAL(trameGpsRecue()), this, SLOT(actualiserTrame()));
    connect(transmission, SIGNAL(trameGpsRecue()), this, SLOT(actualiserDonneeGps()));

    connect(transmission, SIGNAL(portOuvert()), this, SLOT(desactiverOuverturePort()));
    connect(transmission, SIGNAL(portOuvertGps()), this, SLOT(desactiverOuverturePortGps()));
    connect(transmission, SIGNAL(portFerme()), this, SLOT(desactiverFermerPort()));
    connect(transmission, SIGNAL(portFermeGps()), this, SLOT(desactiverFermerPortGps()));

    connect(meteo, SIGNAL(donnerMeteoMiseAJour()), this, SLOT(actualiserAffichageMeteo()));
    connect(transmission, SIGNAL(nouvelleAppareilDisponible()), this, SLOT(mettreAjourAppareilBluetoothDisponible()));
    connect(transmission, SIGNAL(scanfini()), this, SLOT(actualiserAffichageBluetooth()));
    connect(transmission, SIGNAL(connecter()), this, SLOT(actualiserMessageStatutConnecterBluetooth()));
    connect(transmission, SIGNAL(deconnecter()), this, SLOT(actualiserMessageStatutDeconnecterBluetooth()));
    connect(transmission, SIGNAL(socketErreur()), this, SLOT(actualiserMessageStatutErreurBluetooth()));
    connect(transmission, SIGNAL(erreurConnectionPortSerieGps(QString)), this, SLOT(actualiserMessageStatutConnectionGps(QString)));
    connect(transmission, SIGNAL(erreurConnectionPortSerieSonde(QString)), this, SLOT(actualiserMessageStatutConnectionSonde(QString)));
}

/**
 * @brief enregistrer la configuration du port dans un fichier .ini
 *
 * @fn Ihm::enregistrerConfigurationPort
 */
void Ihm::enregistrerConfigurationPort()
{
    QSettings configuration("Sonde.ini", QSettings::IniFormat);

    configuration.beginGroup("PortSerieSonde");
    configuration.setValue("Appareil", ui->comboBoxAppareil->currentText());
    configuration.setValue("DebitBauds", ui->comboBoxDebitBaud->currentText());
    configuration.setValue("BitsDonnee", ui->comboBoxBitsDonnees->currentText());
    configuration.setValue("BitsStop", ui->comboBoxBitsStop->currentText());
    configuration.endGroup();

    configuration.beginGroup("PortSerieGps");
    configuration.setValue("Appareil", ui->comboBoxPortSerieGps->currentText());
    configuration.setValue("DebitBauds", ui->comboBoxDebitGps->currentText());
    configuration.setValue("BitsDonnee", ui->comboBoxBitsDonneesGps->currentText());
    configuration.setValue("BitsStop", ui->comboBoxBitsStopGps->currentText());
    configuration.endGroup();
}

/**
 * @brief charger la configuration du port depuis un fichier .ini
 *
 * @fn Ihm::chargerConfigurationPort
 */
void Ihm::chargerConfigurationPort()
{
    QSettings configuration("Sonde.ini", QSettings::IniFormat);

    ui->comboBoxAppareil->setCurrentText(configuration.value("PortSerieSonde/Appareil","/dev/ttyUSB0").toString());
    ui->comboBoxDebitBaud->setCurrentText(configuration.value("PortSerieSonde/DebitBauds","115200").toString());
    ui->comboBoxBitsDonnees->setCurrentText(configuration.value("PortSerieSonde/BitsDonnee","8").toString());
    ui->comboBoxBitsStop->setCurrentText(configuration.value("PortSerieSonde/BitsStop","1").toString());

    ui->comboBoxPortSerieGps->setCurrentText(configuration.value("PortSerieGps/Appareil","/dev/ttyUSB1").toString());
    ui->comboBoxDebitGps->setCurrentText(configuration.value("PortSerieGps/DebitBauds","9600").toString());
    ui->comboBoxBitsDonneesGps->setCurrentText(configuration.value("PortSerieGps/BitsDonnee","8").toString());
    ui->comboBoxBitsStopGps->setCurrentText(configuration.value("PortSerieGps/BitsStop","1").toString());
}

/**
 * @brief initialise l'interface utilisateur
 *
 * @fn Ihm::initialiserInterface
 */
void Ihm::initialiserInterface()
{
    ui->tabWidget->setTabEnabled(ONGLET_MODE_OPERATEUR,false);
    ui->textEditTrame->setReadOnly(true);
    ui->pushButtonFermerPort->setDisabled(true);
    ui->radioButtonLedOff->setDisabled(true);
    ui->radioButtonLedVert->setDisabled(true);
    ui->radioButtonLedRouge->setDisabled(true);
    ui->radioButtonLedOrange->setDisabled(true);
    ui->radioButtonLedOff->setChecked(true);
    ui->ImageEtatLed->setPixmap(QPixmap(LED_OFF));
    ui->labelStatutPortSerieSonde->setText("<font color=\"#bd2c2c\">Sonde déconnectée</font>");
    ui->labelStatutPortSerieGps->setText("<font color=\"#bd2c2c\">GPS déconnecté</font>");

    ui->comboBoxAppareil->addItems(QStringList{"/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3", "/dev/ttyS2", "/dev/ttyS3" });
    ui->comboBoxDebitBaud->addItems(QStringList{"1200", "1800", "2400", "4800", "9600", "19200", "38400", "57600", "115200", "230400", "460800"});
    ui->comboBoxBitsDonnees->addItems(QStringList{"5", "6", "7", "8"});
    ui->comboBoxBitsStop->addItems(QStringList{"1", "2"});

    ui->comboBoxPortSerieGps->addItems(QStringList{"/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3", "/dev/ttyACM0", "/dev/ttyACM2" });
    ui->comboBoxDebitGps->addItems(QStringList{"1200", "1800", "2400", "4800", "9600", "19200", "38400", "57600", "115200", "230400", "460800"});
    ui->comboBoxBitsDonneesGps->addItems(QStringList{"5", "6", "7", "8"});
    ui->comboBoxBitsStopGps->addItems(QStringList{"1", "2"});


    ui->pushButtonFermerPortGps->setDisabled(true);
    ui->pushButtonConnexion->setDisabled(true);
    ui->pushButtonDeconnexion->setDisabled(true);
    ui->lineEditEnvoyerTrame->setDisabled(true);
    ui->pushButtonEnvoyerTrame->setDisabled(true);
    ui->pushButtonEnvoyerCoordonnee->setEnabled(false);
    ui->labelValeurCoordonnee->setText("<font color=\"#bd2c2c\">Connecter un GPS</font>");
    chargerConfigurationPort();

}

/**
 * @brief Méthode appelée lorsque le Bouton quitté est enclenché
 *
 * @fn Ihm::on_pushButtonQuitter_clicked
 */
void Ihm::on_pushButtonQuitter_clicked()
{
    this->close();
    graphique->close();
}

/**
 * @brief Méthode appelée lorsque le case à cocher Mode operateur est enclenché
 *
 * @fn Ihm::on_ModeOperateur_stateChanged
 * @param arg1
 */
void Ihm::on_ModeOperateur_stateChanged(int arg1)
{
    if(arg1 == MODE_OPERATEUR_ACTIVER)
    {
        ui->tabWidget->setTabEnabled(ONGLET_MODE_OPERATEUR,true);
    }
    else
    {
        ui->tabWidget->setTabEnabled(ONGLET_MODE_OPERATEUR,false);
    }
}

/**
 * @brief ajout la nouvelle trame recu dans le mode operateur
 *
 * @fn Ihm::actualiserTrame
 */
void Ihm::actualiserTrame()
{
    QDateTime maintenant = QDateTime::currentDateTime();
    QString heure = maintenant.toString("hh:mm:ss");

    ui->textEditTrame->setTextColor(Qt::red);
    ui->textEditTrame->append(heure + " :");
    ui->textEditTrame->setTextColor(Qt::black);
    ui->textEditTrame->append(transmission->getTrame());
}

/**
 * @brief Méthode qui actualise l'etat de la led dans ihm et change le radiobutton activer en fontion de l'etat
 *
 * @fn Ihm::modifierEtatLed
 */
void Ihm::modifierEtatLed()
{
    switch (transmission->getSonde()->getEtatLed())
          {
             case VALEUR_LED_OFF:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_OFF));
                ui->radioButtonLedOff->setChecked(true);
                break;
             case VALEUR_LED_ROUGE:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_ROUGE));
                ui->radioButtonLedRouge->setChecked(true);
                break;
             case VALEUR_LED_VERT:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_VERT));
                ui->radioButtonLedVert->setChecked(true);
               break;
             case VALEUR_LED_ORANGE:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_ORANGE));
                ui->radioButtonLedOrange->setChecked(true);
               break;
             default:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_OFF));
                ui->radioButtonLedOff->setChecked(true);
          }
}
/**
 * @brief Méthode qui actualise les données de L'ihm
 *
 * @fn Ihm::modifierEtatLed
 */
void Ihm::actualiserDonnee()
{
    QDateTime maintenant = QDateTime::currentDateTime();
    QString heure = maintenant.toString("hh:mm:ss");
    ui->horodatage->setText(heure);

    ui->lcdNumberTemperature->display(transmission->getSonde()->getTemperature());
    ui->lcdNumberHumidite->display(transmission->getSonde()->getHumidite());
    ui->lcdNumberRessentie->display(transmission->getSonde()->getRessentie());
    ui->lcdNumberLuminosite->display(transmission->getSonde()->getLuminosite());
    ui->lcdNumberPression->display(transmission->getSonde()->getPression());
    ui->lcdNumberAltitude->display(transmission->getSonde()->getAltitude());

    ui->labelUniteTemperature->setText(transmission->getSonde()->getTemperatureUnite());
    ui->labelUniteRessenti->setText(transmission->getSonde()->getRessentieUnite());
    ui->labelUniteHumidite->setText(transmission->getSonde()->getHumiditeUnite());
    ui->labelUniteLuminosite->setText(transmission->getSonde()->getLuminositeUnite());
    ui->labelUnitePression->setText(transmission->getSonde()->getPressionUnite());
    ui->labelUniteAltitude->setText(transmission->getSonde()->getAltitudeUnite());

    modifierEtatLed();

    graphique->ajouterDonneeTemperature(transmission->getSonde()->getTemperature());
    graphique->ajouterDonneeHumidite(transmission->getSonde()->getHumidite());
    graphique->ajouterDonneeLuminosite(transmission->getSonde()->getLuminosite());
    graphique->ajouterDonneePression(transmission->getSonde()->getPression());
}


/**
 * @brief bouton qui ouvre le port serie
 *
 * @fn Ihm::on_pushButtonOuvrirPort_clicked
 */
void Ihm::on_pushButtonOuvrirPort_clicked()
{
    transmission->configurerPort(ui->comboBoxAppareil->currentText(), ui->comboBoxDebitBaud->currentText(), ui->comboBoxBitsDonnees->currentText(), ui->comboBoxBitsStop->currentText());
}

/**
 * @brief bouton qui ferme le port serie
 *
 * @fn Ihm::on_pushButtonFermerPort_clicked
 */
void Ihm::on_pushButtonFermerPort_clicked()
{
    transmission->fermerPort();
}

/**
 * @brief active la possibilité de contrôler les leds
 *
 * @fn Ihm::ActiverControleLed
 */
void Ihm::ActiverControleLed()
{
    ui->radioButtonLedOff->setDisabled(false);
    ui->radioButtonLedVert->setDisabled(false);
    ui->radioButtonLedRouge->setDisabled(false);
    ui->radioButtonLedOrange->setDisabled(false);
}

/**
 * @brief desactive des bouton de l'Ihm
 *
 * @fn Ihm::desactiverOuverturePort
 */
void Ihm::desactiverOuverturePort()
{
    ui->pushButtonOuvrirPort->setDisabled(true);
    ui->pushButtonFermerPort->setDisabled(false);
    ui->lineEditEnvoyerTrame->setDisabled(false);
    ui->pushButtonEnvoyerTrame->setDisabled(false);
    ui->lineEditEnvoyerTrame->setDisabled(false);
    ui->pushButtonEnvoyerTrame->setDisabled(false);
    ui->comboBoxAppareil->setDisabled(true);
    ui->comboBoxBitsDonnees->setDisabled(true);
    ui->comboBoxBitsStop->setDisabled(true);
    ui->comboBoxDebitBaud->setDisabled(true);
    ui->labelStatutPortSerieSonde->setText("<font color=\"#3498db\">Sonde connectée</font>");

    ActiverControleLed();
}

/**
 * @brief desactive des bouton de l'Ihm
 *
 * @fn Ihm::desactiverOuverturePortGps
 */
void Ihm::desactiverOuverturePortGps()
{
    ui->pushButtonOuvrirPortGps->setDisabled(true);
    ui->pushButtonFermerPortGps->setDisabled(false);
    ui->labelStatutPortSerieGps->setText("<font color=\"#3498db\">GPS connecté</font>");

    ui->comboBoxPortSerieGps->setDisabled(true);
    ui->comboBoxBitsDonneesGps->setDisabled(true);
    ui->comboBoxBitsStopGps->setDisabled(true);
    ui->comboBoxDebitGps->setDisabled(true);
}



/**
 * @brief Désactiver la possibilité de contrôler les leds
 *
 * @fn Ihm::DesactiverControleLed
 */
void Ihm::DesactiverControleLed()
{
    ui->radioButtonLedOff->setDisabled(true);
    ui->radioButtonLedVert->setDisabled(true);
    ui->radioButtonLedRouge->setDisabled(true);
    ui->radioButtonLedOrange->setDisabled(true);
}

/**

 * @brief desactive des bouton de l'Ihm
 *
 * @fn Ihm::desactiverFermerPort
 */
void Ihm::desactiverFermerPort()
{
    ui->pushButtonOuvrirPort->setDisabled(false);
    ui->pushButtonFermerPort->setDisabled(true);
    ui->lineEditEnvoyerTrame->setDisabled(true);
    ui->pushButtonEnvoyerTrame->setDisabled(true);
    initialiserAffichage();
    ui->labelStatutPortSerieSonde->setText("<font color=\"#bd2c2c\">Sonde déconnectée</font>");
    ui->comboBoxAppareil->setDisabled(false);
    ui->comboBoxBitsDonnees->setDisabled(false);
    ui->comboBoxBitsStop->setDisabled(false);
    ui->comboBoxDebitBaud->setDisabled(false);
    DesactiverControleLed();
}

/**
 * @brief desactive des bouton de l'Ihm
 *
 * @fn Ihm::desactiverFermerPortGps
 */
void Ihm::desactiverFermerPortGps()
{
    ui->pushButtonOuvrirPortGps->setDisabled(false);
    ui->pushButtonFermerPortGps->setDisabled(true);
    ui->labelValeurCoordonnee->setText("<font color=\"#bd2c2c\">Connecter un GPS</font>");
    ui->labelStatutPortSerieGps->setText("<font color=\"#bd2c2c\">GPS déconnecté</font>");
    ui->comboBoxPortSerieGps->setDisabled(false);
    ui->comboBoxBitsDonneesGps->setDisabled(false);
    ui->comboBoxBitsStopGps->setDisabled(false);
    ui->comboBoxDebitGps->setDisabled(false);
}

/**
 * @brief   remet les lcdNumber a zero quand le port est fermer
 *
 * @fn Ihm::initialiserAffichage
 */
void Ihm::initialiserAffichage()
{
    ui->lcdNumberTemperature->display("----");
    ui->lcdNumberHumidite->display("----");
    ui->lcdNumberRessentie->display("----");
    ui->lcdNumberLuminosite->display("----");
    ui->lcdNumberPression->display("----");
    ui->lcdNumberAltitude->display("----");

    ui->ImageEtatLed->setPixmap(QPixmap(LED_OFF));
}

/**
 * @brief fonction qui actualise les différente donné de la météo
 *
 * @fn Ihm::actualiserAffichageMeteo
 */
void Ihm::actualiserAffichageMeteo()
{
    ui->lineEditVille->setText(meteo->getVille());
    ui->lcdNumberTemperatureMeteo->display(meteo->getTemperature());
    ui->lcdNumberHumiditeMeteo->display(meteo->getHumidite());
    ui->lcdNumberRessentieMeteo->display(meteo->getRessentie());
    ui->lcdNumberPressionMeteo->display(meteo->getPression());
    ui->lcdNumberTempMinMeteo->display(meteo->getTemperatureMin());
    ui->lcdNumberTempMaxMeteo->display(meteo->getTemperatureMax());
}

/**
 * @brief recuperer le texte de la lineEdit dans l'onglet operateur pour l'envoyer par le port serie
 *
 * @fn Ihm::on_pushButtonEnvoyerTrame_clicked
 */
void Ihm::on_pushButtonEnvoyerTrame_clicked()
{
    if(ui->lineEditEnvoyerTrame->text() != "")
    {
        transmission->envoyerDonnees(ui->lineEditEnvoyerTrame->text());
    }
}

/**
 * @brief envoit une trame pour allumer la led en rouge
 *
 * @fn Ihm::on_radioButtonLedRouge_clicked
 */
void Ihm::on_radioButtonLedRouge_clicked()
{
    transmission->envoyerDonnees("SET LED 1");
}

/**
 * @brief envoit une trame pour allumer la led en vert
 *
 * @fn Ihm::on_radioButtonLedVert_clicked
 */
void Ihm::on_radioButtonLedVert_clicked()
{
    transmission->envoyerDonnees("SET LED 2");
}

/**
 * @brief  envoit une trame pour allumer la led en orange
 *
 * @fn Ihm::on_radioButtonLedOrange_clicked
 */
void Ihm::on_radioButtonLedOrange_clicked()
{
    transmission->envoyerDonnees("SET LED 3");
}

/**
 * @brief  envoit une trame pour eteindre la led
 *
 * @fn Ihm::on_radioButtonLedOff_clicked
 */
void Ihm::on_radioButtonLedOff_clicked()
{
    transmission->envoyerDonnees("SET LED off");
}


/**
 * @brief fonction qui envoit la ville contenue dans la line edit
 *
 * @fn Ihm::on_pushButtonVille_clicked
 */
void Ihm::on_pushButtonVille_clicked()
{
    if(ui->lineEditVille->text() != "")
    {
        meteo->creerUrlVille(ui->lineEditVille->text());
    }
}

/**
 * @brief fonction qui met a jour les appareil bluetooth disponible
 *
 * @fn Ihm::mettreAjourAppareilBluetoothDisponible
 */
void Ihm::mettreAjourAppareilBluetoothDisponible()
{
     ui->comboBoxBluetooth->clear();
     ui->comboBoxBluetooth->addItems(transmission->getAppareilDisponible());
}

/**
 * @brief fonction appelée quand le bouton scan est cliqué
 *
 * @fn Ihm::on_pushButtonScan_clicked
 */
void Ihm::on_pushButtonScan_clicked()
{
    ui->comboBoxBluetooth->clear();
    ui->pushButtonScan->setEnabled(false);
    ui->pushButtonConnexion->setEnabled(false);
    ui->pushButtonDeconnexion->setEnabled(false);
    ui->labelStatut->setText("<font color=\"#bd2c2c\">Recherche en cours ...</font>");

    transmission->demarrerScan();
}

/**
 * @brief fonction qui actualise l'affichage de la parti bluetooth
 *
 * @fn Ihm::actualiserAffichageBluetooth
 */
void Ihm::actualiserAffichageBluetooth()
{
    ui->pushButtonScan->setEnabled(true);
    ui->pushButtonConnexion->setEnabled(true);
    ui->labelStatut->setText("<font color=\"#19B2AD\">Recherche terminée</font>");
}

/**
 * @brief fonction appelée quand le bouton connexion est cliqué
 *
 * @fn Ihm::on_pushButtonConnexion_clicked
 */
void Ihm::on_pushButtonConnexion_clicked()
{
    if(ui->comboBoxBluetooth->currentText() != "")
    {
        ui->labelStatut->setText("<font color=\"#21618c\">Connexion en cours ...</font>");
        transmission->connecterAppareilBluetooth(ui->comboBoxBluetooth->currentText());
    }
}

/**
 * @brief fonction qui actualiser dans l'ihm le statut de la connexion avec l'appareil
 *
 * @fn Ihm::actualiserMessageStatutConnecterBluetooth
 */
void Ihm::actualiserMessageStatutConnecterBluetooth()
{
    ui->labelStatut->setText("<font color=\"#f39c12\">" + transmission->getStatutBluetooth() + "</font>");

    proc->execute("notify-send --icon=/usr/share/icons/hicolor/48x48/apps/bluetooth.png \"" + transmission->getStatutBluetooth() + "\" ");

    ui->pushButtonConnexion->setEnabled(false);
    ui->pushButtonScan->setEnabled(false);
    ui->pushButtonDeconnexion->setEnabled(true);
    ui->lineEditEnvoyerTrame->setDisabled(false);
    ui->pushButtonEnvoyerTrame->setDisabled(false);
    //desactiverConnexionPortSerie();
    ActiverControleLed();
}

/**
 * @brief met à jour le message de statut pour afficher que l'appareil est déconnecter
 *
 * @fn Ihm::actualiserMessageStatutDeconnecterBluetooth
 */
void Ihm::actualiserMessageStatutDeconnecterBluetooth()
{
    ui->labelStatut->setText("<font color=\"#7329b9\">" + transmission->getStatutBluetooth() + "</font>");

    proc->execute("notify-send --icon=/usr/share/icons/hicolor/48x48/apps/bluetooth.png \"" + transmission->getStatutBluetooth() + "\" ");

    ui->pushButtonConnexion->setEnabled(true);
    ui->pushButtonScan->setEnabled(true);
    ui->pushButtonDeconnexion->setEnabled(false);
    ui->lineEditEnvoyerTrame->setDisabled(true);
    ui->pushButtonEnvoyerTrame->setDisabled(true);
    initialiserAffichage();
    DesactiverControleLed();
}

/**
 * @brief met à jour le message de statut pour afficher une erreur
 *
 * @fn Ihm::actualiserMessageStatutErreurBluetooth
 */
void Ihm::actualiserMessageStatutErreurBluetooth()
{
    ui->labelStatut->setText("<font color=\"#7329b9\">" + transmission->getStatutBluetooth() + "</font>");
}

/**
 * @brief Méthode appelée quand on clique sur le bouton deconnexion elle réactive la possibilité de se connecter en port série
 *
 * @fn Ihm::on_pushButtonDeconnexion_clicked
 */
void Ihm::on_pushButtonDeconnexion_clicked()
{
    transmission->deconnecterAppareilBluetooth();
    //activerConnexionPortSerie();
}

/**
 * @brief active des objet de l'interface quand la connexion bluetooth est activer
 *
 * @fn Ihm::desactiverConnexionPortSerie
 */
void Ihm::desactiverConnexionPortSerie()
{
    ui->comboBoxAppareil->setDisabled(true);
    ui->comboBoxDebitBaud->setDisabled(true);
    ui->comboBoxBitsDonnees->setDisabled(true);
    ui->comboBoxBitsStop->setDisabled(true);
    ui->pushButtonOuvrirPort->setDisabled(true);
    ui->pushButtonFermerPort->setDisabled(true);
}

/**
 * @brief désactive des objet de l'interface quand la connexion bluetooth est activer
 *
 * @fn Ihm::activerConnexionPortSerie
 */
void Ihm::activerConnexionPortSerie()
{
    ui->comboBoxAppareil->setDisabled(false);
    ui->comboBoxDebitBaud->setDisabled(false);
    ui->comboBoxBitsDonnees->setDisabled(false);
    ui->comboBoxBitsStop->setDisabled(false);
    ui->pushButtonOuvrirPort->setDisabled(false);
}

/**
 * @brief active des objet de l'interface quand la connexion bluetooth est activer
 *
 * @fn Ihm::desactiverConnexionBluetooth
 */
void Ihm::desactiverConnexionBluetooth()
{
    ui->comboBoxBluetooth->setDisabled(true);
    ui->pushButtonScan->setDisabled(true);
    ui->pushButtonConnexion->setDisabled(true);
    ui->pushButtonDeconnexion->setDisabled(true);
    ui->labelStatut->setText("<font color=\"#63cb23\">Connexion en cours ...</font>");

}

/**
 * @brief désactive des objet de l'interface quand la connexion bluetooth est activer
 *
 * @fn Ihm::activerConnexionBluetooth
 */
void Ihm::activerConnexionBluetooth()
{
    ui->comboBoxBluetooth->setDisabled(false);
    ui->pushButtonScan->setDisabled(false);
    ui->pushButtonConnexion->setDisabled(false);
    ui->pushButtonDeconnexion->setDisabled(false);
    ui->labelStatut->setText("");
}

/**
 * @brief
 *
 * @fn Ihm::on_pushButtonGraphique_clicked
 */
void Ihm::on_pushButtonGraphique_clicked()
{
    graphique->show();
}

/**
 * @brief
 *
 * @fn Ihm::on_checkBoxPleinEcran_stateChanged
 * @param arg1
 */
void Ihm::on_checkBoxPleinEcran_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        showFullScreen();
    }
    else
    {
        showNormal();
    }
}

/**
 * @brief
 *
 * @fn Ihm::actualiserDonneeGps
 */
void Ihm::actualiserDonneeGps()
{
    ui->labelValeurCoordonnee->setText(QString::number(transmission->getGps()->getLatitude()) + " " + QString::number(transmission->getGps()->getLongitude()));
    ui->pushButtonEnvoyerCoordonnee->setEnabled(true);
}

/**
 * @brief
 *
 * @fn Ihm::on_pushButtonEnvoyerCoordonnee_clicked
 */
void Ihm::on_pushButtonEnvoyerCoordonnee_clicked()
{
    meteo->creerUrlCoordonnerGps(transmission->getGps()->getLatitude(), transmission->getGps()->getLongitude());
}

void Ihm::on_pushButtonOuvrirPortGps_clicked()
{
    transmission->configurerPortGps(ui->comboBoxPortSerieGps->currentText(), ui->comboBoxDebitGps->currentText(), ui->comboBoxBitsDonneesGps->currentText(), ui->comboBoxBitsStopGps->currentText());
}

void Ihm::on_pushButtonFermerPortGps_clicked()
{
    transmission->fermerPortGps();
}

void Ihm::actualiserMessageStatutConnectionGps(QString message)
{
    transmission->fermerPortGps();
    ui->labelStatutPortSerieGps->setText("<font color=\"#8e44ad\">" + message + "</font>");
}

void Ihm::actualiserMessageStatutConnectionSonde(QString message)
{
    transmission->fermerPort();
    ui->labelStatutPortSerieSonde->setText("<font color=\"#8e44ad\">" + message + "</font>");
}
