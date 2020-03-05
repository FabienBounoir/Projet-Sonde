#ifndef GPS_H
#define GPS_H

#include <QObject>

/**
 * @file gps.h
 *
 * @brief Declaration de la classe Gps
 *
 * @version 4.1
 *
 * @author Bounoir Fabien
 * @author Villesseche Ethan
 */

/**
 * @class Gps gps.h "gps.h"
 *
 * @brief Declaration de la classe Gps
*/
class Gps
{
public:
    Gps();      /** constructeur de la classe GPS */
    ~Gps();     /** destructeur de la classe GPS */

    double getLatitude() const;     /** recuperer la latitude */
    double getLongitude() const;    /** recuperer la longitune */

    void setLatitude(double latitude);      /** fixe la valeur de la latitude */
    void setLongitude(double longitude);    /** fixe la valeur de la longitude */

private:
    double latitude;        //!<  variable qui stocke la latitude
    double longitude;       //!<  variable qui stocke la longitude
};

#endif // GPS_H
