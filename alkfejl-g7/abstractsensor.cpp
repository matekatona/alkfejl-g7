#include "abstractsensor.h"

/*!
 * \brief AbstractSensor::AbstractSensor
 * \param port
 */
AbstractSensor::AbstractSensor(int port) :
    socket(new QTcpSocket())
{
    // socket = std::make_unique<QTcpSocket>(new QTcpSocket());
    this->port = port;
    this->connect();
}

/*!
 * \brief AbstractSensor::connect
 */
void
AbstractSensor::connect()
{
    this->socket->connectToHost("127.0.0.1", this->port);
    if(!this->socket->waitForConnected(1000))
    {
        throw std::runtime_error("Could not connect to socket!");
    }
}

/*!
 * \brief AbstractSensor::disconnect
 */
void
AbstractSensor::disconnect()
{
    this->socket.release();
}

/*!
 * \brief AbstractSensor::readSensor reads sensor data
 * \return sensor data as unparsed string on success or "ERROR" on error
 */
QString
AbstractSensor::readSensor(){
    QString rawString;
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("GET");  // send get command

        QByteArray rawData = socket->readLine(100);  // read answer
        rawString.fromStdString(rawData.toStdString());
    }
    else
        rawString = "ERROR";

    return rawString;
}
