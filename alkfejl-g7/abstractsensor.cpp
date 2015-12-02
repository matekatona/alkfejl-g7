#include "abstractsensor.h"

/*!
 * \brief AbstractSensor::AbstractSensor
 * \param port
 */
AbstractSensor::AbstractSensor(int port) :
    port(port)
{
    this->connect();
}

/*!
 * \brief AbstractSensor::connect
 */
void
AbstractSensor::connect()
{
    QObject::connect(&this->socket, SIGNAL(readyRead()), this, SLOT(readSensor()));
    this->socket.connectToHost("127.0.0.1", this->port, QIODevice::ReadWrite);
//     handling this with signals (or something likw this)
//     if(!this->socket->waitForConnected(1000))
//         throw std::runtime_error("Could not connect to socket!");
}

/*!
 * \brief AbstractSensor::disconnect
 */
void
AbstractSensor::disconnect()
{
    this->socket.disconnectFromHost();
}

int
AbstractSensor::sendGet()
{
    if(this->socket.state() == QAbstractSocket::ConnectedState)
    {
        this->socket.write("GET\n");  // send get command
        return 0;
    }
    else
        return 1;
}

void
AbstractSensor::readSensor()
{

}
