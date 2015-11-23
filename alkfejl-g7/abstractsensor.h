#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "vrepcomm.h"

class AbstractSensor : VREPComm
{
    Q_OBJECT
public:
    AbstractSensor();
    int connect(int port);
    void get_data();

private:
};

#endif // ABSTRACTSENSOR_H
