#ifndef ROBOT_H
#define ROBOT_H

#include "vrepcomm.h"
#include "gyrosensor.h"
#include "accelsensor.h"
#include "linesensor.h"

class Robot : public VREPComm
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);

signals:

public slots:

private:
    GyroSensor gyro;
    AccelSensor accel;
    LineSensor line;

    static const int port_num = 25455;
};

#endif // ROBOT_H
