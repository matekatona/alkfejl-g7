#include "guihandler.h"

/*! 
 * This is the constructor of GuiHandler.
 * Its parameters are objects on the mainWindow (defined in main.qml).
 * It will also connect the event handlers to the signals of some objects passed here.
 * \see mainWindow
 */

GuiHandler::GuiHandler( \
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
        QMLHandlerCppSide *buttonCarSelfTest)
{
    this->alertLamp=alertLamp;
    this->lineSens=lineSens;
    this->textAccelX=textAccelX;
    this->textAccelY=textAccelY;
    this->textAccelZ=textAccelZ;
    this->textGyroX=textGyroX;
    this->textGyroY=textGyroY;
    this->textGyroZ=textGyroZ;
    this->textCurStatus=textCurStatus;
    this->comboSetStatus=comboSetStatus;
    this->textCurSpeed=textCurSpeed;
    this->editSetSpeed=editSetSpeed;
    this->wheels=wheels;
    this->carAccelY=carAccelY;
    this->carGyroX=carGyroX;
    this->carGyroY=carGyroY;
    this->carGyroZ=carGyroZ;
    this->speedGraph=speedGraph;
    this->buttonConDiscon=buttonConDiscon;
    this->buttonSendStatus=buttonSendStatus;
    this->buttonSendSpeed=buttonSendSpeed;
    this->buttonCarSelfTest=buttonCarSelfTest;

    QObject::connect(this->buttonConDiscon->object, SIGNAL(clicked()), this, SLOT(qmlbuttonConDisconClicked()));
    QObject::connect(this->buttonCarSelfTest->object, SIGNAL(clicked()), this, SLOT(qmlbuttonCarSelfTestClicked()));
    QObject::connect(this->buttonSendStatus->object, SIGNAL(clicked()), this, SLOT(qmlbuttonSendStatusClicked()));
    QObject::connect(this->buttonSendSpeed->object, SIGNAL(clicked()), this, SLOT(qmlbuttonSendSpeedClicked()));

}

/*! 
 * \brief The click event handler of buttonConDiscon. 
 *
 * It will emit another signal, `buttonConDisconClicked`.
 */
void GuiHandler::qmlbuttonConDisconClicked()
{
    qDebug() << "ConDiscon button clicked! Command: " << this->buttonConDiscon->object->property("text").toString();
    emit this->buttonConDisconClicked();
}

/*! 
 * \brief The click event handler of buttonSendStatus. 
 *
 * It will emit another signal, `buttonSendStatusClicked`, which is connected to the `status` slot of the `Robot` instance 
 * in `main`, and sends V-REP the new status to set.
 */
void GuiHandler::qmlbuttonSendStatusClicked()
{
    qDebug() << "Send status clicked! Current status: " << this->comboSetStatus->object->property("currentText").toString();
    emit this->buttonSendStatusClicked(this->comboSetStatus->object->property("currentText").toString());
}

/*! 
 * \brief The click event handler of buttonSendSpeed. 
 *
 * It will emit another signal, `buttonSendSpeedClicked`, which is connected to the `speed` slot of the `Robot` instance 
 * in `main`, and sends V-REP the new speed to set.
 */
void GuiHandler::qmlbuttonSendSpeedClicked()
{
    qDebug() << "Send speed clicked! Current speed: " << this->editSetSpeed->object->property("text").toString();
    QString raw = this->editSetSpeed->object->property("text").toString();
    raw.replace(",", ".");
    emit this->buttonSendSpeedClicked(raw.toFloat());
}

/*! 
 * \brief The click event handler of buttonCarSelfTest.
 *
 * It will emit another signal, `buttonCarSelfTestClicked`.
 */
void GuiHandler::qmlbuttonCarSelfTestClicked()
{
    qDebug() << "Car self test clicked!";
    emit this->buttonCarSelfTestClicked();
}

/*!
 * \brief This calls the setAlert JavaScript method in `alertLamp`, to set the alert value.
 * \param alert sets the `alertLamp` status indicator value. If it is true, `alertLamp` is ON.
 */
void GuiHandler::setAlert(bool alert)
{
    QMetaObject::invokeMethod(this->alertLamp->object, "setAlert", Qt::DirectConnection, Q_ARG(QVariant, alert));
}

/*!
 * \brief This calls the setValues JavaScript method in `lineSens`, to set the ON/OFF status of the LEDs on the strip.
 * \param leds is an array of boolean values to set the corresponding LEDs ON/OFF.
 */
void GuiHandler::setLedStrip(QVarLengthArray<bool> leds)
{
    QVariantList values;

    for(int i=0; i<21; i++)
        values << leds.at(i);
    QMetaObject::invokeMethod(this->lineSens->object, "setValues", Qt::DirectConnection, Q_ARG(QVariant, QVariant::fromValue(values)));
    QMetaObject::invokeMethod(this->alertLamp->object, "setAlertLamp", Qt::DirectConnection);
}

/*!
 * \brief This sets the text of the `KeyValuePair` QML element showing the value for "Acceleration X" on the GUI.
 * \param accelX is the floating point acceleration value to display.
 */
void GuiHandler::setTextAccelX(float accelX)
{
    QMetaObject::invokeMethod(this->textAccelX->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(accelX)));
}

/*!
 * \brief This sets the text of the `KeyValuePair` QML element showing the value for "Acceleration Y" on the GUI.
 * \param accelY is the floating point acceleration value to display.
 */

