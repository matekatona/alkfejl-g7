#include "abstractsensor.h"
#include <thread>


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
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("GET");  // send get command

        qDebug() << "get sent";

        std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1));

        QByteArray rawData = socket->readLine(100);  // read answer
        rawString.fromStdString(rawData.toStdString());

        qDebug() << "bytes read from port: " << rawData;
        qDebug() << "string read from port: " << rawString;
    }
    else
        rawString = "ERROR";

    return rawString;
}
