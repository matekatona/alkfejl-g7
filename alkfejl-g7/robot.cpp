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
   QObject::connect(this->line.get(), SIGNAL(dataReady()), this, SLOT(lineSensDataReceived()));
   QObject::connect(this->accel.get(), SIGNAL(dataReady()), this, SLOT(accelDataReceived()));
   QObject::connect(this->gyro.get(), SIGNAL(dataReady()), this, SLOT(gyroDataReceived()));
   QObject::connect(this->wheel.get(), SIGNAL(dataReady()), this, SLOT(wheelDataReceived()));
   qDebug() << "Robot initialized";
}

// ---------------------------------------------------------
// -------------------------- SLOTS ------------------------
// ---------------------------------------------------------

/*!
 * \brief Robot::update
 */
void
Robot::update(){
//    // emit this->setAlert(alert);
//    emit this->setLedStrip(this->line->getBools());
//    float ay = this->accel->getY();
//    emit this->setTextAccelX(this->accel->getX());
//    emit this->setTextAccelY(ay);
//    emit this->setTextAccelZ(this->accel->getZ());
//    float gx = this->gyro->getX();
//    float gy = this->gyro->getY();
//    float gz = this->gyro->getZ();
//    emit this->setTextGyroX(gx);
//    emit this->setTextGyroY(gy);
//    emit this->setTextGyroZ(gz);
//    emit this->setTextStatus(this->cmd->getStatus());
//    float speed = this->cmd->getSpeed();
//    emit this->setTextSpeed(speed);
//    QVarLengthArray<float> wheels;
//    wheels.insert(0,this->wheel->getLeft());
//    wheels.insert(1,this->wheel->getRight());
//    emit this->setWheels(wheels, this->D);
//    emit this->setCarAccelY(wheels, ay);
//    emit this->setCarGyroX(gx);
//    emit this->setCarGyroY(gy);
//    emit this->setCarGyroZ(gz);
//    emit this->drawSpeedGraph(speed);
    if(this->line->sendGet())
        qDebug() << "LineSensor is not connected!";
    if(this->accel->sendGet())
        qDebug() << "AccelSensor is not connected!";
    if(this->gyro->sendGet())
        qDebug() << "GyroSensor is not connected!";
    if(this->wheel->sendGet())
        qDebug() << "WheelSensor is not connected!";
}

void
Robot::lineSensDataReceived()
{
    emit this->setLedStrip(this->line->getCurrentValues());
}

void
Robot::accelDataReceived()
{
    emit this->setTextAccelX(this->accel->getX());
    emit this->setTextAccelY(this->accel->getY());
    emit this->setTextAccelZ(this->accel->getZ());

    QVarLengthArray<float> wheels;
    wheels << this->wheel->getLeft() << this->wheel->getRight();

    emit this->setCarAccelY(wheels, this->accel->getY());
}

void
Robot::gyroDataReceived()
{
    emit this->setTextGyroX(this->gyro->getX());
    emit this->setTextGyroY(this->gyro->getY());
    emit this->setTextGyroZ(this->gyro->getZ());

    emit this->setCarGyroX(this->gyro->getX());
    emit this->setCarGyroY(this->gyro->getY());
    emit this->setCarGyroZ(this->gyro->getZ());
}

void
Robot::wheelDataReceived()
{
    QVarLengthArray<float> wheels;
    wheels << this->wheel->getLeft() << this->wheel->getRight();
    emit this->setWheels(wheels, this->D);
}
