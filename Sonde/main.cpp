#include "ihm.h"
#include <QApplication>

/**
* @file main.cpp
*
* @brief Programme principal ...
*
* @details Crée et affiche la fenêtre principale de l'application ...
*
* @author Bounoir Fabien
* @author Villesseche Ethan
*
* @version 3.0
*
* @fn main(int argc, char *argv[])
* @param argc
* @param argv[]
* @return int
*
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ihm w;
    w.show();

    return a.exec();
}
