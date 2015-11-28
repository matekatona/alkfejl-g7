#include "linesensor.h"

LineSensor::LineSensor()
    : AbstractSensor(port = 27753)
{
    this->currentValue = 0.0f;
}

bool
LineSensor::isOk()
{
    return (this->currentValue < 0.5f);
}

float
LineSensor::getValue()
{
    QString raw = this->readSensor();
    if(raw == "ERROR")
    {
        throw error;
    }
    this->currentValue = raw.toFloat();
    return this->currentValue;
}
