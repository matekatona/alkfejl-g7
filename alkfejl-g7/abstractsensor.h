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
    int sendGet();

protected slots:
    virtual void readSensor();

signals:
    void dataReady();

protected:
    int port = 0;
    QTcpSocket socket;
};
#endif // ABSTRACTSENSOR_H
