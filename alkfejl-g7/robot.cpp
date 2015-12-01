#include "robot.h"


/*!
 * \brief Robot::Robot
 */
Robot::Robot()
    : cmd(new CommandSocket(25455)),
      line(new LineSensor()),
      accel(new AccelSensor()),
      gyro(new GyroSensor()),
      wheel(new WheelSensor())
{
    // etwas
}

// ---------------------------------------------------------
// -------------------------- SLOTS ------------------------
// ---------------------------------------------------------

/*!
 * \brief Robot::update
 */
void
Robot::update(){
    // emit this->setAlert(alert);
    emit this->setLedStrip(this->line->getBools());
    float ay = this->accel->getY();
    emit this->setTextAccelX(this->accel->getX());
    emit this->setTextAccelY(ay);
    emit this->setTextAccelZ(this->accel->getZ());
    float gx = this->gyro->getX();
    float gy = this->gyro->getY();
    float gz = this->gyro->getZ();
    emit this->setTextGyroX(gx);
    emit this->setTextGyroY(gy);
    emit this->setTextGyroZ(gz);
    emit this->setTextStatus(this->cmd->getStatus());
    float speed = this->cmd->getSpeed();
    emit this->setTextSpeed(speed);
    QVarLengthArray<float> wheels;
    wheels.insert(0,this->wheel->getLeft());
    wheels.insert(1,this->wheel->getRight());
    emit this->setWheels(wheels, this->D);
    emit this->setCarAccelY(wheels, ay);
    emit this->setCarGyroX(gx);
    emit this->setCarGyroY(gy);
    emit this->setCarGyroZ(gz);
    emit this->drawSpeedGraph(speed);
}
