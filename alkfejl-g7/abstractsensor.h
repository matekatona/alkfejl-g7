#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <QObject>
#include <QTcpSocket>
#include <stdexcept>
#include <memory>


using namespace std;


class AbstractSensor : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSensor(int port = 0);
    void connect();
    void disconnect();

signals:

public slots:
    void connected();
    void disconnected();

private:
    std::unique_ptr<QTcpSocket> socket;
    bool isConnected;

protected:
    int port = 0;
    QString readSensor();
};
#endif // ABSTRACTSENSOR_H
