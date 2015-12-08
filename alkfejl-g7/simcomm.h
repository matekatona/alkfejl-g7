#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

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


class SimComm : public QObject
{
    Q_OBJECT
public:
    explicit SimComm(int port = 80);
    void connect();
    void disconnect();

signals:
    void cache_expired();

protected slots:
    void cache_timeout();

protected:
    void start_cache_timer();
    QString read();
    void write(QString command);

private:
    std::unique_ptr<QTimer> cache_timer;
    std::unique_ptr<QTcpSocket> socket;
    const int port;
};
#endif // ABSTRACTSENSOR_H
