#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include <QObject>
#include <QtWidgets>
#include <QtCharts>
#include <QApplication>

/**
 * @file graphique.h
 *
 * @brief Declaration de la classe Graphique
 *
 * @version 4.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @class Graphique graphique.h "graphique.h"
 *
 * @brief Declaration de la classe Graphique
*/
class Graphique : public QWidget
{
    Q_OBJECT
public:
    Graphique(QWidget *parent = nullptr);     /** constructeur de la classe graphique */
    ~Graphique();                       /** destructeur de la classe graphique */

    void creerGraphiqueTemperature();       /** fonction appelée pour creer le graphique temperature */
    void creerGraphiquePression();       /** fonction appelée pour creer le graphique pression */
    void creerGraphiqueHumidite();       /** fonction appelée pour creer le graphique humidite */
    void creerGraphiqueLuminosite();       /** fonction appelée pour creer le graphique luminosité */

    void ajouterDonneeTemperature(double temperature);         /** fonction appelée pour ajouter des valeurs au graphique temperature */
    void ajouterDonneeHumidite(int humidite);         /** fonction appelée pour ajouter des valeurs au graphique humidite */
    void ajouterDonneeLuminosite(int luminosite);         /** fonction appelée pour ajouter des valeurs au graphique luminosité */
    void ajouterDonneePression(int pression);         /** fonction appelée pour ajouter des valeurs au graphique pression */

private:
    QWidget *ihmGraphique;  //!<  le widget qui contient les graphiques
    QDateTime debut;        //!<  objet date utilisé pour l'axe temps des graphiques

    QHBoxLayout *layoutHTempHum;    //!<  layout qui contient le graphique temperature et humidité
    QHBoxLayout *layoutHLumPres;    //!<  layout qui contient le graphique luminosité et pression
    QVBoxLayout *layoutV;           //!<  layout qui contient les deux layout (layoutHTempHum / layoutHLumPres)

    QChartView *graphiqueTemperature; //!<  un widget pour afficher le graphe temperature
    QChart *grapheTemperature; //!<  la représentation du graphe temperature
    QLineSeries *courbeTemperature; //!<  les données temperatures
    QValueAxis *axeYTemperature; //!<  l'axe Y temperature
    QDateTimeAxis *axeXTemperature; //!<   l'axe X temperature

    QChartView *graphiqueLuminosite; //!<  un widget pour afficher le graphe  luminosité
    QChart *grapheLuminosite; //!<  la représentation du graphe luminosité
    QLineSeries *courbeLuminosite; //!<  les données de luminosité
    QValueAxis *axeYLuminosite; //!<  l'axe Y luminosité
    QDateTimeAxis *axeXLuminosite; //!<  l'axe X lumonisité

    QChartView *graphiquePression; //!<  un widget pour afficher le graphe pression
    QChart *graphePression; //!<  la représentation du graphe pression
    QLineSeries *courbePression; //!<  les données de pression
    QValueAxis *axeYPression;  //!<  l'axe Y pression
    QDateTimeAxis *axeXPression;  //!<  l'axe X pression

    QValueAxis *axeYHumidite;  //!<  l'axe Y humidite
    QDateTimeAxis *axeXHumidite;  //!<  l'axe X humidite
    QChart *grapheHumidite; //!<  la représentation du graphe humidité
    QChartView *graphiqueHumidite; //!<  un widget pour afficher un graphe humidité
    QLineSeries *courbeHumidite; //!<  les données d'humidité

    double axeYTemperatureMax;      //!<  variable qui contient la valeur max de l'axe temperature
    double axeYTemperatureMin;      //!<  variable qui contient la valeur min de l'axe temperature

    int axeYPressionMax;            //!<  variable qui contient la valeur max de l'axe pression
    int axeYLuminositeMax;          //!<  variable qui contient la valeur max de l'axe luminosite
};

#endif // GRAPHIQUE_H
