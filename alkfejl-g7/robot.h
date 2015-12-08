#ifndef ROBOT_H
#define ROBOT_H

#include "linesensor.h"
#include "accelsensor.h"
#include "gyrosensor.h"
#include "wheelsensor.h"
#include "robotcontrol.h"

class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot();

signals:
    void setAlert(bool alert);
    void setLedStrip(QVarLengthArray<bool> leds);
    void setTextAccelX(float accelX);
    void setTextAccelY(float accelY);
    void setTextAccelZ(float accelZ);
    void setTextGyroX(float gyroX);
    void setTextGyroY(float gyroY);
    void setTextGyroZ(float gyroZ);
    void setTextStatus(QString status);
    void setTextSpeed(float speed);
    void setWheels(QVarLengthArray<float> wheels, const float D);
    void setCarAccelY(QVarLengthArray<float> wheels, float accelY);
    void setCarGyroX(float gyroX);
    void setCarGyroY(float gyroY);
    void setCarGyroZ(float gyroZ);
    void drawSpeedGraph(float speed);

public slots:
    void update();
    void speed(float speed);
    void status(QString status);

private:
    std::unique_ptr<RobotControl> control;
    std::unique_ptr<LineSensor> line;
    std::unique_ptr<AccelSensor> accel;
    std::unique_ptr<GyroSensor> gyro;
    std::unique_ptr<WheelSensor> wheel;
    const float D = 0.12;
};

#endif // ROBOT_H
