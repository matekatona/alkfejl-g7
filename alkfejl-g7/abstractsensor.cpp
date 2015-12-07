#include "abstractsensor.h"
#include <thread>


/*!
 * \brief AbstractSensor::AbstractSensor
 * \param port
 */
AbstractSensor::AbstractSensor(int port) :
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
AbstractSensor::cache_timeout()
{
    emit this->cache_expired();
}

/*!
 * \brief AbstractSensor::start_cache_timer
 */
void
AbstractSensor::start_cache_timer()
{
    this->cache_timer->start(70);
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
