#ifndef IHM_H
#define IHM_H

#include <QWidget>
#include <QDateTime>
#include <QSettings>
#include "transmission.h"

class Transmission;


namespace Ui {
class Ihm;
}

/**
 * @file ihm.h
 * @brief Declaration de la classe Ihm
 *
 * @version 2.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @class Ihm ihm.h "ihm.h"
 */

class Ihm : public QWidget
{
    Q_OBJECT

public:
    explicit Ihm(QWidget *parent = nullptr);    /** constructeur de la classe Ihm*/
    ~Ihm();                                     /** destructeur de la classe Ihm*/
    void modifierEtatLed();                     /** modifie l'etat de la led en fonction de la trame recu */
      
private slots:
    void on_pushButtonQuitter_clicked();           /** action de fermer la widget */
    void on_ModeOperateur_stateChanged(int arg1);   /** permet de passer en mode Operateur */
    void actualiserTrame();                         /** met a jour l'affichage de la trame en mode operateur lors du signal trameRecue() */
    void actualiserDonnee();                        /** met a jour les donner des LcdNumber dans l'onglet Données en fonction de la trame recu */
    void desactiverOuverturePort();                    /** Méthode appelée quand un port serie et ouvert */
    void desactiverFermerPort();                     /** Méthode appelée quand un port serie et fermer */

    void on_pushButtonOuvrirPort_clicked();         /** Méthode n'appelée dès que le bouton Ouvrir port et enclencher */
    void on_pushButtonFermerPort_clicked();         /** Méthode n'appelée dès que le bouton Fermer port et enclencher */
    void on_pushButtonEnvoyerTrame_clicked();       /** Méthode n'appelée dès que le bouton envoyer et enclencher */
    void on_radioButtonLedRouge_clicked();          /** Méthode n'appelée dès que le radio bouton LedRoude et enclencher */
    void on_radioButtonLedVert_clicked();           /** Méthode n'appelée dès que le radio bouton LedVert et enclencher */
    void on_radioButtonLedOrange_clicked();         /** Méthode n'appelée dès que le radio bouton LedOrange et enclencher */
    void on_radioButtonLedOff_clicked();            /** Méthode n'appelée dès que le radio bouton LedOff et enclencher */

private:
    Ui::Ihm *ui;                                    /** objet Ihm */
    Transmission* transmission;                     /** objet transmission*/

    void initialiserAffichage();              /** reinitialise les different lcdNumber a zero */
    void initialiserInterface();                /** cette fonction désactive certains Boutons ne pouvant être utilisé */
    void EnregistrerConfigurationPort();        /** cette methode et appeler pour enregistrer la configuration du port dans un fichier .ini */
    void ChargerConfigurationPort();            /** cette methode et appeler pour charger la configuration du port depuis un fichier .ini */
};

#endif // IHM_H
