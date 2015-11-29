#ifndef ROBOT_H
#define ROBOT_H

#include "abstractsensor.h"
#include "linesensor.h"
#include "accelsensor.h"
#include "gyrosensor.h"
#include "wheelsensor.h"
#include "commandsocket.h"

class Robot : public AbstractSensor
{
public:
    explicit Robot();

signals:
    void status();
    void speed();
    void gyrodata();
    void acceldata();
    void linedata();
    void wheeldata();

public slots:
    void run();
    void stop();
    void getSpeed();
    void setSpeed();
    void getGyroData();
    void getAccelData();
    void getLineData();
    void getWheelData();

private:
    std::unique_ptr<GyroSensor> gyro;
    std::unique_ptr<AccelSensor> accel;
    std::unique_ptr<LineSensor> line;
    std::unique_ptr<WheelSensor> wheel;
    std::unique_ptr<CommandSocket> cmd;
};

#endif // ROBOT_H
