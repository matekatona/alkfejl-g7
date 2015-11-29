#include "linesensor.h"

/*!
 * \brief LineSensor::LineSensor
 */
LineSensor::LineSensor()
    : AbstractSensor(27753)  // call superclass constructor with correct port number
{
    this->currentValue = 0.0f;
}

/*!
 * \brief LineSensor::isOk
 * \return
 */
bool
LineSensor::isOk()
{
    return (this->currentValue < 0.5f);
}

/*!
 * \brief LineSensor::getValue
 * \return
 */
float
LineSensor::getValue()
{
    QString raw = this->readSensor();
    if(raw == "ERROR")
    {
        throw std::runtime_error("this is not really a runtime error");
    }
    this->currentValue = raw.toFloat();
    return this->currentValue;
}
