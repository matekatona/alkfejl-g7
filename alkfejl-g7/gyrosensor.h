//! \file 
//! \brief This file contains the GyroSensor class.

#ifndef GYROSENSOR_H
#define GYROSENSOR_H

#include "simcomm.h"
/*!
 * \brief This class is for reading the values of the gyro sensor of the robot.
 *
 * The class uses cache to store sensor values to minimize communication with
 * the simulator. Every read value is cached, and expires after 70 ms. Repeated
 * reads within this 70 ms will return the same values.
 */
class GyroSensor : public SimComm
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
