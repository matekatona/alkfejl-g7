#include "wheelsensor.h"

/*!
 * \brief WheelSensor::WheelSensor
 */
WheelSensor::WheelSensor()
    : SimComm(30568)  // call superclass constructor with correct port number
{
    this->cacheleft = this->pleft;
    this->cacheright = this->pright;
    this->pleft.reset();
    this->pright.reset();
    QObject::connect(this, SIGNAL(cache_expired()), this, SLOT(reset_cache()));
}

/*!
 * \brief WheelSensor::reset_cache
 */
void
WheelSensor::reset_cache()
{
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
    }
    else
    {
        // read new values
        QString raw = this->read();
        if(raw.length() < 10)
            return 0.0/0.0;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 2)
            return 0.0/0.0;
        left = values[0].toFloat();
        float right = values[1].toFloat();
        // cache value
        this->pleft = std::make_shared<float>(left);
        this->cacheleft = this->pleft;
        this->pright = std::make_shared<float>(right);
        this->cacheright = this->pright;
        this->start_cache_timer();  // will reset cache 70ms later
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
    }
    else
    {
        // read new values
        QString raw = this->read();
        if(raw.length() < 10)
            return 0.0/0.0;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 2)
            return 0.0/0.0;
        float left = values[0].toFloat();
        right = values[1].toFloat();
        // cache value
        this->pleft = std::make_shared<float>(left);
        this->cacheleft = this->pleft;
        this->pright = std::make_shared<float>(right);
        this->cacheright = this->pright;
        this->start_cache_timer();  // will reset cache 70ms later
    }
    return right;
}

/*!
 * \brief WheelSensor::getWheels
 * \return
 */
QVarLengthArray<float>
WheelSensor::getWheels()
{
    QVarLengthArray<float> wheels;
    wheels.insert(0,this->getLeft());
    wheels.insert(1,this->getRight());
    return wheels;
}
