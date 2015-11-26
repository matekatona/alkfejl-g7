#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <QObject>
#include <QTcpSocket>
#include <stdexcept>

class AbstractSensor : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSensor(QObject *parent = 0);
    int getPort();
    void connect(int port);
    QString recvUntilNewline();
    QString recvAll();
    void send(QString data);
    bool isReadyRead();

signals:
    void readyRead();

public slots:

private:
    QTcpSocket *socket;
    QString allDataReceived;

protected:
    int port = 0;
    QString readSensor();
};
#endif // ABSTRACTSENSOR_H
