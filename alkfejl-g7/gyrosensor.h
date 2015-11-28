#ifndef GYROSENSOR_H
#define GYROSENSOR_H

#include "abstractsensor.h"

class GyroSensor : public AbstractSensor
{
public:
    explicit GyroSensor();

private:
    std::shared_ptr<float> px;
    std::shared_ptr<float> py;
    std::shared_ptr<float> pz;

    std::weak_ptr<float> cachex;
    std::weak_ptr<float> cachey;
    std::weak_ptr<float> cachez;
};

#endif // GYROSENSOR_H
