#include "guihandler.h"

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
        QMLHandlerCppSide *statusHistory, \
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
    this->statusHistory=statusHistory;
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

void GuiHandler::qmlbuttonConDisconClicked()
{
    QString command = this->buttonConDiscon->object->property("text").toString();
    if(command == "Connect")
        emit this->buttonConClicked();
    else
        emit this->buttonDisClicked();
}

void GuiHandler::qmlbuttonSendStatusClicked()
{
    emit this->buttonSendStatusClicked(this->comboSetStatus->object->property("currentText").toString());
}

void GuiHandler::qmlbuttonSendSpeedClicked()
{
    QString raw = this->editSetSpeed->object->property("text").toString();
    raw.replace(",", ".");
    emit this->buttonSendSpeedClicked(raw.toFloat());
}

void GuiHandler::qmlbuttonCarSelfTestClicked()
{
    emit this->buttonCarSelfTestClicked();
}

void GuiHandler::setAlert(int color)
{
    QMetaObject::invokeMethod(this->alertLamp->object, "setAlert", Qt::DirectConnection, Q_ARG(QVariant, color));
}

void GuiHandler::setLedStrip(QVarLengthArray<bool> leds)
{
    QVariantList values;

    for(int i=0; i<21; i++)
        values << leds.at(i);
    QMetaObject::invokeMethod(this->lineSens->object, "setValues", Qt::DirectConnection, Q_ARG(QVariant, QVariant::fromValue(values)));
}

void GuiHandler::setTextAccelX(float accelX)
{
    QMetaObject::invokeMethod(this->textAccelX->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(accelX)));
}

void GuiHandler::setTextAccelY(float accelY)
{
    QMetaObject::invokeMethod(this->textAccelY->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(accelY)));
}

void GuiHandler::setTextAccelZ(float accelZ)
{
    QMetaObject::invokeMethod(this->textAccelZ->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(accelZ)));
}

void GuiHandler::setTextGyroX(float gyroX)
{
    QMetaObject::invokeMethod(this->textGyroX->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(gyroX)));
}

void GuiHandler::setTextGyroY(float gyroY)
{
    QMetaObject::invokeMethod(this->textGyroY->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(gyroY)));
}

void GuiHandler::setTextGyroZ(float gyroZ)
{
    QMetaObject::invokeMethod(this->textGyroZ->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(gyroZ)));
}

void GuiHandler::setTextStatus(QString status)
{
    QMetaObject::invokeMethod(this->textCurStatus->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, status));
}

void GuiHandler::setTextSpeed(float speed)
{
    QMetaObject::invokeMethod(this->textCurSpeed->object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, QString::number(speed)));
}

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

void GuiHandler::setCarAccelY(QVarLengthArray<float> wheels, float accelY)
{
    float v, R, angle;
    float dt=10;

    v=(wheels.at(0)+wheels.at(1))/2.0;
    R=(v*v)/(accelY);
    if(R==0 || R!=R)
        angle=0;
    else
        angle=v*dt/R;

    QMetaObject::invokeMethod(this->carAccelY->object, "setAngle", Qt::DirectConnection, Q_ARG(QVariant, angle));
}

void GuiHandler::setCarGyroX(float gyroX)
{
    if(gyroX!=gyroX)
        gyroX=0;

    gyroX*=-5.55;

    QMetaObject::invokeMethod(this->carGyroX->object, "addAngle", Qt::DirectConnection, Q_ARG(QVariant, gyroX));
}

void GuiHandler::setCarGyroY(float gyroY)
{
    if(gyroY!=gyroY)
        gyroY=0;

    gyroY*=-5.55;

    QMetaObject::invokeMethod(this->carGyroY->object, "addAngle", Qt::DirectConnection, Q_ARG(QVariant, gyroY));
}

void GuiHandler::setCarGyroZ(float gyroZ)
{
    if(gyroZ!=gyroZ)
        gyroZ=0;

    gyroZ*=-5.55;

    QMetaObject::invokeMethod(this->carGyroZ->object, "addAngle", Qt::DirectConnection, Q_ARG(QVariant, gyroZ));
}

void GuiHandler::drawSpeedGraph(float speed)
{
    if(speed!=speed)
        speed=0;

    QMetaObject::invokeMethod(this->speedGraph->object, "newSample", Qt::DirectConnection, Q_ARG(QVariant, (-speed/3.0)+0.5));
}

void GuiHandler::addStatusHistory(QString status)
{
    QMetaObject::invokeMethod(this->statusHistory->object, "addValue", Qt::DirectConnection, Q_ARG(QVariant, status));
}

void GuiHandler::robotConnected()
{
    this->buttonCarSelfTest->object->setProperty("enabled", true);
    this->buttonConDiscon->object->setProperty("text", "Disconnect");
}

void GuiHandler::robotDisconnected()
{
    this->buttonCarSelfTest->object->setProperty("enabled", false);
    this->buttonConDiscon->object->setProperty("text", "Connect");
}
