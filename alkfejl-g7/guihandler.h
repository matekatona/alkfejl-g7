#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QObject>
#include <QVarLengthArray>
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
            QMLHandlerCppSide *comboSetStatus, \
            QMLHandlerCppSide *textCurSpeed, \
            QMLHandlerCppSide *editSetSpeed, \
            QMLHandlerCppSide *wheels, \
            QMLHandlerCppSide *carAccelY, \
            QMLHandlerCppSide *carGyroX, \
            QMLHandlerCppSide *carGyroY, \
            QMLHandlerCppSide *carGyroZ, \
            QMLHandlerCppSide *speedGraph, \
            QMLHandlerCppSide *buttonConDiscon, \
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
    QMLHandlerCppSide *comboSetStatus;
    QMLHandlerCppSide *textCurSpeed;
    QMLHandlerCppSide *editSetSpeed;
    QMLHandlerCppSide *wheels;
    QMLHandlerCppSide *carAccelY;
    QMLHandlerCppSide *carGyroX;
    QMLHandlerCppSide *carGyroY;
    QMLHandlerCppSide *carGyroZ;
    QMLHandlerCppSide *speedGraph;
    QMLHandlerCppSide *buttonConDiscon;
    QMLHandlerCppSide *buttonSendStatus;
    QMLHandlerCppSide *buttonSendSpeed;
    QMLHandlerCppSide *buttonCarSelfTest;

signals:
    void buttonConClicked();
    void buttonDisClicked();
    void buttonSendStatusClicked(QString status);
    void buttonSendSpeedClicked(float speed);
    void buttonCarSelfTestClicked();

public slots:
    void qmlbuttonConDisconClicked();
    void qmlbuttonSendStatusClicked();
    void qmlbuttonSendSpeedClicked();
    void qmlbuttonCarSelfTestClicked();

    void setAlert(int color);
    void setLedStrip(QVarLengthArray<bool> leds);
    void setTextAccelX(float accelX);
    void setTextAccelY(float accelY);
    void setTextAccelZ(float accelZ);
    void setTextGyroX(float gyroX);
    void setTextGyroY(float gyroY);
    void setTextGyroZ(float gyroZ);
    void setTextStatus(QString status);
    void setTextSpeed(float speed);
    void setWheels(QVarLengthArray<float> wheels, const float D);
    void setCarAccelY(QVarLengthArray<float> wheels, float accelY);
    void setCarGyroX(float gyroX);
    void setCarGyroY(float gyroY);
    void setCarGyroZ(float gyroZ);
    void drawSpeedGraph(float speed);

    void robotConnected();
    void robotDisconnected();
};

#endif // GUIHANDLER_H
