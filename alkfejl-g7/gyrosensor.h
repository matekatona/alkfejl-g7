#ifndef GYROSENSOR_H
#define GYROSENSOR_H

#include "abstractsensor.h"

class GyroSensor : AbstractSensor
{
public:
    explicit GyroSensor();

private:
    static const int port_num = 26489;
};

#endif // GYROSENSOR_H
