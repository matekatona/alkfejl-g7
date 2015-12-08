#include "robotcontrol.h"

/*!
 * \brief CommandSocket::CommandSocket
 * \param port
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
 * \brief CommandSocket::reset_cache
 */
void
RobotControl::reset_cache()
{
    this->pspeed.reset();
    this->pstatus.reset();
}

/*!
 * \brief CommandSocket::getStatus
 * \return
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
        if(raw.length() < 5)
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
 * \brief CommandSocket::getSpeed
 * \return
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
        if(raw.length() < 5)
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
 * \brief CommandSocket::setStatus
 * \param status
 */
void
RobotControl::setStatus(QString status)
{
    QString command = "setStatus:" + status + "\n";
    this->write(command);
}

/*!
 * \brief CommandSocket::setSpeed
 * \param speed
 */
void
RobotControl::setSpeed(float speed)
{
    QString command = "setSpeed:" + QString::number(speed) + "\n";
    this->write(command);
}

