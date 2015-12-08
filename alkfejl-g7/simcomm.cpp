#include "simcomm.h"

/*!
 * \brief AbstractSensor::AbstractSensor
 * \param port
 */
SimComm::SimComm(int port) :
    cache_timer(new QTimer()),
    socket(new QTcpSocket()),
    port(port)
{
    this->connect();
    this->cache_timer->setSingleShot(true);
    QObject::connect(this->cache_timer.get(), SIGNAL(timeout()), this, SLOT(cache_timeout()));
}

/*!
 * \brief AbstractSensor::cache_timeout
 */
void
SimComm::cache_timeout()
{
    emit this->cache_expired();
}

/*!
 * \brief AbstractSensor::start_cache_timer
 */
void
SimComm::start_cache_timer()
{
    this->cache_timer->start(70);
}

/*!
 * \brief AbstractSensor::connect
 */
void
SimComm::connect()
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
SimComm::disconnect()
{
    this->socket->disconnectFromHost();
}

/*!
 * \brief AbstractSensor::readSensor reads sensor data
 * \return sensor data as unparsed QString on success or empty QString on error
 */
QString
SimComm::read(){
    QString rawString = "";
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->write("GET\n");  // send get command
        // TODO timeout
        QByteArray rawData = socket->readLine(300);  // read answer
        rawString = QString(rawData);
    }

    return rawString;
}

void
SimComm::write(QString command)
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        quint64 res = this->socket->write(command.toLocal8Bit());
        if(res < (quint64)command.length())
        {
            // TODO feedback?
        }
    }
}
