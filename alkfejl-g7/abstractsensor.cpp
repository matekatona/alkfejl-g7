#include "abstractsensor.h"

/*!
 * \brief AbstractSensor::AbstractSensor
 * \param port
 */
AbstractSensor::AbstractSensor(int port) :
    socket(new QTcpSocket()),
    isConnected(false),
    port(port)
{
    // TODO build error
    // QObject::connect(this->socket, &QAbstractSocket::connected, this, &AbstractSensor::connected);
    // QObject::connect(this->socket, &QAbstractSocket::disconnected, this, &AbstractSensor::disconnected);
    this->connect();
}

/*!
 * \brief AbstractSensor::connected
 */
void
AbstractSensor::connected()
{
    this->isConnected = true;
}

/*!
 * \brief AbstractSensor::disconnected
 */
void
AbstractSensor::disconnected()
{
    this->isConnected = false;
}

/*!
 * \brief AbstractSensor::connect
 */
void
AbstractSensor::connect()
{
    this->socket->connectToHost("127.0.0.1", this->port);
    // handling this with signals (or something likw this)
    // if(!this->socket->waitForConnected(1000))
        // throw std::runtime_error("Could not connect to socket!");
}

/*!
 * \brief AbstractSensor::disconnect
 */
void
AbstractSensor::disconnect()
{
    this->socket.release();
    // this->isConnected = false;  // will be set in disconnected() slot
}

/*!
 * \brief AbstractSensor::readSensor reads sensor data
 * \return sensor data as unparsed string on success or "ERROR" on error
 */
QString
AbstractSensor::readSensor(){
    QString rawString;
    if(this->isConnected && this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("GET");  // send get command

        QByteArray rawData = socket->readLine(100);  // read answer
        rawString.fromStdString(rawData.toStdString());
    }
    else
        rawString = "ERROR";

    return rawString;
}
