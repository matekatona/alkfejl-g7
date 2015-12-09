#ifndef LINESENSOR_H
#define LINESENSOR_H


#include "simcomm.h"

#define LINE_THRESHOLD 0.5f

class LineSensor : public SimComm
{
    Q_OBJECT
public:
    LineSensor();
    QVarLengthArray<bool> getValues();
};

#endif // LINESENSOR_H
