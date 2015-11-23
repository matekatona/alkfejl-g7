#ifndef VREPCOMM_H
#define VREPCOMM_H

#include <QObject>
#include <QTcpSocket>

class VREPComm : public QObject
{
    Q_OBJECT
public:
    explicit VREPComm(QObject *parent = 0);
    int getPort();
    void connect(int port);

signals:

public slots:

private:
    QTcpSocket socket;
    int port = 0;
};
#endif // VREPCOMM_H