#ifndef ACCELSENSOR_H
#define ACCELSENSOR_H


#include "abstractsensor.h"


class AccelSensor : public AbstractSensor
{
public:
    explicit AccelSensor();
    float getX();
    float getY();
    float getZ();

private slots:
    void readSensor();

private:
    std::shared_ptr<float> px;
    std::shared_ptr<float> py;
    std::shared_ptr<float> pz;

    std::weak_ptr<float> cachex;
    std::weak_ptr<float> cachey;
    std::weak_ptr<float> cachez;
};

#endif // ACCELSENSOR_H
