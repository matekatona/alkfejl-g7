#include "wheelsensor.h"

/*!
 * \brief WheelSensor::WheelSensor
 */
WheelSensor::WheelSensor()
    : AbstractSensor(30568)  // call superclass constructor with correct port number
{
    this->cacheleft = this->pleft;
    this->cacheright = this->pright;
    this->pleft.reset();
    this->pright.reset();
}


/*!
 * \brief WheelSensor::getLeft returns what?
 * \return -||-
 */
float
WheelSensor::getLeft()
{
    float left;
    // check for value in cache
    std::shared_ptr<float> cleft = this->cacheleft.lock();
    if(cleft)
    {
        // use cached value
        left = *cleft;
        this->pleft.reset();
    }
    else
    {
        // read new values
        QString raw = this->readSensor();
        QStringList values = raw.split(QRegExp("\\s"));
        left = values[0].toFloat();
        float right = values[1].toFloat();
        // cache the other value
        this->pright = std::make_shared<float>(right);
    }
    return left;
}


/*!
 * \brief WheelSensor::getRight returns what?
 * \return -||-
 */
float
WheelSensor::getRight()
{
    float right;
    // check for value in cache
    std::shared_ptr<float> cright = this->cacheright.lock();
    if(cright)
    {
        // use cached value
        right = *cright;
        this->pright.reset();
    }
    else
    {
        // read new values
        QString raw = this->readSensor();
        QStringList values = raw.split(QRegExp("\\s"));
        float left = values[0].toFloat();
        right = values[1].toFloat();
        // cache the other value
        this->pleft = std::make_shared<float>(left);
    }
    return right;
}
