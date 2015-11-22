#ifndef ACCELSENSOR_H
#define ACCELSENSOR_H

#include "abstractsensor.h"

class AccelSensor : AbstractSensor
{
    Q_OBJECT
public:
    explicit AccelSensor();

private:
    static const int port_num = 24931;

};

#endif // ACCELSENSOR_H
