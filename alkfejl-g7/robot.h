#ifndef ROBOT_H
#define ROBOT_H

#include "vrepcomm.h"
#include "linesensor.h"
#include "accelsensor.h"
#include "gyrosensor.h"

class Robot : public VREPComm
{
public:
    explicit Robot();
signals:
public slots:
private:
    GyroSensor gyro;
    AccelSensor accel;
    LineSensor line;
};

#endif // ROBOT_H
