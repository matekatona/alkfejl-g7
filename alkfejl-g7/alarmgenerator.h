#ifndef ALARMGENERATOR_H
#define ALARMGENERATOR_H

#include <QObject>
#include <QDebug>

#define ALARM_GREEN     0
#define ALARM_YELLOW    1
#define ALARM_RED       2

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
    void updateColor();
    int getColor();

private:
    bool socketsConnected;
    bool lineFound;
    int color;
};

#endif // ACCELSENSOR_H
