#include "robot.h"


/*!
 * \brief Robot::Robot creates a robot object, trough which the GUI can
 *                     communicate with all V-REP sockets in an organized way
 */
Robot::Robot()
    : control(new RobotControl()),  // order of initialization is crucial!!!
      line(new LineSensor()),       // V-REP will freeze with any other order
      accel(new AccelSensor()),     // but we have no time to fix this in V-REP
      gyro(new GyroSensor()),       // and no one will notice anyway
      wheel(new WheelSensor())      // at least we hope so
{
    // etwas
}

/*!
 * \brief Robot::connect connects all sockets to V-REP
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
 * \brief Robot::disconnect disconnects all sockets from V-REP
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
 * \brief Robot::speed slot to set speed of robot
 * \param speed the speed to be set
 */
void
Robot::speed(float speed)
{
    this->control->setSpeed(speed);
}

/*!
 * \brief Robot::status slot to set status of robot
 * \param status the status to be set
 */
void
Robot::status(QString status)
{
    this->control->setStatus(status);
}

/*!
 * \brief Robot::update slot to send an update request to all sensors
 *
 * This slot will emit signals to update all GUI elements with sensor data read
 * from V-REP
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
