#include "robot.h"


/*!
 * \brief Robot::Robot
 */
Robot::Robot()
    : gyro(new GyroSensor()),
      accel(new AccelSensor()),
      line(new LineSensor()),
      wheel(new WheelSensor()),
      cmd(new CommandSocket(25455))
{
    // etwas
}

// ---------------------------------------------------------
// -------------------------- SLOTS ------------------------
// ---------------------------------------------------------

/*!
 * \brief Robot::setStatus
 */
void
Robot::setStatus(QString status)
{
    if(status == "Run")
        this->cmd->run();
    if(status == "Stop")
        this->cmd->stop();
    emit this->getStatus();
}

/*!
 * \brief getSpeed
 */
void
Robot::getSpeed(){
    float speed = this->cmd->getSpeed();
    emit this->speed(speed);
}

void
Robot::getStatus()
{
    robot_status_t status = this->cmd->getStatus();
    emit this->status(status);
}

/*!
 * \brief setSpeed
 */
void
Robot::setSpeed(float speed)
{
    this->cmd->setSpeed(speed);
}

/*!
 * \brief getGyroData
 */
void
Robot::getGyroData()
{
    float gx = this->gyro->getX();
    float gy = this->gyro->getY();
    float gz = this->gyro->getZ();
    emit this->gyrodata(gx, gy, gz);
}

/*!
 * \brief getAccelData
 */
void
Robot::getAccelData()
{
    float ax = this->accel->getX();
    float ay = this->accel->getY();
    float az = this->accel->getZ();
    emit this->acceldata(ax, ay, az);
}

/*!
 * \brief getLineData
 */
void
Robot::getLineData()
{   // TODO this is not serious, but better than an empty function
    float value = this->line->getValue();
    std::vector<float> valvec = {value};
    emit this->linedata(valvec);
}

/*!
 * \brief getWheelData
 */
void
Robot::getWheelData()
{
    float left = this->wheel->getLeft();
    float right = this->wheel->getRight();
    emit this->wheeldata(left, right);
}
