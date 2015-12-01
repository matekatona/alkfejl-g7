#ifndef ROBOT_H
#define ROBOT_H

#include "linesensor.h"
#include "accelsensor.h"
#include "gyrosensor.h"
#include "wheelsensor.h"
#include "commandsocket.h"

class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot();

signals:
    void status(robot_status_t status);
    void speed(float speed);
    void gyrodata(float x, float y, float z);
    void acceldata(float x, float y, float z);
    void linedata(std::vector<float> line);
    void wheeldata(float left, float right);

public slots:
    void setStatus(QString status);
    void getSpeed();
    void getStatus();
    void setSpeed(float speed);
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
