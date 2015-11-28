#ifndef WHEELSENSOR_H
#define WHEELSENSOR_H


#include "abstractsensor.h"


class WheelSensor : public AbstractSensor
{
public:
    WheelSensor();
    float getLeft();
    float getRight();

private:
    std::shared_ptr<float> pleft;
    std::shared_ptr<float> pright;

    std::weak_ptr<float> cacheleft;
    std::weak_ptr<float> cacheright;
};

#endif // WHEELSENSOR_H
