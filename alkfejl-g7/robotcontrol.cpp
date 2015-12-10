#include "robotcontrol.h"


/*!
 * \brief RobotControl::RobotControl creates control object, that is connected to
 *                                   the command port of V-REP
 */
RobotControl::RobotControl() :
    SimComm(PORT_NUM_CONTROL)  // call superclass constructor with correct port number
{
    this->cachestatus = this->pstatus;
    this->cachespeed = this->pspeed;
    this->pstatus.reset();
    this->pspeed.reset();

    QObject::connect(this, SIGNAL(cache_expired()), this, SLOT(reset_cache()));
}

/*!
 * \brief RobotControl::clear_cache delete cached values
 *
 * The next read will result in reading new values from V-REP
 * \see SimComm::cache_expired
 */
void
RobotControl::reset_cache()
{
    this->pspeed.reset();
    this->pstatus.reset();
}

/*!
 * \brief RobotControl::getStatus get robot status
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read
 * \return current status of robot, either "Run" or "Stop"
 */
QString
RobotControl::getStatus()
{
    QString status = "";
    std::shared_ptr<QString> cst = this->cachestatus.lock();
    if(cst)
    {
        // use cached value
        status = *cst;
    }
    else
    {
        // read new values
        QString raw = this->read();
        qDebug() << "status " << raw;
        if(raw.length() < 3)
            return status;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 2)
            return status;
        status = values[0];
        float speed = values[1].toFloat();
        // cache values
        this->pspeed = std::make_shared<float>(speed);
        this->cachespeed = this->pspeed;
        this->pstatus = std::make_shared<QString>(status);
        this->cachestatus = this->pstatus;
        this->start_cache_timer();  // will reset cache 70ms later
    }

    return status;
}

/*!
 * \brief RobotControl::getSpeed get robot speed
 *
 * If a valid value is found in cache, tha cached value is returned. Otherwise
 * new values are read from V-REP, put into the cache, and returned.
 * \see SimComm::read
 * \return current speed of robot
 */
float
RobotControl::getSpeed()
{
    float speed = 0.0/0.0;
    std::shared_ptr<float> csp = this->cachespeed.lock();
    if(csp)
    {
        // use cached value
        speed = *csp;
    }
    else
    {
        // read new values
        QString raw = this->read();
        qDebug() << "speed " << raw;
        if(raw.length() < 3)
            return speed;
        QStringList values = raw.split(QRegExp("\\s"));
        if(values.size() < 2)
            return speed;
        QString status = values[0];
        speed = values[1].toFloat();
        // cache values
        this->pspeed = std::make_shared<float>(speed);
        this->cachespeed = this->pspeed;
        this->pstatus = std::make_shared<QString>(status);
        this->cachestatus = this->pstatus;
        this->start_cache_timer();  // will reset cache 70ms later
    }

    return speed;
}

/*!
 * \brief RobotControl::setStatus sets the status of the robot
 *
 * This command sends the given status to the robot. If it is a valid status
 * (i.e. "Run" or "Stop") the robot will change it's state accordingly. Other
 * status words are ignored.
 * \see SimComm::write
 * \param status the new status, either "Run" or "Stop"
 */
void
RobotControl::setStatus(QString status)
{
    QString command = "setStatus:" + status + "\n";
    this->write(command);
}

/*!
 * \brief RobotControl::setSpeed sets the speed of the robot
 *
 * This command sends the given speed to the robot. If it is a valid speed
 * (i.e. positive) the robot will change it's speed accordingly. If the given
 * speed is 0, the robot will stop, and change it's status to "Stop".
 * \see SimComm::write
 * \warning high speeds may cause the robot to lose line tracking, and fall off
 * the edge of the world.
 * \param speed the new speed
 */
void
RobotControl::setSpeed(float speed)
{
    QString command = "setSpeed:" + QString::number(speed) + "\n";
    this->write(command);
}
