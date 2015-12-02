#include "gyrosensor.h"

/*!
 * \brief GyroSensor::GyroSensor
 */
GyroSensor::GyroSensor()
    : AbstractSensor(26489)  // call superclass constructor with correct port number
{
    this->cachex = this->px;
    this->cachey = this->py;
    this->cachez = this->pz;
    this->px.reset();
    this->py.reset();
    this->pz.reset();
}

void
GyroSensor::readSensor()
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
 * \brief GyroSensor::GetX returns what?
 * \return -||-
 */
float
GyroSensor::getX()
{
    return *this->px.get();
}

/*!
 * \brief GyroSensor::GetY returns what?
 * \return -||-
 */
float
GyroSensor::getY()
{
    return *this->py.get();
}

/*!
 * \brief GyroSensor::GetZ returns what?
 * \return -||-
 */
float
GyroSensor::getZ()
{
    return *this->pz.get();
}


