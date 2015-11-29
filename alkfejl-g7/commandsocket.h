#ifndef COMMANDSOCKET_H
#define COMMANDSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <stdexcept>
#include <memory>

using namespace std;


typedef enum{
    STATUS_RUN,
    STATUS_STOP,
    STATUS_UNKNOWN
}robot_status_t;

class CommandSocket : public QObject
{
    Q_OBJECT
public:
    explicit CommandSocket(int port = 0);
    void connect();
    void disconnect();
    int getStatus();
    void run();
    void stop();
    float getSpeed();
    void setSpeed(float newspeed);

signals:

public slots:

private:
    std::unique_ptr<QTcpSocket> socket;
    int port = 0;
};
#endif // COMMANDSOCKET_H
