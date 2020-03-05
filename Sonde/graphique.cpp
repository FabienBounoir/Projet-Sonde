#include "graphique.h"
/**
* @file graphique.cpp
*
* @brief classe qui gére les differents graphiques
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 4.1
*
*/


/**
 * @brief le constructeur de la classe Graphique
 *
 * @fn Graphique::Graphique
 */
Graphique::Graphique(QWidget *parent) : QWidget(parent), axeYTemperatureMax(30), axeYTemperatureMin(15), axeYPressionMax(2000), axeYLuminositeMax(1000)
{
    setWindowTitle("Graphiques");
    setFixedSize(900,700);
    isFullScreen();
    debut = QDateTime::currentDateTime();

    layoutV = new QVBoxLayout();
    layoutHTempHum = new QHBoxLayout();
    layoutHLumPres = new QHBoxLayout();

    creerGraphiqueTemperature();
    creerGraphiqueHumidite();
    creerGraphiqueLuminosite();
    creerGraphiquePression();

    layoutV->addItem(layoutHTempHum);
    layoutV->addItem(layoutHLumPres);

    this->setLayout(layoutV);

    ihmGraphique = new QWidget(this);
}

/**
 * @brief le destructeur de la classe Graphique
 *
 * @fn Graphique::~Graphique
 */
Graphique::~Graphique()
{
    delete ihmGraphique;
}

/**
 * @brief methode qui cree le graphique pour la temperature
 *
 * @fn Graphique::creerGraphiqueTemperature
 */
void Graphique::creerGraphiqueTemperature()
{

    // Les données
    courbeTemperature = new QLineSeries(this);
    courbeTemperature->setName(QString::fromUtf8("température en degré"));
    courbeTemperature->setColor(Qt::red);

    // Le grapheTemperature
    grapheTemperature = new QChart();
    grapheTemperature->setTitle("Température");
    grapheTemperature->setTheme(QChart::ChartThemeDark);
    grapheTemperature->addSeries(courbeTemperature);

    //QDateTimeAxis
    axeXTemperature = new QDateTimeAxis(this);
    axeXTemperature->setTickCount(5);
    axeXTemperature->setFormat("hh:mm");
    axeXTemperature->setMin(debut);
    axeXTemperature->setTitleText("Temps (Heures/minutes)");

    grapheTemperature->addAxis(axeXTemperature, Qt::AlignBottom);
    courbeTemperature->attachAxis(axeXTemperature);

    axeYTemperature = new QValueAxis(this);
    axeYTemperature->setRange(axeYTemperatureMin, axeYTemperatureMax);
    axeYTemperature->setLabelFormat("%.1f");
    axeYTemperature->setTitleText(QString::fromUtf8("Température (°C)"));
    grapheTemperature->addAxis(axeYTemperature, Qt::AlignLeft);
    courbeTemperature->setPointsVisible(true);

    //afficher les points sur la courbe
    //courbeTemperature->setPointLabelsFormat("@yPoint °C");
    //courbeTemperature->setPointLabelsVisible(true);

    courbeTemperature->attachAxis(axeYTemperature);

    // Le widget
    graphiqueTemperature = new QChartView(grapheTemperature);
    graphiqueTemperature->setRenderHint(QPainter::Antialiasing);

    resize(300, 200);

    layoutHTempHum->addWidget(graphiqueTemperature);
}

/**
 * @brief methode qui cree le graphique pour l'humidité
 *
 * @fn Graphique::creerGraphiqueHumidite
 */
