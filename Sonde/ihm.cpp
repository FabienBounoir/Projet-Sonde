#include "ihm.h"
#include "ui_ihm.h"

#include <QDebug>

#define MODE_OPERATEUR_ACTIVER 2
#define ONGLET_MODE_OPERATEUR 3
#define LED_ROUGE "../Sonde/image/ledRouge.png"
#define LED_VERT "../Sonde/image/ledVert.png"
#define LED_ORANGE "../Sonde/image/ledOrange.png"
#define LED_OFF "../Sonde/image/ledEteint.png"

/**
* @file ihm.cpp
*
* @brief programme qui s'occupe de l'affichage dans l'ihm
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 2.1
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

    connect(transmission, SIGNAL(trameRecue()), this, SLOT(actualiserTrame()));
    connect(transmission, SIGNAL(trameRecue()), this, SLOT(actualiserDonnee()));
    connect(transmission, SIGNAL(portOuvert()), this, SLOT(desactiverOuverturePort()));
    connect(transmission, SIGNAL(portFerme()), this, SLOT(desactiverFermerPort()));
}

/**
 * @brief destructeur de la classe Ihm
 *
 * @fn Ihm::~Ihm
 */
Ihm::~Ihm()
{
    EnregistrerConfigurationPort();

    delete ui;
}

/**
 * @brief enregistrer la configuration du port dans un fichier .ini
 *
 * @fn Ihm::EnregistrerConfigurationPort
 */
void Ihm::EnregistrerConfigurationPort()
{
    QSettings EnregistrerConfigurationPort("Sonde.ini", QSettings::IniFormat);

    EnregistrerConfigurationPort.beginGroup("Port");
    EnregistrerConfigurationPort.setValue("Appareil", ui->comboBoxAppareil->currentText());
    EnregistrerConfigurationPort.setValue("DebitBauds", ui->comboBoxDebitBaud->currentText());
    EnregistrerConfigurationPort.setValue("BitsDonnee", ui->comboBoxBitsDonnees->currentText());
    EnregistrerConfigurationPort.setValue("BitsStop", ui->comboBoxBitsStop->currentText());
    EnregistrerConfigurationPort.endGroup();
}

/**
 * @brief charger la configuration du port depuis un fichier .ini
 *
 * @fn Ihm::ChargerConfigurationPort
 */
void Ihm::ChargerConfigurationPort()
{
    QSettings initialiserPort("Sonde.ini", QSettings::IniFormat);

    ui->comboBoxAppareil->setCurrentText(initialiserPort.value("Port/Appareil","/dev/ttyUSB0").toString());
    ui->comboBoxDebitBaud->setCurrentText(initialiserPort.value("Port/DebitBauds","1200").toString());
    ui->comboBoxBitsDonnees->setCurrentText(initialiserPort.value("Port/BitsDonnee","5").toString());
    ui->comboBoxBitsStop->setCurrentText(initialiserPort.value("Port/BitsStop","1").toString());
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

    ui->comboBoxAppareil->addItems(QStringList{"/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2", "/dev/ttyS3" });
    ui->comboBoxDebitBaud->addItems(QStringList{"1200", "1800", "2400", "4800", "9600", "19200", "38400", "57600", "115200", "230400", "460800"});
    ui->comboBoxBitsDonnees->addItems(QStringList{"5", "6", "7", "8"});
    ui->comboBoxBitsStop->addItems(QStringList{"1", "2"});

    ChargerConfigurationPort();
}

/**
 * @brief Méthode appelée lorsque le Bouton quitté est enclenché
 *
 * @fn Ihm::on_pushButton_Quitter_clicked
 */
void Ihm::on_pushButtonQuitter_clicked()
{
    this->close();
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

    ui->horodatage->setText(heure);
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
    switch (transmission->getEsp32()->getEtatLed())
          {
             case 0:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_OFF));
                ui->radioButtonLedOff->setChecked(true);
                break;
             case 1:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_ROUGE));
                ui->radioButtonLedRouge->setChecked(true);
                break;
             case 2:
                ui->ImageEtatLed->setPixmap(QPixmap(LED_VERT));
                ui->radioButtonLedVert->setChecked(true);
               break;
             case 3:
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
    ui->lcdNumberTemperature->display(transmission->getEsp32()->getTemperature());
    ui->lcdNumberHumidite->display(transmission->getEsp32()->getHumidite());
    ui->lcdNumberRessentie->display(transmission->getEsp32()->getRessentie());
    ui->lcdNumberLuminosite->display(transmission->getEsp32()->getLuminosite());
    ui->lcdNumberPression->display(transmission->getEsp32()->getPression());
    ui->lcdNumberAltitude->display(transmission->getEsp32()->getAltitude());

    ui->labelUniteTemperature->setText(transmission->getEsp32()->getTemperatureUnite());
    ui->labelUniteRessenti->setText(transmission->getEsp32()->getRessentieUnite());
    ui->labelUniteHumidite->setText(transmission->getEsp32()->getHumiditeUnite());
    ui->labelUniteLuminosite->setText(transmission->getEsp32()->getLuminositeUnite());
    ui->labelUnitePression->setText(transmission->getEsp32()->getPressionUnite());
    ui->labelUniteAltitude->setText(transmission->getEsp32()->getAltitudeUnite());

    modifierEtatLed();
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
 * @brief desactive des bouton de l'Ihm
 *
 * @fn Ihm::desactiverOuvrirPort
 */
void Ihm::desactiverOuverturePort()
{
    ui->pushButtonOuvrirPort->setDisabled(true);
    ui->pushButtonFermerPort->setDisabled(false);

    ui->radioButtonLedOff->setDisabled(false);
    ui->radioButtonLedVert->setDisabled(false);
    ui->radioButtonLedRouge->setDisabled(false);
    ui->radioButtonLedOrange->setDisabled(false);
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
    initialiserAffichage();

    ui->radioButtonLedOff->setDisabled(true);
    ui->radioButtonLedVert->setDisabled(true);
    ui->radioButtonLedRouge->setDisabled(true);
    ui->radioButtonLedOrange->setDisabled(true);
}

/**
 * @brief   remet les lcdNumber a zero quand le port est fermer
 *initialiserAffichage
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
