#include "robot.h"


/*!
 * \brief Robot::Robot
 */
Robot::Robot()
    : control(new RobotControl()),  // order of initialization is crucial!!!
      line(new LineSensor()),       // VREP will freeze with other orders
      accel(new AccelSensor()),     // but we have no time to fix this in VREP
      gyro(new GyroSensor()),       // and noone will notice anyway
      wheel(new WheelSensor())
{
    // etwas
}

/*!
 * \brief Robot::connect
 */
void
Robot::connect()
{
    this->control->connect();
    this->line->connect();
    this->accel->connect();
    this->gyro->connect();
    this->wheel->connect();
}

/*!
 * \brief Robot::disconnect
 */
void
Robot::disconnect()
{
    this->control->disconnect();
    this->line->disconnect();
    this->accel->disconnect();
    this->gyro->disconnect();
    this->wheel->disconnect();
}

/*!
 * \brief Robot::speed
 * \param speed
 */
void
Robot::speed(float speed)
{
    this->control->setSpeed(speed);
}

/*!
 * \brief Robot::status
 * \param status
 */
void
Robot::status(QString status)
{
    this->control->setStatus(status);
}

/*!
 * \brief Robot::update
 */
void
Robot::update(){
    emit this->setLedStrip(this->line->getValues());
    emit this->setTextAccelX(this->accel->getX());
    emit this->setTextAccelY(this->accel->getY());
    emit this->setTextAccelZ(this->accel->getZ());
    emit this->setTextGyroX(this->gyro->getX());
    emit this->setTextGyroY(this->gyro->getY());
    emit this->setTextGyroZ(this->gyro->getZ());
    emit this->setTextStatus(this->control->getStatus());
    emit this->setTextSpeed(this->control->getSpeed());
    emit this->setWheels(this->wheel->getWheels(), this->D);
    emit this->setCarAccelY(this->wheel->getWheels(), this->accel->getY());
    emit this->setCarGyroX(this->gyro->getX());
    emit this->setCarGyroY(this->gyro->getY());
    emit this->setCarGyroZ(this->gyro->getZ());
    emit this->drawSpeedGraph(this->control->getSpeed());
}
