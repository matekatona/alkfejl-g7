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
    QString readSensor();

protected:
    std::unique_ptr<QTcpSocket> socket;
    int port = 0;
};
#endif // ABSTRACTSENSOR_H
