#include "wheelsensor.h"

/*!
 * \brief WheelSensor::WheelSensor creates sensor object, that is connected to
 *        the wheelsensor port of V-REP
 */
WheelSensor::WheelSensor()
    : SimComm(PORT_NUM_WHEEL)  // call superclass constructor with correct port number
{
    this->cacheleft = this->pleft;
    this->cacheright = this->pright;
    this->pleft.reset();
    this->pright.reset();

    QObject::connect(this, SIGNAL(cache_expired()), this, SLOT(reset_cache()));
}

/*!
 * \brief WheelSensor::clear_cache delete cached sensor values
 *
 * The next sensor read will result in reading new values from V-REP
 * \see SimComm::cache_expired
 */
void
WheelSensor::reset_cache()
{
    this->pleft.reset();
    this->pright.reset();
}

/*!
 * \brief WheelSensor::getLeft get speed of left wheel
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read
 * \return left wheel speed in m/s?
 */
float
WheelSensor::getLeft()
{
    float left = 0.0/0.0;
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
            return left;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 2)
            return left;
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
 * \brief WheelSensor::getRight get speed of right wheel
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read
 * \return right wheel speed in m/s?
 */
float
WheelSensor::getRight()
{
    float right = 0.0/0.0;
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
            return right;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 2)
            return right;
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
 * \brief WheelSensor::getWheels returns both wheel speeds
 *
 * This function uses the `getLeft()` and `getRight()` functions inside,
 * and is provided for easier access to the values.
 * \return wheel speeds as [left, right]
 */
QVarLengthArray<float>
WheelSensor::getWheels()
{
    QVarLengthArray<float> wheels;
    wheels.insert(0,this->getLeft());
    wheels.insert(1,this->getRight());
    return wheels;
}
