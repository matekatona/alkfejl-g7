#ifndef ACCELSENSOR_H
#define ACCELSENSOR_H

#include "abstractsensor.h"

class AccelSensor : public AbstractSensor
{
public:
    explicit AccelSensor();
    float GetX();
    float GetY();
    float GetZ();

private:
    float currentX;
    float currentY;
    float currentZ;

};

#endif // ACCELSENSOR_H
