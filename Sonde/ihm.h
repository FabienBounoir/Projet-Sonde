#ifndef IHM_H
#define IHM_H

#include "transmission.h"
#include "meteo.h"
#include "graphique.h"

#include <QWidget>
#include <QDateTime>
#include <QSettings>
#include <QApplication>

#define MODE_OPERATEUR_ACTIVER 2
#define ONGLET_MODE_OPERATEUR 4
#define LED_ROUGE "../Sonde/image/ledRouge.png"
#define LED_VERT "../Sonde/image/ledVert.png"
#define LED_ORANGE "../Sonde/image/ledOrange.png"
#define LED_OFF "../Sonde/image/ledEteint.png"

#define VALEUR_LED_OFF      0
#define VALEUR_LED_ROUGE    1
#define VALEUR_LED_VERT     2
#define VALEUR_LED_ORANGE   3


class Transmission;
class Meteo;
class Graphique;


namespace Ui {
class Ihm;
}

/**
 * @file ihm.h
 * @brief Declaration de la classe Ihm
 *
 * @version 4.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @class Ihm ihm.h "ihm.h"
 * @brief Declaration de la classe Ihm
*/
class Ihm : public QWidget
{
    Q_OBJECT

public:
    explicit Ihm(QWidget *parent = nullptr);    /** constructeur de la classe Ihm*/
    ~Ihm();                                     /** destructeur de la classe Ihm*/
    void modifierEtatLed();                     /** modifie l'etat de la led en fonction de la trame recue */

private slots:
    void on_pushButtonQuitter_clicked();            /** action de fermer la widget */
    void on_ModeOperateur_stateChanged(int arg1);   /** permet de passer en mode Operateur */
    void actualiserTrame();                         /** met a jour l'affichage de la trame en mode Operateur lors du signal trameRecue() */
    void actualiserDonnee();                        /** met a jour les données dans l'onglet Données en fonction de la trame recue */
    void desactiverOuverturePort();                 /** Méthode appelée quand un port serie de la Sonde est ouvert */
    void desactiverOuverturePortGps();              /** Méthode appelée quand le port serie du GPS est ouvert */
    void desactiverFermerPort();                    /** Méthode appelée quand un port serie est fermé */
    void desactiverFermerPortGps();                 /** Méthode appelée quand le port serie du GPS est fermé */
    void actualiserAffichageMeteo();                /** methode qui actualise les données de meteo reçues */
    void mettreAjourAppareilBluetoothDisponible();  /** methode qui actualise les appareil disponible */
    void actualiserAffichageBluetooth();            /** methode qui met à jour l'affichage des boutons (enable / disable)*/
    void actualiserMessageStatutConnecterBluetooth();        /** methode qui met à jour le message de statut de la connexion bluetooth (appareil connecté)*/
    void actualiserMessageStatutDeconnecterBluetooth();      /** methode qui met à jour le message de statut de la connexion bluetooth (appareil deconnecté)*/
    void actualiserMessageStatutErreurBluetooth();           /** methode qui met à jour le message de statut de la connexion bluetooth (erreur de connexion)*/

    void on_pushButtonOuvrirPort_clicked();         /** Méthode appelée dès que le bouton Ouvrir port est enclenché */
    void on_pushButtonFermerPort_clicked();         /** Méthode appelée dès que le bouton Fermer port est enclenché */
    void on_pushButtonEnvoyerTrame_clicked();       /** Méthode appelée dès que le bouton envoyer est enclenché */
    void on_radioButtonLedRouge_clicked();          /** Méthode appelée dès que le radio bouton LedRoude est enclenché */
    void on_radioButtonLedVert_clicked();           /** Méthode appelée dès que le radio bouton LedVert est enclenché */
    void on_radioButtonLedOrange_clicked();         /** Méthode appelée dès que le radio bouton LedOrange est enclenché */
    void on_radioButtonLedOff_clicked();            /** Méthode appelée dès que le radio bouton LedOff est enclenché */
    void on_pushButtonVille_clicked();              /** Méthode appelée dès que le radio bouton Ville est enclenché */
    void on_pushButtonScan_clicked();               /** Méthode appelée dès que le push bouton Scan est enclenché */
    void on_pushButtonConnexion_clicked();          /** Méthode appelée dès que le push bouton Connexion est enclenché */
    void on_pushButtonDeconnexion_clicked();        /** Méthode appelée dès que le push bouton deconnexion est enclenché */
    void on_pushButtonGraphique_clicked();          //!< Méthode appelée dès que le push bouton graphique est enclenché
    void on_checkBoxPleinEcran_stateChanged(int arg1);  //!< Méthode appelée dès que l'etat du checkBox plein ecran change
    void actualiserDonneeGps();                         //!< Méthode qui met a jour la latitude et longitude dans l'Ihm
    void on_pushButtonEnvoyerCoordonnee_clicked();   //!< bouton qui actualise l'etat des données meteo grace à la latitude et longitude
    void on_pushButtonOuvrirPortGps_clicked();       //!< bouton qui permet d'ouvrir la communication pour le port serie du GPS
    void on_pushButtonFermerPortGps_clicked();       //!< bouton qui permet de fermer la communication pour le port serie du GPS
    void actualiserMessageStatutConnectionGps(QString message); //!< met à jour le statut de connexion du GPS
    void actualiserMessageStatutConnectionSonde(QString message); //!< met à jour le statut de connexion de la Sonde

private:
    Ui::Ihm *ui;                                    //!< objet Ihm
    Transmission* transmission;                     //!< objet transmission
    Meteo* meteo;                                   //!< objet meteo
    Graphique* graphique;                           //!< objet graphique;
    QProcess *proc;                                 //!< pointer proc

    void initialiserAffichage();                /** reinitialise l'affichage des données */
    void initialiserInterface();                /** désactive certains Boutons ne pouvant être utilisés */
    void enregistrerConfigurationPort();        /** enregistre la configuration du port dans un fichier .ini */
    void chargerConfigurationPort();            /** charge la configuration du port depuis un fichier .ini */
    void desactiverConnexionPortSerie();        /** desactive la possibilité de connexion par port serie car une connexion bluetooth est en cours */
    void activerConnexionPortSerie();           /** active la possibilité de connexion par port serie car aucun connexion en cours */
    void desactiverConnexionBluetooth();        /** desactive la possibilité de connexion par bluetooth car une connexion par port serie est en cours */
    void activerConnexionBluetooth();           /** active la possibilité de connexion par bluetooth car aucun connexion en cours */
    void ActiverControleLed();                  /** active le controle de la led quand une connexion est en cours */
    void DesactiverControleLed();               /** desactive le controle de la led car aucun connexion en cours */
    void initialiserConnect();                  /** initialise les connexions signal/slot */
};

#endif // IHM_H
