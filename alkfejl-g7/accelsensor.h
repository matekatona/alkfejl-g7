#ifndef ACCELSENSOR_H
#define ACCELSENSOR_H

#include "simcomm.h"

class AccelSensor : public SimComm
{
    Q_OBJECT
public:
    explicit AccelSensor();
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

#endif // ACCELSENSOR_H