void Graphique::creerGraphiqueHumidite()
{

    // Les données
    courbeHumidite = new QLineSeries(this);
    courbeHumidite->setName(QString::fromUtf8("humidité en pourcentage"));
    courbeHumidite->setColor(Qt::blue);

    // Le grapheHumidite
    grapheHumidite = new QChart();
    grapheHumidite->setTitle("Humidité");
    grapheHumidite->setTheme(QChart::ChartThemeDark);
    grapheHumidite->addSeries(courbeHumidite);

    //QDateTimeAxis
    axeXHumidite = new QDateTimeAxis(this);
    axeXHumidite->setTickCount(5);
    axeXHumidite->setFormat("hh:mm");
    axeXHumidite->setMin(debut);
    axeXHumidite->setTitleText("Temps (Heures/minutes)");

    grapheHumidite->addAxis(axeXHumidite, Qt::AlignBottom);
    courbeHumidite->attachAxis(axeXHumidite);

    axeYHumidite = new QValueAxis(this);
    axeYHumidite->setRange(0, 100);
    axeYHumidite->setLabelFormat("%.1f");
    axeYHumidite->setTitleText(QString::fromUtf8("Pourcentage (%)"));
    grapheHumidite->addAxis(axeYHumidite, Qt::AlignLeft);
    courbeHumidite->setPointsVisible(true);

    //afficher les points sur la courbe
    //courbeHumidite->setPointLabelsFormat("@yPoint %");
    //courbeHumidite->setPointLabelsVisible(true);

    courbeHumidite->attachAxis(axeYHumidite);

    // Le widget
    graphiqueHumidite = new QChartView(grapheHumidite);
    graphiqueHumidite->setRenderHint(QPainter::Antialiasing);

    resize(300, 200);

    layoutHTempHum->addWidget(graphiqueHumidite);
}

/**
 * @brief methode qui cree le graphique pour la luminosité
 *
 * @fn Graphique::creerGraphiqueLuminosite
 */
void Graphique::creerGraphiqueLuminosite()
{

    // Les données
    courbeLuminosite = new QLineSeries(this);
    courbeLuminosite->setName(QString::fromUtf8("Luminosité en lux"));
    courbeLuminosite->setColor(Qt::magenta);


    // Le grapheLuminosite
    grapheLuminosite = new QChart();
    grapheLuminosite->setTitle("Luminosité");
    grapheLuminosite->setTheme(QChart::ChartThemeDark);
    grapheLuminosite->addSeries(courbeLuminosite);

    //QDateTimeAxis
    axeXLuminosite = new QDateTimeAxis(this);
    axeXLuminosite->setTickCount(5);
    axeXLuminosite->setFormat("hh:mm");
    axeXLuminosite->setMin(debut);
    axeXLuminosite->setTitleText("Temps (Heures/minutes)");

    grapheLuminosite->addAxis(axeXLuminosite, Qt::AlignBottom);
    courbeLuminosite->attachAxis(axeXLuminosite);

    axeYLuminosite = new QValueAxis(this);
    axeYLuminosite->setRange(0, axeYLuminositeMax);
    axeYLuminosite->setLabelFormat("%.1f");
    axeYLuminosite->setTitleText(QString::fromUtf8("Luminosite (lux)"));
    grapheLuminosite->addAxis(axeYLuminosite, Qt::AlignLeft);
    courbeLuminosite->setPointsVisible(true);

    //afficher les points sur la courbe
    //courbeLuminosite->setPointLabelsFormat("@yPoint Lux");
    //courbeLuminosite->setPointLabelsVisible(true);

    courbeLuminosite->attachAxis(axeYLuminosite);

    // Le widget
    graphiqueLuminosite = new QChartView(grapheLuminosite);
    graphiqueLuminosite->setRenderHint(QPainter::Antialiasing);

    resize(300, 200);

    layoutHLumPres->addWidget(graphiqueLuminosite);
}

/**
 * @brief methode qui cree le graphique pour la pression atmosphérique
 *
 * @fn Graphique::creerGraphiquePression
 */
