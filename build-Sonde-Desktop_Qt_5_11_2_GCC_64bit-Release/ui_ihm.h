/********************************************************************************
** Form generated from reading UI file 'ihm.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHM_H
#define UI_IHM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ihm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayoutPrincipalFenetre;
    QTabWidget *tabWidget;
    QWidget *Donnees;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QLCDNumber *lcdNumberRessentie;
    QLabel *labelRessentie;
    QLabel *labelUniteRessenti;
    QLCDNumber *lcdNumberLuminosite;
    QLabel *labelPression;
    QLCDNumber *lcdNumberTemperature;
    QLabel *labelLuminositer;
    QLabel *labelTemperature;
    QLabel *labelHumiditer;
    QLCDNumber *lcdNumberHumidite;
    QLabel *labelUniteTemperature;
    QLCDNumber *lcdNumberPression;
    QLabel *labelUnitePression;
    QLabel *labelUniteHumidite;
    QLCDNumber *lcdNumberAltitude;
    QLabel *labelUniteLuminosite;
    QLabel *labelAltitude;
    QLabel *labelUniteAltitude;
    QLabel *horodatage;
    QLabel *labelHorodatage;
    QLabel *ImageEtatLed;
    QWidget *commande;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelEtatLed;
    QRadioButton *radioButtonLedRouge;
    QRadioButton *radioButtonLedVert;
    QRadioButton *radioButtonLedOrange;
    QRadioButton *radioButtonLedOff;
    QWidget *Configuration;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelAppareil;
    QLabel *labelDebitBauds;
    QLabel *labelBitsDonnees;
    QLabel *labelBitsStop;
    QPushButton *pushButtonFermerPort;
    QComboBox *comboBoxDebitBaud;
    QComboBox *comboBoxBitsDonnees;
    QComboBox *comboBoxBitsStop;
    QComboBox *comboBoxAppareil;
    QPushButton *pushButtonOuvrirPort;
    QWidget *Operateur;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEditTrame;
    QLabel *labelEnvoieTrame;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEditEnvoyerTrame;
    QPushButton *pushButtonEnvoyerTrame;
    QHBoxLayout *horizontalLayoutFooter;
    QCheckBox *ModeOperateur;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonQuitter;

    void setupUi(QWidget *Ihm)
    {
        if (Ihm->objectName().isEmpty())
            Ihm->setObjectName(QStringLiteral("Ihm"));
        Ihm->resize(500, 353);
        Ihm->setMinimumSize(QSize(500, 353));
        verticalLayout_2 = new QVBoxLayout(Ihm);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayoutPrincipalFenetre = new QVBoxLayout();
        verticalLayoutPrincipalFenetre->setSpacing(6);
        verticalLayoutPrincipalFenetre->setObjectName(QStringLiteral("verticalLayoutPrincipalFenetre"));
        tabWidget = new QTabWidget(Ihm);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Donnees = new QWidget();
        Donnees->setObjectName(QStringLiteral("Donnees"));
        horizontalLayout_2 = new QHBoxLayout(Donnees);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        lcdNumberRessentie = new QLCDNumber(Donnees);
        lcdNumberRessentie->setObjectName(QStringLiteral("lcdNumberRessentie"));

        gridLayout->addWidget(lcdNumberRessentie, 2, 1, 1, 1);

        labelRessentie = new QLabel(Donnees);
        labelRessentie->setObjectName(QStringLiteral("labelRessentie"));

        gridLayout->addWidget(labelRessentie, 2, 0, 1, 1);

        labelUniteRessenti = new QLabel(Donnees);
        labelUniteRessenti->setObjectName(QStringLiteral("labelUniteRessenti"));

        gridLayout->addWidget(labelUniteRessenti, 2, 2, 1, 1);

        lcdNumberLuminosite = new QLCDNumber(Donnees);
        lcdNumberLuminosite->setObjectName(QStringLiteral("lcdNumberLuminosite"));

        gridLayout->addWidget(lcdNumberLuminosite, 4, 1, 1, 1);

        labelPression = new QLabel(Donnees);
        labelPression->setObjectName(QStringLiteral("labelPression"));

        gridLayout->addWidget(labelPression, 5, 0, 1, 1);

        lcdNumberTemperature = new QLCDNumber(Donnees);
        lcdNumberTemperature->setObjectName(QStringLiteral("lcdNumberTemperature"));

        gridLayout->addWidget(lcdNumberTemperature, 1, 1, 1, 1);

        labelLuminositer = new QLabel(Donnees);
        labelLuminositer->setObjectName(QStringLiteral("labelLuminositer"));

        gridLayout->addWidget(labelLuminositer, 4, 0, 1, 1);

        labelTemperature = new QLabel(Donnees);
        labelTemperature->setObjectName(QStringLiteral("labelTemperature"));

        gridLayout->addWidget(labelTemperature, 1, 0, 1, 1);

        labelHumiditer = new QLabel(Donnees);
        labelHumiditer->setObjectName(QStringLiteral("labelHumiditer"));

        gridLayout->addWidget(labelHumiditer, 3, 0, 1, 1);

        lcdNumberHumidite = new QLCDNumber(Donnees);
        lcdNumberHumidite->setObjectName(QStringLiteral("lcdNumberHumidite"));

        gridLayout->addWidget(lcdNumberHumidite, 3, 1, 1, 1);

        labelUniteTemperature = new QLabel(Donnees);
        labelUniteTemperature->setObjectName(QStringLiteral("labelUniteTemperature"));

        gridLayout->addWidget(labelUniteTemperature, 1, 2, 1, 1);

        lcdNumberPression = new QLCDNumber(Donnees);
        lcdNumberPression->setObjectName(QStringLiteral("lcdNumberPression"));

        gridLayout->addWidget(lcdNumberPression, 5, 1, 1, 1);

        labelUnitePression = new QLabel(Donnees);
        labelUnitePression->setObjectName(QStringLiteral("labelUnitePression"));

        gridLayout->addWidget(labelUnitePression, 5, 2, 1, 1);

        labelUniteHumidite = new QLabel(Donnees);
        labelUniteHumidite->setObjectName(QStringLiteral("labelUniteHumidite"));

        gridLayout->addWidget(labelUniteHumidite, 3, 2, 1, 1);

        lcdNumberAltitude = new QLCDNumber(Donnees);
        lcdNumberAltitude->setObjectName(QStringLiteral("lcdNumberAltitude"));

        gridLayout->addWidget(lcdNumberAltitude, 6, 1, 1, 1);

        labelUniteLuminosite = new QLabel(Donnees);
        labelUniteLuminosite->setObjectName(QStringLiteral("labelUniteLuminosite"));

        gridLayout->addWidget(labelUniteLuminosite, 4, 2, 1, 1);

        labelAltitude = new QLabel(Donnees);
        labelAltitude->setObjectName(QStringLiteral("labelAltitude"));

        gridLayout->addWidget(labelAltitude, 6, 0, 1, 1);

        labelUniteAltitude = new QLabel(Donnees);
        labelUniteAltitude->setObjectName(QStringLiteral("labelUniteAltitude"));

        gridLayout->addWidget(labelUniteAltitude, 6, 2, 1, 1);

        horodatage = new QLabel(Donnees);
        horodatage->setObjectName(QStringLiteral("horodatage"));

        gridLayout->addWidget(horodatage, 0, 1, 1, 2);

        labelHorodatage = new QLabel(Donnees);
        labelHorodatage->setObjectName(QStringLiteral("labelHorodatage"));

        gridLayout->addWidget(labelHorodatage, 0, 0, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        ImageEtatLed = new QLabel(Donnees);
        ImageEtatLed->setObjectName(QStringLiteral("ImageEtatLed"));

        horizontalLayout_2->addWidget(ImageEtatLed);

        tabWidget->addTab(Donnees, QString());
        commande = new QWidget();
        commande->setObjectName(QStringLiteral("commande"));
        horizontalLayout_3 = new QHBoxLayout(commande);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelEtatLed = new QLabel(commande);
        labelEtatLed->setObjectName(QStringLiteral("labelEtatLed"));
        labelEtatLed->setScaledContents(false);

        verticalLayout_4->addWidget(labelEtatLed);

        radioButtonLedRouge = new QRadioButton(commande);
        radioButtonLedRouge->setObjectName(QStringLiteral("radioButtonLedRouge"));
        radioButtonLedRouge->setEnabled(true);

        verticalLayout_4->addWidget(radioButtonLedRouge);

        radioButtonLedVert = new QRadioButton(commande);
        radioButtonLedVert->setObjectName(QStringLiteral("radioButtonLedVert"));

        verticalLayout_4->addWidget(radioButtonLedVert);

        radioButtonLedOrange = new QRadioButton(commande);
        radioButtonLedOrange->setObjectName(QStringLiteral("radioButtonLedOrange"));

        verticalLayout_4->addWidget(radioButtonLedOrange);

        radioButtonLedOff = new QRadioButton(commande);
        radioButtonLedOff->setObjectName(QStringLiteral("radioButtonLedOff"));

        verticalLayout_4->addWidget(radioButtonLedOff);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_2);

        tabWidget->addTab(commande, QString());
        Configuration = new QWidget();
        Configuration->setObjectName(QStringLiteral("Configuration"));
        verticalLayout = new QVBoxLayout(Configuration);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelAppareil = new QLabel(Configuration);
        labelAppareil->setObjectName(QStringLiteral("labelAppareil"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelAppareil);

        labelDebitBauds = new QLabel(Configuration);
        labelDebitBauds->setObjectName(QStringLiteral("labelDebitBauds"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelDebitBauds);

        labelBitsDonnees = new QLabel(Configuration);
        labelBitsDonnees->setObjectName(QStringLiteral("labelBitsDonnees"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelBitsDonnees);

        labelBitsStop = new QLabel(Configuration);
        labelBitsStop->setObjectName(QStringLiteral("labelBitsStop"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelBitsStop);

        pushButtonFermerPort = new QPushButton(Configuration);
        pushButtonFermerPort->setObjectName(QStringLiteral("pushButtonFermerPort"));

        formLayout->setWidget(5, QFormLayout::LabelRole, pushButtonFermerPort);

        comboBoxDebitBaud = new QComboBox(Configuration);
        comboBoxDebitBaud->setObjectName(QStringLiteral("comboBoxDebitBaud"));
        comboBoxDebitBaud->setEditable(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBoxDebitBaud);

        comboBoxBitsDonnees = new QComboBox(Configuration);
        comboBoxBitsDonnees->setObjectName(QStringLiteral("comboBoxBitsDonnees"));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBoxBitsDonnees);

        comboBoxBitsStop = new QComboBox(Configuration);
        comboBoxBitsStop->setObjectName(QStringLiteral("comboBoxBitsStop"));

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBoxBitsStop);

        comboBoxAppareil = new QComboBox(Configuration);
        comboBoxAppareil->setObjectName(QStringLiteral("comboBoxAppareil"));
        comboBoxAppareil->setEditable(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxAppareil);

        pushButtonOuvrirPort = new QPushButton(Configuration);
        pushButtonOuvrirPort->setObjectName(QStringLiteral("pushButtonOuvrirPort"));

        formLayout->setWidget(4, QFormLayout::LabelRole, pushButtonOuvrirPort);


        verticalLayout->addLayout(formLayout);

        tabWidget->addTab(Configuration, QString());
        Operateur = new QWidget();
        Operateur->setObjectName(QStringLiteral("Operateur"));
        horizontalLayout = new QHBoxLayout(Operateur);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        textEditTrame = new QTextEdit(Operateur);
        textEditTrame->setObjectName(QStringLiteral("textEditTrame"));

        verticalLayout_3->addWidget(textEditTrame);

        labelEnvoieTrame = new QLabel(Operateur);
        labelEnvoieTrame->setObjectName(QStringLiteral("labelEnvoieTrame"));

        verticalLayout_3->addWidget(labelEnvoieTrame);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        lineEditEnvoyerTrame = new QLineEdit(Operateur);
        lineEditEnvoyerTrame->setObjectName(QStringLiteral("lineEditEnvoyerTrame"));

        horizontalLayout_6->addWidget(lineEditEnvoyerTrame);

        pushButtonEnvoyerTrame = new QPushButton(Operateur);
        pushButtonEnvoyerTrame->setObjectName(QStringLiteral("pushButtonEnvoyerTrame"));

        horizontalLayout_6->addWidget(pushButtonEnvoyerTrame);


        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout->addLayout(verticalLayout_3);

        tabWidget->addTab(Operateur, QString());

        verticalLayoutPrincipalFenetre->addWidget(tabWidget);


        verticalLayout_2->addLayout(verticalLayoutPrincipalFenetre);

        horizontalLayoutFooter = new QHBoxLayout();
        horizontalLayoutFooter->setSpacing(6);
        horizontalLayoutFooter->setObjectName(QStringLiteral("horizontalLayoutFooter"));
        ModeOperateur = new QCheckBox(Ihm);
        ModeOperateur->setObjectName(QStringLiteral("ModeOperateur"));

        horizontalLayoutFooter->addWidget(ModeOperateur);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutFooter->addItem(horizontalSpacer);

        pushButtonQuitter = new QPushButton(Ihm);
        pushButtonQuitter->setObjectName(QStringLiteral("pushButtonQuitter"));

        horizontalLayoutFooter->addWidget(pushButtonQuitter);


        verticalLayout_2->addLayout(horizontalLayoutFooter);


        retranslateUi(Ihm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Ihm);
    } // setupUi

    void retranslateUi(QWidget *Ihm)
    {
        Ihm->setWindowTitle(QApplication::translate("Ihm", "Ihm", nullptr));
        labelRessentie->setText(QApplication::translate("Ihm", "Ressentie :", nullptr));
        labelUniteRessenti->setText(QApplication::translate("Ihm", "\302\260C", nullptr));
        labelPression->setText(QApplication::translate("Ihm", "Pression :", nullptr));
        labelLuminositer->setText(QApplication::translate("Ihm", "Luminosit\303\251 :", nullptr));
        labelTemperature->setText(QApplication::translate("Ihm", "Temp\303\251rature :", nullptr));
        labelHumiditer->setText(QApplication::translate("Ihm", "Humidit\303\251 :", nullptr));
        labelUniteTemperature->setText(QApplication::translate("Ihm", "\302\260C", nullptr));
        labelUnitePression->setText(QApplication::translate("Ihm", "hPa", nullptr));
        labelUniteHumidite->setText(QApplication::translate("Ihm", "%", nullptr));
        labelUniteLuminosite->setText(QApplication::translate("Ihm", "Lux", nullptr));
        labelAltitude->setText(QApplication::translate("Ihm", "Altitude :", nullptr));
        labelUniteAltitude->setText(QApplication::translate("Ihm", "M\303\250tre", nullptr));
        horodatage->setText(QString());
        labelHorodatage->setText(QApplication::translate("Ihm", "Horodatage :", nullptr));
        ImageEtatLed->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(Donnees), QApplication::translate("Ihm", "Donn\303\251es", nullptr));
        labelEtatLed->setText(QApplication::translate("Ihm", "Configurer la couleur de la LED :", nullptr));
        radioButtonLedRouge->setText(QApplication::translate("Ihm", "Rouge", nullptr));
        radioButtonLedVert->setText(QApplication::translate("Ihm", "Vert", nullptr));
        radioButtonLedOrange->setText(QApplication::translate("Ihm", "Orange", nullptr));
        radioButtonLedOff->setText(QApplication::translate("Ihm", "Eteint", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(commande), QApplication::translate("Ihm", "Commande", nullptr));
        labelAppareil->setText(QApplication::translate("Ihm", "Appareil :", nullptr));
        labelDebitBauds->setText(QApplication::translate("Ihm", "d\303\251bit en bauds", nullptr));
        labelBitsDonnees->setText(QApplication::translate("Ihm", "Bits de donn\303\251es :", nullptr));
        labelBitsStop->setText(QApplication::translate("Ihm", "Bits de stop :", nullptr));
        pushButtonFermerPort->setText(QApplication::translate("Ihm", "fermer port", nullptr));
        comboBoxAppareil->setCurrentText(QApplication::translate("Ihm", "/dev/ttyUSB0", nullptr));
        pushButtonOuvrirPort->setText(QApplication::translate("Ihm", "Ouvrir port", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Configuration), QApplication::translate("Ihm", "Configuration", nullptr));
        labelEnvoieTrame->setText(QApplication::translate("Ihm", "envoie trame:", nullptr));
        pushButtonEnvoyerTrame->setText(QApplication::translate("Ihm", "Envoyer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Operateur), QApplication::translate("Ihm", "Operateur", nullptr));
        ModeOperateur->setText(QApplication::translate("Ihm", "Mode Operateur", nullptr));
        pushButtonQuitter->setText(QApplication::translate("Ihm", "Quitter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ihm: public Ui_Ihm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHM_H
