#ifndef LINESENSOR_H
#define LINESENSOR_H


#include "abstractsensor.h"

#define LINE_THRESHOLD 0.5f


class LineSensor : public AbstractSensor
{
    Q_OBJECT
public:
    LineSensor();
    QVarLengthArray<bool> getValues();
};

#endif // LINESENSOR_H
