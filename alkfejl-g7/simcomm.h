//! \file 
//! \brief _Client in the Server-Client design pattern._ This file contains the SimComm class.

#ifndef SIMCOMM_H
#define SIMCOMM_H

#include <QObject>
#include <QtWidgets>    // QTimer
#include <QTcpSocket>   // QTcpSocket
#include <memory>

#define PORT_NUM_CONTROL    25455
#define PORT_NUM_ACCEl      24931
#define PORT_NUM_GYRO       26489
#define PORT_NUM_LINE       27753
#define PORT_NUM_WHEEL      30568

using namespace std;


/*! 
 * \brief This class is the base of all classes that communicate with V-REP. 
 *
 * It handles the control socket (TCP) and the communication protocol.
 */
class SimComm : public QObject
{
    Q_OBJECT
public:
    explicit SimComm(int port = 80);
    void connect();
    void disconnect();
    bool isConnected();

signals:
    void cache_expired();  //!< This signal is emitted by `SimComm::cache_timer`.
    void stateChanged();   //!< This signal is emitted by SimComm::socketStateChanged.

protected slots:
    void socketStateChanged(QAbstractSocket::SocketState socketState);

protected:
    void start_cache_timer();
    QString read();
    void write(QString command);

private:
    std::unique_ptr<QTimer> cache_timer;
    std::unique_ptr<QTcpSocket> socket;
    const int port;
    bool connected;
};
#endif // SIMCOMM_H
