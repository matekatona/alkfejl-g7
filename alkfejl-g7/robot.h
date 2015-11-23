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
    void init();
signals:
public slots:
private:
    GyroSensor gyro;
    AccelSensor accel;
    LineSensor linesens;
};

#endif // ROBOT_H
