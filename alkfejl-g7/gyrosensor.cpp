#include "gyrosensor.h"

/*!
 * \brief GyroSensor::GyroSensor creates sensor object, that is connected to
 *                               the gyroscope sensor port of V-REP
 */
GyroSensor::GyroSensor() :
    SimComm(PORT_NUM_GYRO)  // call superclass constructor with correct port number
{
    this->cachex = this->px;
    this->cachey = this->py;
    this->cachez = this->pz;
    this->px.reset();
    this->py.reset();
    this->pz.reset();

    QObject::connect(this, SIGNAL(cache_expired()), this, SLOT(reset_cache()));
}

/*!
 * \brief GyroSensor::clear_cache deletes cached sensor values
 *
 * The next sensor read will result in reading new values from V-REP
 * \see SimComm::cache_expired
 */
void
GyroSensor::reset_cache()
{
    this->px.reset();
    this->py.reset();
    this->pz.reset();
}

/*!
 * \brief GyroSensor::getX get robot rotation speed around longitudinal axis
                           (aka roll rate)
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read
 * \return roll rate in deg/s?
 */
float
GyroSensor::getX()
{
    float x;
    // check for value in cache
    std::shared_ptr<float> cx = this->cachex.lock();
    if(cx)
    {
        // use cached value
        x = *cx;
    }
    else
    {
        // read new values
        QString raw = this->read();
        if(raw.length() < 20)
            return 0.0/0.0;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 3)
            return 0.0/0.0;
        x = values[0].toFloat();
        float y = values[1].toFloat();
        float z = values[2].toFloat();
        // cache values
        this->px = std::make_shared<float>(x);
        this->cachex = this->px;
        this->py = std::make_shared<float>(y);
        this->cachey = this->py;
        this->pz = std::make_shared<float>(z);
        this->cachez = this->pz;
        this->start_cache_timer();  // will reset cache 70ms later
    }
    return x;
}

/*!
 * \brief GyroSensor::getY get robot rotation speed around lateral axis
                           (aka pitch rate)
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read
 * \return pitch rate in deg/s?
 */
float
GyroSensor::getY()
{
    float y;
    // check for value in cache
    std::shared_ptr<float> cy = this->cachey.lock();
    if(cy)
    {
        // use cached value
        y = *cy;
    }
    else
    {
        // read new values
        QString raw = this->read();
        if(raw.length() < 20)
            return 0.0/0.0;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 3)
            return 0.0/0.0;
        float x = values[0].toFloat();
        y = values[1].toFloat();
        float z = values[2].toFloat();
        // cache values
        this->px = std::make_shared<float>(x);
        this->cachex = this->px;
        this->py = std::make_shared<float>(y);
        this->cachey = this->py;
        this->pz = std::make_shared<float>(z);
        this->cachez = this->pz;
        this->start_cache_timer();  // will reset cache 70ms later
    }
    return y;
}

/*!
 * \brief GyroSensor::getY get robot rotation speed around vertical axis
                           (aka yaw rate)
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read
 * \return yaw rate in deg/s?
 */
float
GyroSensor::getZ()
{
    float z;
    // check for value in cache
    std::shared_ptr<float> cz = this->cachez.lock();
    if(cz)
    {
        // use cached value
        z = *cz;
    }
    else
    {
        // read new values
        QString raw = this->read();
        if(raw.length() < 20)
            return 0.0/0.0;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 3)
            return 0.0/0.0;
        float x = values[0].toFloat();
        float y = values[1].toFloat();
        z = values[2].toFloat();
        // cache values
        this->px = std::make_shared<float>(x);
        this->cachex = this->px;
        this->py = std::make_shared<float>(y);
        this->cachey = this->py;
        this->pz = std::make_shared<float>(z);
        this->cachez = this->pz;
        this->start_cache_timer();  // will reset cache 70ms later
    }
    return z;
}
