#include "accelsensor.h"

/*!
 * \brief AccelSensor::AccelSensor creates sensor object, that is connected to
 *                                 the acceleration sensor port of V-REP
 */
AccelSensor::AccelSensor() :
    SimComm(PORT_NUM_ACCEl)  // call superclass constructor with correct port number
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
 * \brief AccelSensor::clear_cache delete cached sensor values
 *
 * The next sensor read will result in reading new values from V-REP
 * \see SimComm::cache_expired
 */
void
AccelSensor::reset_cache()
{
    this->px.reset();
    this->py.reset();
    this->pz.reset();
}

/*!
 * \brief AccelSensor::getX get robot acceleration in longitudinal direction
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read, the function that is internally used to get data from V-REP.
 * \return longitudinal acceleration in m/s?
 */
float
AccelSensor::getX()
{
    float x = 0.0/0.0;
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
            return x;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 3)
            return x;
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
 * \brief AccelSensor::getY get robot acceleration in lateral direction
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read, the function that is internally used to get data from V-REP.
 * \return lateral acceleration in m/s?
 */
float
AccelSensor::getY()
{
    float y = 0.0/0.0;
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
            return y;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 3)
            return y;
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
 * \brief AccelSensor::getZ get robot acceleration in vertical direction
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read, the function that is internally used to get data from V-REP.
 * \return vertical acceleration in m/s?
 */
float
AccelSensor::getZ()
{
    float z = 0.0/0.0;
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
            return z;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 3)
            return z;
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
