//! \file 
//! \brief _Facade design pattern_. This file contains the RobotControl class.

#ifndef COMMANDSOCKET_H
#define COMMANDSOCKET_H

#include "simcomm.h"

/*!
 * \brief This class is for setting and getting global robot parameters.
 *
 * The class uses cache to store values to minimize communication with
 * the simulator. Every read value is cached, and expires after 70 ms. Repeated
 * reads within this 70 ms will return the same values.
 */
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
