#ifndef WHEELSENSOR_H
#define WHEELSENSOR_H


#include "simcomm.h"


class WheelSensor : public SimComm
{
    Q_OBJECT
public:
    WheelSensor();
    float getLeft();
    float getRight();
    QVarLengthArray<float> getWheels();

private slots:
    void reset_cache();

private:
    std::shared_ptr<float> pleft;
    std::shared_ptr<float> pright;

    std::weak_ptr<float> cacheleft;
    std::weak_ptr<float> cacheright;
};

#endif // WHEELSENSOR_H
