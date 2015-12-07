#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <QObject>
#include <QtWidgets>    // QTimer
#include <QTcpSocket>   // QTcpSocket
#include <memory>


using namespace std;


class AbstractSensor : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSensor(int port = 0);
    void connect();
    void disconnect();
    QString readSensor();

signals:
    void cache_expired();

protected slots:
    void cache_timeout();

protected:
    void start_cache_timer();

private:
    std::unique_ptr<QTimer> cache_timer;
    std::unique_ptr<QTcpSocket> socket;
    int port = 0;
};
#endif // ABSTRACTSENSOR_H
