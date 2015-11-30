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
        QMLHandlerCppSide *textCurSpeed, \
        QMLHandlerCppSide *wheels, \
        QMLHandlerCppSide *carAccelY, \
        QMLHandlerCppSide *carGyroX, \
        QMLHandlerCppSide *carGyroY, \
        QMLHandlerCppSide *carGyroZ, \
        QMLHandlerCppSide *speedGraph, \
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
    this->textCurSpeed=textCurSpeed;
    this->wheels=wheels;
    this->carAccelY=carAccelY;
    this->carGyroX=carGyroX;
    this->carGyroY=carGyroY;
    this->carGyroZ=carGyroZ;
    this->speedGraph=speedGraph;
    this->buttonSendStatus=buttonSendStatus;
    this->buttonSendSpeed=buttonSendSpeed;
    this->buttonCarSelfTest=buttonCarSelfTest;

    QObject::connect(this->buttonCarSelfTest->mainWindowObject, SIGNAL(clicked()), this, SLOT(qmlbuttonCarSelfTestClicked()));

}

void GuiHandler::qmlbuttonSendStatusClicked(){}
void GuiHandler::qmlbuttonSendSpeedClicked(){}
void GuiHandler::qmlbuttonCarSelfTestClicked()
{
    qDebug() << "Car self test clicked!";
}

void GuiHandler::setAlert(bool alert){}
void GuiHandler::setLedStrip(QVarLengthArray<bool> leds){}
void GuiHandler::setTextAccelX(float accelX){}
void GuiHandler::setTextAccelY(float accelY){}
void GuiHandler::setTextAccelZ(float accelZ){}
void GuiHandler::setTextGyroX(float gyroX){}
void GuiHandler::setTextGyroY(float gyroY){}
void GuiHandler::setTextGyroZ(float gyroZ){}
void GuiHandler::setTextStatus(QString status){}
void GuiHandler::setTextSpeed(float speed){}
void GuiHandler::setWheels(QVarLengthArray<float> wheels){}
void GuiHandler::setCarAccelY(float accelY){}
void GuiHandler::setCarGyroX(float gyroX){}
void GuiHandler::setCarGyroY(float gyroY){}
void GuiHandler::setCarGyroZ(float gyroZ){}
void GuiHandler::drawSpeedGraph(float speed){}