void Graphique::creerGraphiquePression()
{

    // Les données
    courbePression = new QLineSeries(this);
    courbePression->setName(QString::fromUtf8("Pression atmosphérique en hPa"));
    courbePression->setColor(Qt::green);

    // Le graphePression
    graphePression = new QChart();
    graphePression->setTitle("Pression atmosphérique");
    graphePression->setTheme(QChart::ChartThemeDark);
    graphePression->addSeries(courbePression);

    //QDateTimeAxis
    axeXPression = new QDateTimeAxis(this);
    axeXPression->setTickCount(5);
    axeXPression->setFormat("hh:mm");
    axeXPression->setMin(debut);
    axeXPression->setTitleText("Temps (Heures/minutes)");

    graphePression->addAxis(axeXPression, Qt::AlignBottom);
    courbePression->attachAxis(axeXPression);

    axeYPression = new QValueAxis(this);
    axeYPression->setRange(0, axeYPressionMax);
    axeYPression->setLabelFormat("%.1f");
    axeYPression->setTitleText(QString::fromUtf8("Pression (hPa)"));
    graphePression->addAxis(axeYPression, Qt::AlignLeft);
    courbePression->setPointsVisible(true);

    //afficher les points sur la courbe
    //courbePression->setPointLabelsFormat("@yPoint hPa");
    //courbePression->setPointLabelsVisible(true);

    courbePression->attachAxis(axeYPression);

    // Le widget
    graphiquePression = new QChartView(graphePression);
    graphiquePression->setRenderHint(QPainter::Antialiasing);

    resize(300, 200);

    layoutHLumPres->addWidget(graphiquePression);
}

/**
 * @brief Méthode appelée pour ajouter des valeurs au graphique températures
 *
 * @fn Graphique::ajouterDonneeTemperature
 * @param temperature
 */
void Graphique::ajouterDonneeTemperature(double temperature)
{
    QDateTime fin;
    fin = QDateTime::currentDateTime();

    axeXTemperature->setMin(debut);
    if(temperature > axeYTemperatureMax)
    {
        axeYTemperature->setRange(axeYTemperatureMin, temperature);
        axeYTemperatureMax = temperature;
    }
    else if(temperature < axeYTemperatureMin)
    {
        axeYTemperature->setRange(temperature, axeYTemperatureMax);
        axeYTemperatureMin = temperature;
    }
    courbeTemperature->append(fin.toMSecsSinceEpoch(), temperature);
    axeXTemperature->setMax(fin);

    graphiqueTemperature->setChart(grapheTemperature);

}

/**
 * @brief Méthode appelée pour ajouter des valeurs au graphique humidité
 *
 * @fn Graphique::ajouterDonneeHumidite
 * @param humidite
 */
void Graphique::ajouterDonneeHumidite(int humidite)
{
    QDateTime fin;
    fin = QDateTime::currentDateTime();

    axeXHumidite->setMin(debut);
    courbeHumidite->append(fin.toMSecsSinceEpoch(), humidite);
    axeXHumidite->setMax(fin);

    graphiqueHumidite->setChart(grapheHumidite);


}

/**
 * @brief Méthode appelée pour ajouter des valeurs au graphique luminosité
 *
 * @fn Graphique::ajouterDonneeLuminosite
 * @param luminosite
 */
void Graphique::ajouterDonneeLuminosite(int luminosite)
{
    QDateTime fin;
    fin = QDateTime::currentDateTime();

    axeXLuminosite->setMin(debut);
    if(luminosite > axeYLuminositeMax)
    {
        axeYLuminosite->setRange(0, luminosite);
        axeYLuminositeMax = luminosite;
    }
    courbeLuminosite->append(fin.toMSecsSinceEpoch(), luminosite);
    axeXLuminosite->setMax(fin);

    graphiqueLuminosite->setChart(grapheLuminosite);
    graphiqueLuminosite->update();

}

/**
 * @brief Méthode appelée pour ajouter des valeurs au graphique pression
 *
 * @fn Graphique::ajouterDonneePression
 * @param pression
 */
void Graphique::ajouterDonneePression(int pression)
{
    QDateTime fin;
    fin = QDateTime::currentDateTime();

    axeXPression->setMin(debut);
    if(pression > axeYPressionMax)
    {
        axeYPression->setRange(0, pression);
        axeYPressionMax = pression;
    }
    courbePression->append(fin.toMSecsSinceEpoch(), pression);
    axeXPression->setMax(fin);

    graphiquePression->setChart(graphePression);
    graphiquePression->update();
}
