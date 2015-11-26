#include "linesensor.h"

LineSensor::LineSensor()
{
    // connect?
}

bool
LineSensor::isOk()
{
    return currentValue < 0.5f;
}

float
LineSensor::getValue()
{
    QString raw = this->readSensor();
    // TODO check for error
    currentValue = raw.toFloat();
    return currentValue;
}
