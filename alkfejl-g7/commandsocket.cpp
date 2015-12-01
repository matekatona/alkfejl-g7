#include "commandsocket.h"

/*!
 * \brief CommandSocket::CommandSocket
 * \param port
 */
CommandSocket::CommandSocket(int port)
    : socket(new QTcpSocket())
{
    // socket = std::make_unique<QTcpSocket>(new QTcpSocket());
    this->port = port;
    this->connect();
}

/*!
 * \brief CommandSocket::connect
 */
void
CommandSocket::connect()
{
    this->socket->connectToHost("127.0.0.1", this->port);
    if(!this->socket->waitForConnected(1000))
    {
        throw std::runtime_error("Could not connect to socket!");
    }
}

/*!
 * \brief CommandSocket::disconnect
 */
void
CommandSocket::disconnect()
{
    this->socket.release();
}

/*!
 * \brief CommandSocket::getStatus
 * \return
 */
QString CommandSocket::getStatus()
{
    QString status;
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("getStatus");  // send get command

        QByteArray rawData = socket->readLine(100);  // read answer
        status.fromStdString(rawData.toStdString());
    }
    else
        status = "UNKNOWN";

    return status;
}

/*!
 * \brief CommandSocket::run
 */
void
CommandSocket::run()
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("setStatus:Run");  // send run command
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
        this->socket->write("setStatus:Stop");  // send stop command
    }
}

/*!
 * \brief CommandSocket::getSpeed
 * \return
 */
float
CommandSocket::getSpeed()
{
    QString rawString;
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("getSpeed");  // send get command

        QByteArray rawData = socket->readLine(100);  // read answer
        rawString.fromStdString(rawData.toStdString());
    }
    else
        return 0.0f / 0.0f;

    return rawString.toFloat();
}

/*!
 * \brief CommandSocket::setSpeed
 * \param newspeed
 */
void
CommandSocket::setSpeed(float newspeed)
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        // TODO real solution
        char command[20];
        sprintf(command, "setSpeed:%.1f", newspeed);
        this->socket->write(command);  // send setspeed command
    }
}

