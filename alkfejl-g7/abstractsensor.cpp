#include "abstractsensor.h"



AbstractSensor::AbstractSensor(QObject *parent, int port) : QObject(parent)
{
    socket = new QTcpSocket(this);
    this->port = port;
    this->connect();
}

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
