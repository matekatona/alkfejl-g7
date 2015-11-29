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

// -------------------------------------------------
// --------------------- SIGNALS -------------------
// -------------------------------------------------

/*!
 * \brief status
 */
void
Robot::status()
{

}

/*!
 * \brief speed
 */
void
Robot::speed()
{

}

/*!
 * \brief gyro
 */
void
Robot::gyrodata()
{

}

/*!
 * \brief accel
 */
void
Robot::acceldata()
{

}

/*!
 * \brief line
 */
void
Robot::linedata(){

}

/*!
 * \brief wheel
 */
void
Robot::wheeldata()
{

}

// -------------------------------------------------
// ---------------------- SLOTS --------------------
// -------------------------------------------------

/*!
 * \brief run
 */
void
Robot::run()
{

}

/*!
 * \brief stop
 */
void
Robot::stop()
{

}

/*!
 * \brief getSpeed
 */
void
Robot::getSpeed(){

}

/*!
 * \brief setSpeed
 */
void
Robot::setSpeed()
{

}

/*!
 * \brief getGyroData
 */
void
Robot::getGyroData()
{

}

/*!
 * \brief getAccelData
 */
void
Robot::getAccelData()
{

}

/*!
 * \brief getLineData
 */
void
Robot::getLineData()
{

}

/*!
 * \brief getWheelData
 */
void
Robot::getWheelData()
{

}

























