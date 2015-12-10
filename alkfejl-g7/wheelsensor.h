//! \file 
//! \brief This file contains the WheelSensor class.

#ifndef WHEELSENSOR_H
#define WHEELSENSOR_H

#include "simcomm.h"

/*!
 * \brief This class is for reading the values of the wheel sensor of the robot.
 *
 * It uses a cache to store sensor values to minimize communication with
 * the simulator. Every read value is cached, and expires after 70 ms. Repeated
 * reads within this 70 ms will return the same values.
 */
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
