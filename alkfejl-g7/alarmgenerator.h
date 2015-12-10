//! \file 
//! \brief This file contains the AlarmGenerator class.

#ifndef ALARMGENERATOR_H
#define ALARMGENERATOR_H

#include <QObject>
#include <QDebug>

#define ALARM_GREEN     0
#define ALARM_YELLOW    1
#define ALARM_RED       2

/*!
 * \brief This class handles the alarm indicator LED on the GUI.
 *
 * Based on two parameters, the class sets the color of the LED in the GUI. The
 * colors are as following:\n
 * <pre>
 *      YELLOW -> if not all sockets are connected
 *      RED    -> if all sockets are connected, but no line is found
 *      GREEN  -> if all sockets are connected, and a line is found
 * </pre>
 * Whether a line is found or not is determined by the line sensor values: if all
 * values are the same, then no line is present, otherwise there is one.
 */

class AlarmGenerator : public QObject
{
    Q_OBJECT
public:
    explicit AlarmGenerator();

signals:
    void setAlarm(int state); //!<It is emitted by AlarmGenerator::updateAlarm.

public:
    void setLineState(QVarLengthArray<bool> lineVals);
    void setConnectionState(bool isConnected);
    void updateColor();
    void updateAlarm();
    int getColor();

private:
    bool socketsConnected;
    bool lineFound;
    int color;
};

#endif // ACCELSENSOR_H
