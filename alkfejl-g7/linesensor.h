#ifndef LINESENSOR_H
#define LINESENSOR_H


#include "abstractsensor.h"


class LineSensor : public AbstractSensor
{
public:
    LineSensor();
    bool isOk();
    float getValue();

private:
    float currentValue;
};

#endif // LINESENSOR_H
