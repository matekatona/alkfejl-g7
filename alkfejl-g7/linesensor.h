#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "abstractsensor.h"

class LineSensor : public AbstractSensor
{
public:
    LineSensor();
    bool isOk();
    double getValue();

private:
    double currentValue;
};

#endif // LINESENSOR_H
