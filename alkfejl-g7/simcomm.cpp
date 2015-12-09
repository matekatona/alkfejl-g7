#include "simcomm.h"

/*!
 * \brief SimComm::SimComm creates an abstract object to communicate with VREP
 *
 * This object does the actual communication via TCP sockets, and has the timer
 * to signal cache expiration.
 * \param port
 */
SimComm::SimComm(int port) :
    cache_timer(new QTimer()),
    socket(new QTcpSocket()),
    port(port),
    connected(false)
{
    this->cache_timer->setSingleShot(true);
    QObject::connect(this->cache_timer.get(), SIGNAL(timeout()), this, SIGNAL(cache_expired()));
    QObject::connect(this->socket.get(), SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
}

/*!
 * \brief SimComm::socketStateChanged
 * \param socketState
 */
void
SimComm::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    if(socketState==QAbstractSocket::ConnectedState)
        this->connected = true;
    if(socketState==QAbstractSocket::UnconnectedState)
        this->connected = false;

    emit this->stateChanged();
}

/*!
 * \brief SimComm::start_cache_timer starts cache timer
 *
 * The class has a one-shot timer, which can be started by this function. The
 * timer will emit the `cache_timeout()` signal 70 ms after start, and then stop.
 * \sa cache_timeout
 */
void
SimComm::start_cache_timer()
{
    this->cache_timer->start(70);
}

/*!
 * \brief SimComm::connect connects to the port given in constructor
 *
 * This function is explicitly called in constructor, so it does not have to be
 * called after object instantiation. It can be used to reconnect to VREP if the
 * initial connect failed, or if `disconnect()` has been called previously.
 */
void
SimComm::connect()
{
    if(this->connected)
        return;

    this->socket->connectToHost("127.0.0.1", this->port);
    if(!this->socket->waitForConnected(100))
    {
        qDebug() << "could not connect to port " << this->port;
    }
    else
    {
        qDebug() << "connected to port " << this->port;
    }
}

/*!
 * \brief SimComm::disconnect disconnects from port
 *
 * The socket is implicitly closed before destroying instances of this object, so
 * there is no need to explicitly call this function. It can be used to reconnect
 * if there were errors with the initial connect, or if VREP has been restarted
 * during program execution.
 */
void
SimComm::disconnect()
{
    this->socket->disconnectFromHost();
}

/*!
 * \brief SimComm::isConnected
 * \return
 */
bool
SimComm::isConnected()
{
    return this->connected;
}

/*!
 * \brief SimComm::read reads robot data
 *
 * This function is handling communication with VREP. It sends the "GET" string
 * to the instance's port, so the user does not have to send it using `write()`,
 * and reads the answer until the next newline. It does not parse the received string.
 * \return unparsed robot data
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

/*!
 * \brief SimComm::write writes command to socket
 *
 * This function is handling communication with VREP. It sends the given command
 * to the instance's port. No modification is made on the command, so it has to
 * be a valid one. Nothing is returned, since the robot only replies to the
 * "GET" command. To check whether the command has been executed by the robot,
 * the user can call getter functions later, and check the returned values.
 * \param command the command string to send.
 */
void
SimComm::write(QString command)
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        quint64 res = this->socket->write(command.toLocal8Bit());
        if(res < (quint64)command.length())
        {
            // could not send the command
            // TODO feedback?
        }
    }
}
