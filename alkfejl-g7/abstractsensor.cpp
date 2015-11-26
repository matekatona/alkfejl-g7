#include "abstractsensor.h"

AbstractSensor::AbstractSensor(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    QObject::connect(socket, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
}

bool
AbstractSensor::isReadyRead()
{
    return socket->isReadable();
}

void
AbstractSensor::connect(int port)
{
    socket->connectToHost("127.0.0.1", this->port=port);
    if(!socket->waitForConnected(100)) //should replace this with signals
    {
        throw std::runtime_error("Could not connect to socket!");
    }

}

void
AbstractSensor::send(QString data)
{
    socket->write(data.toStdString().c_str(), data.length());
}

//untested
//reads one line (ending with '\n' from the socket)
// see QIODevice::readLine()
QString
AbstractSensor::recvUntilNewline()
{
    if(!allDataReceived.contains("\n"))
        allDataReceived+=socket->readAll();
    if(allDataReceived.contains("\n"))
    {
        int chopUntil = allDataReceived.indexOf("\n");
        QString toReturn = allDataReceived.left(chopUntil);
        allDataReceived=allDataReceived.mid(chopUntil);
        return allDataReceived;
    }
    else return "";
}

QString
AbstractSensor::recvAll()
{
    QString toReturn = allDataReceived + socket->readAll();
    allDataReceived = "";
    return toReturn;
}

// -----------------------------------------------------------------------

/*!
 * \brief AbstractSensor::readSensor reads sensor data
 * \return sensor data as unparsed string on success or "ERROR" on error
 */
QString
AbstractSensor::readSensor(){
    QString rawString;
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write("GET");  // send get command

        QByteArray rawData = socket->readLine(100);  // read answer
        rawString.fromStdString(rawData.toStdString());
    }
    else
        rawString = "ERROR";

    return rawString;
}