void GuiHandler::setTextAccelY(float accelY)
{
    QMetaObject::invokeMethod(this->textAccelY->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(accelY)));
}

/*!
 * \brief This sets the text of the `KeyValuePair` QML element showing the value for "Acceleration Z" on the GUI.
 * \param accelZ is the floating point acceleration value to display.
 */
void GuiHandler::setTextAccelZ(float accelZ)
{
    QMetaObject::invokeMethod(this->textAccelZ->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(accelZ)));
}

/*!
 * \brief This sets the text of the `KeyValuePair` QML element showing the value for "Gyroscope X" on the GUI.
 * \param gyroX is the floating point gyro sensor value to display.
 */
void GuiHandler::setTextGyroX(float gyroX)
{
    QMetaObject::invokeMethod(this->textGyroX->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(gyroX)));
}

/*!
 * This sets the text of the `KeyValuePair` QML element showing the value for "Gyroscope Y" on the GUI.
 * \param gyroY is the floating point gyro sensor value to display.
 */
void GuiHandler::setTextGyroY(float gyroY)
{
    QMetaObject::invokeMethod(this->textGyroY->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(gyroY)));
}

/*!
 * \brief This sets the text of the `KeyValuePair` QML element showing the value for "Gyroscope Z" on the GUI.
 * \param gyroZ is the floating point gyro sensor value to display.
 */
void GuiHandler::setTextGyroZ(float gyroZ)
{
    QMetaObject::invokeMethod(this->textGyroZ->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(gyroZ)));
}

/*!
 * \brief This sets the text of the `KeyValuePair` QML element showing the value for "Current status" on the GUI.
 * \param status is the status string to display.
 */
void GuiHandler::setTextStatus(QString status)
{
    QMetaObject::invokeMethod(this->textCurStatus->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, status));
}

/*!
 * \brief This sets the text of the `KeyValuePair` QML element showing the value for "Speed" on the GUI.
 * \param speed is the floating point speed value to display.
 */
void GuiHandler::setTextSpeed(float speed)
{
    QMetaObject::invokeMethod(this->textCurSpeed->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(speed)));
}

/*!
 * \brief This sets the angle of the `wheels` `GyroIndicator` QML element on the GUI, based on the wheel parameters acquired from V-REP.
 * \param wheels is an array that stores the speed of individual wheels.
 * \param D is the distance of wheels.
 */
void GuiHandler::setWheels(QVarLengthArray<float> wheels, float D)
{
    float v, R, angle;
    float dt=10;

    v=(wheels.at(0)+wheels.at(1))/2.0;
    R=v*D/(wheels.at(1)-wheels.at(0));
    if(R==0 || R!=R)
        angle=0;
    else
        angle=-v*dt/R;

    QMetaObject::invokeMethod(this->wheels->object, "setAngle", Qt::DirectConnection, Q_ARG(QVariant, angle));
}

/*!
 * \brief This sets the angle of the `AccelY` `GyroIndicator` QML element on the GUI, based on the parameters acquired from V-REP.
 * \param wheels is an array that stores the speed of individual wheels.
 * \param accelY is the horizontal acceleration of the robot.
 */
void GuiHandler::setCarAccelY(QVarLengthArray<float> wheels, float accelY)
{
    float v, R, angle;
    float dt=10;

    v=(wheels.at(0)+wheels.at(1))/2.0;
    R=(v*v)/(accelY);
    if(R==0 || R!=R)
        angle=0;
    else
        angle=-v*dt/R;

    QMetaObject::invokeMethod(this->carAccelY->object, "setAngle", Qt::DirectConnection, Q_ARG(QVariant, angle));
}

/*!
 * \brief This sets the angle of the `CarGyroX` `GyroIndicator` QML element on the GUI.
 * \param gyroX is the value to add to the angle value already displayed on the indicator.
 */
void GuiHandler::setCarGyroX(float gyroX)
{
    QMetaObject::invokeMethod(this->carGyroX->object, "addAngle", Qt::DirectConnection, Q_ARG(QVariant, gyroX));
}

/*!
 * \brief This sets the angle of the `CarGyroY` `GyroIndicator` QML element on the GUI.
 * \param gyroY is the value to add to the angle value already displayed on the indicator.
 */
void GuiHandler::setCarGyroY(float gyroY)
{
    QMetaObject::invokeMethod(this->carGyroY->object, "addAngle", Qt::DirectConnection, Q_ARG(QVariant, gyroY));
}

/*!
 * \brief This sets the angle of the `CarGyroZ` `GyroIndicator` QML element on the GUI.
 * \param gyroZ is the value to add to the angle value already displayed on the indicator.
 */
void GuiHandler::setCarGyroZ(float gyroZ)
{
    QMetaObject::invokeMethod(this->carGyroZ->object, "addAngle", Qt::DirectConnection, Q_ARG(QVariant, gyroZ));
}

/*!
 * \brief This adds a new sample to the `speedGraph` `Graph` QML element on the GUI, and redraws it.
 * \param speed is the sample to add to the graph.
 */
void GuiHandler::drawSpeedGraph(float speed)
{
    QMetaObject::invokeMethod(this->speedGraph->object, "newSample", Qt::DirectConnection, Q_ARG(QVariant, (-speed/3.0)+0.5));
}
