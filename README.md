\mainpage Mini-projet Qt Sonde ESP32

\section section_tdm Table des matières
- \ref page_README
- \ref page_changelog
- \ref todo
- \ref page_about
- \ref page_licence

## Programme Qt

Le programme, réalisé avec le framework Qt 5.11.2, permet de communiquer avec une sonde équipée de différents capteurs. 

L'IHM affiche les informations des capteurs dans l'onglet Données. Il est possible de consulter les relevés de mesures sous forme de graphiques.

\image html capture-onglet-donnees.png
\image latex capture-onglet-donnees.png

\image html capture-onglet-graphiques.png
\image latex capture-onglet-graphiques.png

Il est possible de consulter les données météos d'une ville dont il est possible de saisir le nom. Un affichage des coordonnées GPS est dipsonible.

\image html capture-onglet-meteo.png
\image latex capture-onglet-meteo.png

Tous les échanges de trame s'affichent dans l'onglet Opérateur où il est également possible de piloter la led manuellement selon le protocole.

\image html capture-onglet-operateur.png
\image latex capture-onglet-operateur.png

La communication se fera au choix de l'utilisateur, soit par liaison série soit par communication Bluetooth. La communication via WiFi n'est pas implémentée dans ce programme.

\image html capture-onglet-configuration.png
\image latex capture-onglet-configuration.png

## Sonde ESP32-Weather

La carte ESP32-Weather est une sonde construite autour d'un ESP32 et équipée d'un module **BlueDot** I2C, qui intègre un capteur d'éclairement lumineux **TSL 2591** et un capteur **BME280** (température, humidité et pression atmosphétrique), et d'une Led Bicolore. Les mesures sont affichées périodiquement sur l'écran **OLED** de la carte.

La sonde communique aussi via le WiFi, le Bluetooth et la liaison série. Le même protocole est utilisé pour les trois modes de communication. L'écran de la sonde affiche l'adresse IP et le numéro de port utilisés pour une communication WiFi et l'adresse MAC de l'interface Bluetooth.

La carte a été réalisée par des étudiants d'EC et le programme de l'ESP32 par un professeur.

\image html ESP32_weather.png
\image latex ESP32_weather.png

## Auteurs

\a Fabien Bounoir (IR) <bounoirfabien@gmail.com>

\a Ethan Villesseche (IR) <villesseche.ethan@gmail.com>

\page page_README README

## Nom : Mini-projet Qt Sonde ESP32 (BTS SN-IR La Salle Avignon)

## Numéro de version : 4.1

## Auteurs

\a Fabien Bounoir (IR) <bounoirfabien@gmail.com>

\a Ethan Villesseche (IR) <villesseche.ethan@gmail.com>

## Description

Le programme a été réalisé avec le framework Qt 5.11.2.

Fichier `.pro` :

```
QT       += core gui \
            serialport network \
            bluetooth \
            positioning \
            charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sonde
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        ihm.cpp \
    transmission.cpp \
    esp32.cpp \
    meteo.cpp \
    graphique.cpp \
    gps.cpp

HEADERS += \
        ihm.h \
    transmission.h \
    esp32.h \
    meteo.h \
    graphique.h \
    gps.h

FORMS += \
        ihm.ui

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
```

## Protocole

```
SONDE;TEMPERATURE;UNITE;RESSENTIE;UNITE;HUMIDITE;UNITE;ECLAIREMENT;UNITE;PRESSION;UNITE;ALTITUDE;UNITE;\n
LED;ETAT LED ROUGE;ETAT LED VERTE;ETAT;COULEUR;\n
```

Exemple :

```
SONDE;20.8;C;20.0;C;41;%;997;lux;1007;hPa;52;m;\n -> Température 20,8 °C, Ressentie 20 °C, Humidité 41 %, un éclairement de 997 lux, une pression atmosphérique de 1007 hPa et d'une altitude évaluée à 52 m
LED;1;0;1;1;\n -> Le Led est allumée en rouge
```

_Remarques :_

- Les valeurs de température sont précisées au dixième de degré.
- Un booléen est égal à 0 pour false et 1 pour true.
- Les codes de couleur pour la Led sont : 
    - Aucune (éteinte) = 0
    - Rouge = 1
    - Verte = 2
    - Orange = 3

Les clients connectés ont la possibilité d'envoyer une requête pour commander la led :

```
SET LED commande\n
```

Le champ commande peut prendre les valeurs suivantes :

```
SET LED ON\n -> allume la Led dans sa couleur courante
SET LED OFF\n -> éteint la Led
SET LED 0\n -> éteint la Led
SET LED 1\n -> allume la Led en rouge
SET LED 2\n -> allume la Led en vert
SET LED 3\ -> allume la Led en orange
SET LED ROUGE\n -> allume la Led en rouge
SET LED VERT\n -> allume la Led en vert
SET LED VERTE\n -> allume la Led en vert
SET LED ORANGE\n -> allume la Led en orange
```

_Remarque : la requête est insensible à la casse._


\page page_about A propos
\author \a Fabien Bounoir (IR) <bounoirfabien@gmail.com>
\author \a Ethan Villesseche (IR) <villesseche.ethan@gmail.com>
\version 4.0
\date \b 2020

\page page_licence Licence GPL

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
