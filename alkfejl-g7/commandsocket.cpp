#include "commandsocket.h"

/*!
 * \brief CommandSocket::CommandSocket
 * \param port
 */
CommandSocket::CommandSocket(int port)
{
    // socket = std::make_unique<QTcpSocket>(new QTcpSocket());
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
    QObject::connect(&this->socket, SIGNAL(readyRead()), this, SLOT(readStatus()));
    this->socket.connectToHost("127.0.0.1", this->port, QIODevice::ReadWrite);
}

/*!
 * \brief CommandSocket::disconnect
 */
void
CommandSocket::disconnect()
{
    this->socket.disconnectFromHost();
}

/*!
 * \brief CommandSocket::getStatus
 * \return
 */
int CommandSocket::getStatus()
{
    if(this->socket.state() == QAbstractSocket::ConnectedState)
    {
        this->socket.write("getStatus\n");  // send get command
        return 0;
    }
    else
        return 1;
}

/*!
 * \brief CommandSocket::run
 */
void
CommandSocket::run()
{
    if(this->socket.state() == QAbstractSocket::ConnectedState)
    {
        this->socket.write("setStatus:Run");  // send run command
    }
}

/*!
 * \brief CommandSocket::stop
 */
void
CommandSocket::stop()
{
    if(this->socket.state() == QAbstractSocket::ConnectedState)
    {
        this->socket.write("setStatus:Stop");  // send stop command
    }
}

QString
CommandSocket::getCurrentStatus()
{
    return *this->pstatus.get();
}

float
CommandSocket::getCurrentSpeed()
{
    return *this->pspeed.get();
}

void
CommandSocket::readStatus()
{
    while(!this->socket.canReadLine()){}

    QByteArray rawData = this->socket.readAll();
    QString rawString(rawData);

    QStringList rawValues = rawString.split(" ");
    QString status;
    float speed;
    status=rawValues[0];
    speed=rawValues[1].toFloat();

    this->pstatus = std::make_shared<QString>(status);
    this->pspeed = std::make_shared<float>(speed);

    emit this->dataReady();
}

void
CommandSocket::setStatus(QString newstatus)
{
    if(this->socket.state() == QAbstractSocket::ConnectedState)
    {
        // TODO real solution
        QString command;
        command="setStatus:" + newstatus + "\n";
        this->socket.write(command.toUtf8());  // send setstatus command
    }
}

/*!
 * \brief CommandSocket::setSpeed
 * \param newspeed
 */
void
CommandSocket::setSpeed(float newspeed)
{
    if(this->socket.state() == QAbstractSocket::ConnectedState)
    {
        // TODO real solution
        QString command;
        command="setSpeed:" + QString::number(newspeed) + "\n";
        this->socket.write(command.toUtf8());  // send setspeed command
    }
}

