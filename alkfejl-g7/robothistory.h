#ifndef ROBOTHISTORY_H
#define ROBOTHISTORY_H
#include <QList>
#include <QVarLengthArray>

class RobotHistory
{
public:
    RobotHistory(int length=100);
    QVarLengthArray<bool> getLastLine();
    QVarLengthArray<float> getLastAccel();
    QVarLengthArray<float> getLastGyro();
    QVarLengthArray<float> getLastWheels();
    void addNewLineData(QVarLengthArray<bool> data);
    void addNewAccelData(QVarLengthArray<float> data);
    void addNewGyroData(QVarLengthArray<float> data);
    void addNewWheelData(QVarLengthArray<float> data);

private:
    int maxLength;
    bool state[4]={false, false, false, false};
    QList<QVarLengthArray<bool>> historyLine;
    QList<QVarLengthArray<float>> historyAccel;
    QList<QVarLengthArray<float>> historyGyro;
    QList<QVarLengthArray<float>> historyWheel;

    void insertNewLineData(QVarLengthArray<bool> data=QVarLengthArray<bool>({false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}));
    void insertNewAccelData(QVarLengthArray<float> data=QVarLengthArray<float>({NAN, NAN, NAN}));
    void insertNewGyroData(QVarLengthArray<float> data=QVarLengthArray<float>({NAN, NAN, NAN}));
    void insertNewWheelData(QVarLengthArray<float> data=QVarLengthArray<float>({NAN, NAN}));
};

#endif // ROBOTHISTORY_H
