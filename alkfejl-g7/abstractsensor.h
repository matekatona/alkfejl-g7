#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <QObject>
#include <QTcpSocket>
#include <stdexcept>

class AbstractSensor : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSensor(QObject *parent = 0, int port = 0);

signals:

public slots:

private:
    QTcpSocket *socket;

protected:
    int port = 0;
    void connect();
    QString readSensor();
};
#endif // ABSTRACTSENSOR_H
