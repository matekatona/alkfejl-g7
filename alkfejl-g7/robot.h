#ifndef ROBOT_H
#define ROBOT_H

#include "abstractsensor.h"
#include "linesensor.h"
#include "accelsensor.h"
#include "gyrosensor.h"

class Robot : public AbstractSensor
{
public:
    explicit Robot();
    void init();
    GyroSensor* getGyro();
    AccelSensor* getAccel();
    LineSensor* getLineSens();
signals:
public slots:
private:
    GyroSensor gyro;
    AccelSensor accel;
    LineSensor linesens;
};

#endif // ROBOT_H
