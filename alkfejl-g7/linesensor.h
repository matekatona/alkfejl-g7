#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "abstractsensor.h"

class LineSensor : public AbstractSensor
{
public:
    LineSensor();

private:
    static const int port_num = 27753;
};

#endif // LINESENSOR_H
