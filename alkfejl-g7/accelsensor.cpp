#include "accelsensor.h"

/*!
 * \brief AccelSensor::AccelSensor
 */
AccelSensor::AccelSensor()
    : AbstractSensor(24931)  // call superclass constructor with correct port number
{
    this->cachex = this->px;
    this->cachey = this->py;
    this->cachez = this->pz;
    this->px.reset();
    this->py.reset();
    this->pz.reset();
}

void
AccelSensor::readSensor()
{
    QByteArray rawData = this->socket.readAll();
    QString rawString(rawData);

    QStringList rawValues = rawString.split(" ");
    float x, y, z;
    x=rawValues[0].toFloat();
    y=rawValues[1].toFloat();
    z=rawValues[2].toFloat();
    this->px = std::make_shared<float>(x);
    this->py = std::make_shared<float>(y);
    this->pz = std::make_shared<float>(z);

    emit this->dataReady();
}

/*!
 * \brief AccelSensor::GetX returns acceleration in x direction
 * \return -||-
 */
float
AccelSensor::getX()
{
    return *this->px.get();
}

/*!
 * \brief AccelSensor::GetY returns acceleration in y direction
 * \return -||-
 */
float
AccelSensor::getY()
{
    return *this->py.get();
}

/*!
 * \brief AccelSensor::GetZ returns acceleration in z direction
 * \return -||-
 */
float
AccelSensor::getZ()
{
    return *this->pz.get();
}
