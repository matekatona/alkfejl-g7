#ifndef GYROSENSOR_H
#define GYROSENSOR_H

#include "abstractsensor.h"

class GyroSensor : public AbstractSensor
{
    Q_OBJECT
public:
    explicit GyroSensor();
    float getX();
    float getY();
    float getZ();

private slots:
    void reset_cache();

private:
    std::shared_ptr<float> px;
    std::shared_ptr<float> py;
    std::shared_ptr<float> pz;

    std::weak_ptr<float> cachex;
    std::weak_ptr<float> cachey;
    std::weak_ptr<float> cachez;
};

#endif // GYROSENSOR_H
