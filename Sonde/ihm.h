#ifndef IHM_H
#define IHM_H

#include <QWidget>
#include <QDateTime>
#include <QSettings>
#include "transmission.h"
#include "meteo.h"

#define MODE_OPERATEUR_ACTIVER 2
#define ONGLET_MODE_OPERATEUR 4
#define LED_ROUGE "../Sonde/image/ledRouge.png"
#define LED_VERT "../Sonde/image/ledVert.png"
#define LED_ORANGE "../Sonde/image/ledOrange.png"
#define LED_OFF "../Sonde/image/ledEteint.png"

#define VALEUR_LED_OFF 0
#define VALEUR_LED_ROUGE 1
#define VALEUR_LED_VERT 2
#define VALEUR_LED_ORANGE 3


class Transmission;
class Meteo;


namespace Ui {
class Ihm;
}

/**
 * @file ihm.h
 * @brief Declaration de la classe Ihm
 *
 * @version 3.0
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
    void modifierEtatLed();                     /** modifie l'etat de la led en fonction de la trame recu */
      
private slots:
    void on_pushButtonQuitter_clicked();            /** action de fermer la widget */
    void on_ModeOperateur_stateChanged(int arg1);   /** permet de passer en mode Operateur */
    void actualiserTrame();                         /** met a jour l'affichage de la trame en mode operateur lors du signal trameRecue() */
    void actualiserDonnee();                        /** met a jour les donner des LcdNumber dans l'onglet Données en fonction de la trame recu */
    void desactiverOuverturePort();                 /** Méthode appelée quand un port serie et ouvert */
    void desactiverFermerPort();                    /** Méthode appelée quand un port serie et fermer */
    void actualiserAffichageMeteo();

    void on_pushButtonOuvrirPort_clicked();         /** Méthode appelée dès que le bouton Ouvrir port et enclencher */
    void on_pushButtonFermerPort_clicked();         /** Méthode appelée dès que le bouton Fermer port et enclencher */
    void on_pushButtonEnvoyerTrame_clicked();       /** Méthode appelée dès que le bouton envoyer et enclencher */
    void on_radioButtonLedRouge_clicked();          /** Méthode appelée dès que le radio bouton LedRoude et enclencher */
    void on_radioButtonLedVert_clicked();           /** Méthode appelée dès que le radio bouton LedVert et enclencher */
    void on_radioButtonLedOrange_clicked();         /** Méthode appelée dès que le radio bouton LedOrange et enclencher */
    void on_radioButtonLedOff_clicked();            /** Méthode appelée dès que le radio bouton LedOff et enclencher */
    void on_pushButtonVille_clicked();              /** Méthode appelée dès que le radio bouton Ville et enclencher */

private:
    Ui::Ihm *ui;                                    //!< objet Ihm
    Transmission* transmission;                     //!< objet transmission
    Meteo* meteo;                                   //!< objet meteo

    void initialiserAffichage();                /** reinitialise les different lcdNumber a zero */
    void initialiserInterface();                /** cette fonction désactive certains Boutons ne pouvant être utilisé */
    void enregistrerConfigurationPort();        /** cette methode et appeler pour enregistrer la configuration du port dans un fichier .ini */
    void chargerConfigurationPort();            /** cette methode et appeler pour charger la configuration du port depuis un fichier .ini */
};

#endif // IHM_H
