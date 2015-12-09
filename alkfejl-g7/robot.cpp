#include "robot.h"

/*!
 * \brief Robot::Robot creates a robot object, trough which the GUI can
 *                     communicate with all VREP sockets in an organized way
 *
 * The Robot class has one instance of every sensor, and one control socket.
 * This is the interface between the GUI and the backend, and as such does not
 * provide any special functionality, only translates GUI requests to commands
 * for VREP, and sensor data to GUI data.
 * \warning initialization order of objects inherited from SimComm is crucial!
 *          DO NOT change it!
 * \see RobotControl
 * \see LineSensor
 * \see AccelSensor
 * \see GyroSensor
 * \see WheelSensor
 */
Robot::Robot()
    : control(new RobotControl()),
      line(new LineSensor()),       // VREP will freeze with any other order
      accel(new AccelSensor()),     // but we have no time to fix this in VREP
      gyro(new GyroSensor()),       // and noone will notice anyway
      wheel(new WheelSensor()),
      update_timer(new QTimer()),
      alarmgen(new AlarmGenerator())
{
    this->update_timer->setSingleShot(false);
    this->update_timer->setInterval(100);
    this->connectedSockets = 0;

    QObject::connect(this->update_timer.get(), SIGNAL(timeout()), this, SLOT(update()));
    QObject::connect(this->alarmgen.get(), SIGNAL(setAlarm(int)), this, SIGNAL(setAlert(int)));
    QObject::connect(this->control.get(), SIGNAL(stateChanged()), this, SLOT(socketStateChanged()));
    QObject::connect(this->line.get(), SIGNAL(stateChanged()), this, SLOT(socketStateChanged()));
    QObject::connect(this->accel.get(), SIGNAL(stateChanged()), this, SLOT(socketStateChanged()));
    QObject::connect(this->gyro.get(), SIGNAL(stateChanged()), this, SLOT(socketStateChanged()));
    QObject::connect(this->wheel.get(), SIGNAL(stateChanged()), this, SLOT(socketStateChanged()));
}

/*!
 * \brief Robot::connect connects all sockets to VREP
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
 * \brief Robot::disconnect disconnects all sockets from VREP
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
 * \brief Robot::socketStateChanged
 * \param socketState
 */
void
Robot::socketStateChanged()
{
    bool s0 = this->control->isConnected();
    bool s1 = this->accel->isConnected();
    bool s2 = this->gyro->isConnected();
    bool s3 = this->line->isConnected();
    bool s4 = this->wheel->isConnected();

    bool robotConnected = s0 & s1 & s2 & s3 & s4;

    if(robotConnected)
    {
        this->update_timer->start();
        emit this->connected();
    }
    else
    {
        this->update_timer->stop();
        emit this->disconnected();
    }

    this->alarmgen->setConnectionState(robotConnected);
    this->alarmgen->setLineState(this->line->getValues());
    this->alarmgen->updateAlarm();
}

void
Robot::selfTest()
{
    switch(this->testState){
    case 0:
        this->test_timer =  std::make_unique<QTimer>();
        QObject::connect(this->test_timer.get(), SIGNAL(timeout()), this, SLOT(selfTest()));
        this->control->setStatus(QString("Run"));
        this->testState++;
        this->test_timer->setInterval(5000);
        this->test_timer->start();
        break;
    case 1:
        this->control->setSpeed(0.8);
        this->testState++;
        this->test_timer->setInterval(2000);
        this->test_timer->start();
        break;
    case 2:
        this->control->setSpeed(0);
        this->testState++;
        this->test_timer->setInterval(8000);
        this->test_timer->start();
        break;
    case 3:
        this->control->setSpeed(0.5);
        this->control->setStatus(QString("Run"));
        this->testState++;
        this->test_timer->setInterval(4000);
        this->test_timer->start();
        break;
    case 4:
        this->control->setStatus(QString("Stop"));
        this->testState++;
        this->test_timer->setInterval(1000);
        this->test_timer->start();
        break;
    default:
        QObject::disconnect(this->test_timer.get(), SIGNAL(timeout()), this, SLOT(selfTest()));
        this->test_timer.reset();
        this->testState=0;
    }
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
 * from VREP
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
