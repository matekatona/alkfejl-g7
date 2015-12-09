#ifndef ALARMGENERATOR_H
#define ALARMGENERATOR_H

#include <QObject>

#define ALARM_GREEN     0
#define ALARM_YELLOW    1
#define ALARM_RED       2

/*!
 * \brief AlarmGenerator::AlarmGenerator this class handles the alarm on the GUI
 *
 * Based on two parameters, the class sets the color o the LED in the GUI. The
 * colors are as following:
 *      YELLOW -> if not all sockets are connected
 *      RED    -> if all sockets are connected, but no line is found
 *      GREEN  -> if all sockets are connected, and a line is found
 * Whether a line is found or not is determined by the linesensor values: if all
 * values are the same, then no line is present, otherwise there is one.
 */

class AlarmGenerator : public QObject
{
    Q_OBJECT
public:
    explicit AlarmGenerator();

signals:
    void setAlarm(int state);

public:
    void setLineState(QVarLengthArray<bool> lineVals);
    void setConnectionState(bool isConnected);
    void updateAlarm();

private:
    bool socketsConnected;
    bool lineFound;
};

#endif // ACCELSENSOR_H
