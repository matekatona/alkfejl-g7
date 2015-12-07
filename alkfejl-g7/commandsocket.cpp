#include "commandsocket.h"

/*!
 * \brief CommandSocket::CommandSocket
 * \param port
 */
CommandSocket::CommandSocket(int port) :
    socket(new QTcpSocket())
{
    this->port = port;

    this->cachestatus = this->pstatus;
    this->cachespeed = this->pspeed;
    this->pstatus.reset();
    this->pspeed.reset();

    this->connect();
}

/*!
 * \brief CommandSocket::connect
 */
void
CommandSocket::connect()
{
    this->socket->connectToHost("127.0.0.1", this->port, QIODevice::ReadWrite);
    if(!this->socket->waitForConnected(1000))
    {
        qDebug() << "could not connect to port " << this->port;
    }
    else
    {
        qDebug() << "connected to port " << this->port;
    }
}

/*!
 * \brief CommandSocket::disconnect
 */
void
CommandSocket::disconnect()
{
    this->socket->disconnectFromHost();
}

/*!
 * \brief CommandSocket::getStatus
 * \return
 */
QString
CommandSocket::getStatus()
{
    QString status;
    std::shared_ptr<QString> cst = this->cachestatus.lock();
    if(cst)
    {
        // use cached value
        status = *cst;
        this->pstatus.reset();
    }
    else
    {
        // read new values
        if(this->socket->state() == QAbstractSocket::ConnectedState)
        {
            this->socket->write("getStatus\n");  // send get command
        }
        else
        {
            return "";
        }

        QByteArray rawData = socket->readLine(300);  // read answer
        QString rawString(rawData);
        QStringList rawValues = rawString.split(" ");
        if(rawValues.size() < 2)
        {
            return "";
        }
        status = rawValues[0];
        float speed = rawValues[1].toFloat();
        // cache speed
        this->pspeed = std::make_shared<float>(speed);
        this->cachespeed = this->pspeed;
    }

    return status;
}

/*!
 * \brief CommandSocket::getSpeed
 * \return
 */
float
CommandSocket::getSpeed()
{
    float speed;
    std::shared_ptr<float> csp = this->cachespeed.lock();
    if(csp)
    {
        // use cached value
        speed = *csp;
        this->pspeed.reset();
    }
    else
    {
        // read new values
        if(this->socket->state() == QAbstractSocket::ConnectedState)
        {
            this->socket->write("getStatus\n");  // send get command
        }
        else
        {
            return 0.0;
        }
        QByteArray rawData = socket->readLine(300);  // read answer
        QString rawString(rawData);
        QStringList rawValues = rawString.split(" ");
        if(rawValues.size() < 2)
        {
            return 0.0;
        }
        QString status = rawValues[0];
        speed = rawValues[1].toFloat();
        // cache status
        this->pstatus = std::make_shared<QString>(status);
        this->cachestatus = this->pstatus;
    }

    return speed;
}

/*!
 * \brief CommandSocket::run
 */
void
CommandSocket::run()
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("setStatus:Run\n");  // send run command
    }
}

/*!
 * \brief CommandSocket::stop
 */
void
CommandSocket::stop()
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("setStatus:Stop\n");  // send stop command
    }
}

/*!
 * \brief CommandSocket::setStatus
 * \param newstatus
 */
void
CommandSocket::setStatus(QString status)
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        // TODO real solution
        QString command;
        command = "setStatus:" + status + "\n";
        this->socket->write(command.toLocal8Bit());  // send setstatus command
    }
}

/*!
 * \brief CommandSocket::setSpeed
 * \param newspeed
 */
void
CommandSocket::setSpeed(float speed)
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        // TODO real solution
        QString command;
        command = "setSpeed:" + QString::number(speed) + "\n";
        this->socket->write(command.toLocal8Bit());  // send setspeed command
    }
}

