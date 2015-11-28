#include "gyrosensor.h"


using namespace std;


GyroSensor::GyroSensor()
    : AbstractSensor(port = 26489)
{
    this->cachex = this->px;
    this->cachey = this->py;
    this->cachez = this->pz;
    this->px.reset();
    this->py.reset();
    this->pz.reset();
}

/*!
 * \brief GyroSensor::GetX returns what?
 * \return -||-
 */
float
AccelSensor::GetX()
{
    float x;
    // check for value in cache
    std::shared_ptr<float> cx = this->cachex.lock();
    if(cx)
    {
        // use cached value
        x = *cx;
        this->px.reset();
    }
    else
    {
        // read new values
        QString raw = this->readSensor();
        QStringList values = raw.split(QRegExp("\\s"));
        x = values[0].toFloat();
        float y = values[1].toFloat();
        float z = values[2].toFloat();
        // cache the other values
        this->py = std::make_shared<float>(y);
        this->pz = std::make_shared<float>(z);
    }
    return x;
}

/*!
 * \brief GyroSensor::GetY returns what?
 * \return -||-
 */
float
AccelSensor::GetY()
{
    float y;
    // check for value in cache
    std::shared_ptr<float> cy = this->cachey.lock();
    if(cy)
    {
        // use cached value
        y = *cy;
        this->py.reset();
    }
    else
    {
        // read new values
        QString raw = this->readSensor();
        QStringList values = raw.split(QRegExp("\\s"));
        float x = values[0].toFloat();
        y = values[1].toFloat();
        float z = values[2].toFloat();
        // cache the other values
        this->px = std::make_shared<float>(x);
        this->pz = std::make_shared<float>(z);
    }
    return y;
}

/*!
 * \brief GyroSensor::GetZ returns what?
 * \return -||-
 */
float
AccelSensor::GetZ()
{
    float z;
    // check for value in cache
    std::shared_ptr<float> cz = this->cachez.lock();
    if(cz)
    {
        // use cached value
        z = *cz;
        this->pz.reset();
    }
    else
    {
        // read new values
        QString raw = this->readSensor();
        QStringList values = raw.split(QRegExp("\\s"));
        float x = values[0].toFloat();
        float y = values[1].toFloat();
        z = values[2].toFloat();
        // cache the other values
        this->px = std::make_shared<float>(x);
        this->py = std::make_shared<float>(y);
    }
    return z;
}


