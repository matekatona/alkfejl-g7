#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QObject>
#include "qmlhandlercppside.h"

class GuiHandler : public QObject
{
    Q_OBJECT

public:
    explicit GuiHandler( \
            QMLHandlerCppSide *alertLamp, \
            QMLHandlerCppSide *lineSens, \
            QMLHandlerCppSide *textAccelX, \
            QMLHandlerCppSide *textAccelY, \
            QMLHandlerCppSide *textAccelZ, \
            QMLHandlerCppSide *textGyroX, \
            QMLHandlerCppSide *textGyroY, \
            QMLHandlerCppSide *textGyroZ, \
            QMLHandlerCppSide *textCurStatus, \
            QMLHandlerCppSide *textCurSpeed, \
            QMLHandlerCppSide *wheels, \
            QMLHandlerCppSide *carAccelY, \
            QMLHandlerCppSide *carGyroX, \
            QMLHandlerCppSide *carGyroY, \
            QMLHandlerCppSide *carGyroZ, \
            QMLHandlerCppSide *speedGraph, \
            QMLHandlerCppSide *buttonSendStatus, \
            QMLHandlerCppSide *buttonSendSpeed, \
            QMLHandlerCppSide *buttonCarSelfTest);

private:
    QMLHandlerCppSide *alertLamp;
    QMLHandlerCppSide *lineSens;
    QMLHandlerCppSide *textAccelX;
    QMLHandlerCppSide *textAccelY;
    QMLHandlerCppSide *textAccelZ;
    QMLHandlerCppSide *textGyroX;
    QMLHandlerCppSide *textGyroY;
    QMLHandlerCppSide *textGyroZ;
    QMLHandlerCppSide *textCurStatus;
    QMLHandlerCppSide *textCurSpeed;
    QMLHandlerCppSide *wheels;
    QMLHandlerCppSide *carAccelY;
    QMLHandlerCppSide *carGyroX;
    QMLHandlerCppSide *carGyroY;
    QMLHandlerCppSide *carGyroZ;
    QMLHandlerCppSide *speedGraph;
    QMLHandlerCppSide *buttonSendStatus;
    QMLHandlerCppSide *buttonSendSpeed;
    QMLHandlerCppSide *buttonCarSelfTest;

signals:
    void buttonSendStatusClicked(QString status);
    void buttonSendSpeedClicked(QString speed);
    void buttonCarSelfTestClicked();

public slots:
    void qmlbuttonSendStatusClicked();
    void qmlbuttonSendSpeedClicked();
    void qmlbuttonCarSelfTestClicked();

    void setAlert(bool alert);
    void setLedStrip(QVarLengthArray<bool> leds);
    void setTextAccelX(float accelX);
    void setTextAccelY(float accelY);
    void setTextAccelZ(float accelZ);
    void setTextGyroX(float gyroX);
    void setTextGyroY(float gyroY);
    void setTextGyroZ(float gyroZ);
    void setTextStatus(QString status);
    void setTextSpeed(float speed);
    void setWheels(QVarLengthArray<float> wheels);
    void setCarAccelY(float accelY);
    void setCarGyroX(float gyroX);
    void setCarGyroY(float gyroY);
    void setCarGyroZ(float gyroZ);
    void drawSpeedGraph(float speed);
};

#endif // GUIHANDLER_H
