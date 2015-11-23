#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "vrepcomm.h"

class AbstractSensor : VREPComm
{
public:
    AbstractSensor();


private:
    QString recvUntilNewline();

};

#endif // ABSTRACTSENSOR_H
