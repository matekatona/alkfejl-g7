#include "wheelsensor.h"

/*!
 * \brief WheelSensor::WheelSensor
 */
WheelSensor::WheelSensor()
    : AbstractSensor(30568)  // call superclass constructor with correct port number
{
    this->cacheleft = this->pleft;
    this->cacheright = this->pright;
    this->pleft=std::make_shared<float>(0.0);
    this->pright=std::make_shared<float>(0.0);
}

void
WheelSensor::readSensor()
{
    while(!this->socket.canReadLine()){}

    QByteArray rawData = this->socket.readAll();
    QString rawString(rawData);

    QStringList rawValues = rawString.split(" ");
    float left, right;
    left=rawValues[0].toFloat();
    right=rawValues[1].toFloat();
    this->pleft = std::make_shared<float>(left);
    this->pright = std::make_shared<float>(right);

    emit this->dataReady();
}


/*!
 * \brief WheelSensor::getLeft returns what?
 * \return -||-
 */
float
WheelSensor::getLeft()
{
    return *this->pleft.get();
}


/*!
 * \brief WheelSensor::getRight returns what?
 * \return -||-
 */
float
WheelSensor::getRight()
{
    return *this->pright.get();
}
