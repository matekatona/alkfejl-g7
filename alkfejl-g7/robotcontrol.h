#ifndef COMMANDSOCKET_H
#define COMMANDSOCKET_H

#include "simcomm.h"


class RobotControl : public SimComm
{
    Q_OBJECT
public:
    explicit RobotControl();
    void setSpeed(float speed);
    void setStatus(QString status);
    QString getStatus();
    float getSpeed();

private slots:
    void reset_cache();

private:
    std::shared_ptr<QString> pstatus;
    std::shared_ptr<float> pspeed;
    std::weak_ptr<QString> cachestatus;
    std::weak_ptr<float> cachespeed;
};
#endif // COMMANDSOCKET_H
