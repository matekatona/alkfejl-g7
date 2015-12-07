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
    QObject::connect(this, SIGNAL(cache_expired()), this, SLOT(reset_cache()));
}

/*!
 * \brief GyroSensor::reset_cache
 */
void
GyroSensor::reset_cache()
{
    this->px.reset();
    this->py.reset();
    this->pz.reset();
}

/*!
 * \brief GyroSensor::GetX returns what?
 * \return -||-
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
        QString raw = this->readSensor();
        if(raw.length() < 1)
            return 0.0;
        QStringList values = raw.split(QRegExp("\\s"));
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
 * \brief GyroSensor::GetY returns what?
 * \return -||-
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
        QString raw = this->readSensor();
        if(raw.length() < 1)
            return 0.0;
        QStringList values = raw.split(QRegExp("\\s"));
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
 * \brief GyroSensor::GetZ returns what?
 * \return -||-
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
        QString raw = this->readSensor();
        if(raw.length() < 1)
            return 0.0;
        QStringList values = raw.split(QRegExp("\\s"));
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


