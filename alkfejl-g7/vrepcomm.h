#ifndef VREPCOMM_H
#define VREPCOMM_H

#include <QObject>
#include <QTcpSocket>

class VREPComm : public QObject
{
    Q_OBJECT
public:
    explicit VREPComm(QObject *parent = 0);

signals:

public slots:

private:
    QTcpSocket socket;


#endif // VREPCOMM_H
