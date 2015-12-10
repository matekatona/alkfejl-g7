#ifndef ACCELSENSOR_H
#define ACCELSENSOR_H

#include "simcomm.h"

/*!
 * \brief This class is for reading the values of the acceleration sensor of the robot.
 *
 * It uses cache to store sensor values to minimize communication with
 * the simulator. Every read value is cached, and expires after 70 ms. Repeated
 * reads within this 70 ms will return the same values.
 */

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
