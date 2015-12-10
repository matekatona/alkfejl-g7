//! \file 
//! \brief _Connection between Front-end and Back-end._ This file contains the GuiHandler class.

#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QObject>
#include <QVarLengthArray>
#include "qmlhandlercppside.h"

/*! \brief This class implements the event handlers for the Qt Quick controls. */

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
            QMLHandlerCppSide *statusHistory, \
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
    QMLHandlerCppSide *statusHistory;
    QMLHandlerCppSide *speedGraph;
    QMLHandlerCppSide *buttonConDiscon;
    QMLHandlerCppSide *buttonSendStatus;
    QMLHandlerCppSide *buttonSendSpeed;
    QMLHandlerCppSide *buttonCarSelfTest;

signals:

    void buttonConClicked(); //!< This signal is emitted by `qmlbuttonConDisconClicked`, and is connected to the `connect` slot of `Robot`.
    void buttonDisClicked(); //!< This signal is emitted by `qmlbuttonConDisconClicked`, and is connected to the `disconnect` slot of `Robot`.
    void buttonSendStatusClicked(QString status); //!< This signal is emitted by `qmlbuttonSendStatusClicked`, and is connected to the `status` slot of `Robot`, which will actually send the new status to V-REP.
												  //!< \param status is the new status of the `Robot` instance.
    void buttonSendSpeedClicked(float speed); //!< This signal is emitted by `qmlbuttonSendSpeedClicked`, and is connected to the `speed` slot of `Robot`, which will actually send the new speed to V-REP.
											  //!< \param speed is the new speed of the `Robot` instance.
    void buttonCarSelfTestClicked(); //!< This signal is emitted by `qmlbuttonCarSelfTestClicked`.

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
    void addStatusHistory(QString status);

    void robotConnected();
    void robotDisconnected();
};

#endif // GUIHANDLER_H
