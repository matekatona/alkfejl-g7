#include "accelsensor.h"

AccelSensor::AccelSensor()
{
    // connect?
}

/*!
 * \brief AccelSensor::GetX returns acceleration in x direction
 * \return -||-
 */
float
AccelSensor::GetX()
{
    // ez így szar mer egymás után akarod lekérdezni őket, de em összetartozó értékek jönnek majd
    // kell majd weakptr móka meg cache meg a faszom
    // ha van a cache-ben érvénye xyz akkor visszatérünk vele
    // ha nincs akkor kérünk readSensor()-ral és frissítjük a cache-t
    // érvénytelenítés nemtom hogy legyen
    // mind3 olvasása után vagy timeout után sztem jo lesz (amelyik elöbb)
    QString raw = this->readSensor();
    QStringList values = raw.split(QRegExp("\\s"));
    this->currentX = values[0].toFloat();
    this->currentY = values[1].toFloat();
    this->currentZ = values[2].toFloat();

    return this->currentX;
}

/*!
 * \brief AccelSensor::GetY returns acceleration in y direction
 * \return -||-
 */
float
AccelSensor::GetY()
{
    QString raw = this->readSensor();
    QStringList values = raw.split(QRegExp("\\s"));
    this->currentX = values[0].toFloat();
    this->currentY = values[1].toFloat();
    this->currentZ = values[2].toFloat();

    return this->currentY;
}

/*!
 * \brief AccelSensor::GetZ returns acceleration in z direction
 * \return -||-
 */
float
AccelSensor::GetZ()
{
    QString raw = this->readSensor();
    QStringList values = raw.split(QRegExp("\\s"));
    this->currentX = values[0].toFloat();
    this->currentY = values[1].toFloat();
    this->currentZ = values[2].toFloat();

    return this->currentZ;
}
