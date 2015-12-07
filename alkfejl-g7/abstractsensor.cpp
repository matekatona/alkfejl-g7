#include "abstractsensor.h"
#include <thread>


/*!
 * \brief AbstractSensor::AbstractSensor
 * \param port
 */
AbstractSensor::AbstractSensor(int port) :
    socket(new QTcpSocket()),
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
        this->socket->write("GET\n");  // send get command

         // std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1));

        QByteArray rawData = socket->readLine(300);  // read answer
        // QByteArray rawData = socket->readAll();
        QString temp(rawData);
        rawString = temp;
    }
    else
        rawString = "ERROR";

    return rawString;
}
