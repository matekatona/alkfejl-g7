#ifndef COMMANDSOCKET_H
#define COMMANDSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <stdexcept>
#include <memory>

using namespace std;


class CommandSocket : public QObject
{
    Q_OBJECT
public:
    explicit CommandSocket(int port = 0);
    void connect();
    void disconnect();
    void run();
    void stop();
    void setSpeed(float speed);
    void setStatus(QString status);
    QString getStatus();
    float getSpeed();

private:
    std::unique_ptr<QTcpSocket> socket;

    std::shared_ptr<QString> pstatus;
    std::shared_ptr<float> pspeed;
    std::weak_ptr<QString> cachestatus;
    std::weak_ptr<float> cachespeed;

    int port = 0;
};
#endif // COMMANDSOCKET_H
