#include <QApplication>
#include <QGuiApplication>
#include <QtWidgets>
#include <QQmlApplicationEngine>
#include <QVarLengthArray>
#include "qmlhandlercppside.h"

#include "graph.h"
#include "guihandler.h"
#include "robot.h"
#include <QtQml/QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Graph>("Graph", 1, 0, "Graph");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    app.setWindowIcon(QIcon(":/content/icon.png"));

    QMLHandlerCppSide alertLamp(engine.rootObjects()[0], "alertLamp");
    QMLHandlerCppSide lineSens(engine.rootObjects()[0], "lineSens");
    QMLHandlerCppSide textAccelX(engine.rootObjects()[0], "textAccelX");
    QMLHandlerCppSide textAccelY(engine.rootObjects()[0], "textAccelY");
    QMLHandlerCppSide textAccelZ(engine.rootObjects()[0], "textAccelZ");
    QMLHandlerCppSide textGyroX(engine.rootObjects()[0], "textGyroX");
    QMLHandlerCppSide textGyroY(engine.rootObjects()[0], "textGyroY");
    QMLHandlerCppSide textGyroZ(engine.rootObjects()[0], "textGyroZ");
    QMLHandlerCppSide textCurStatus(engine.rootObjects()[0], "textCurStatus");
    QMLHandlerCppSide comboSetStatus(engine.rootObjects()[0], "comboSetStatus");
    QMLHandlerCppSide textCurSpeed(engine.rootObjects()[0], "textCurSpeed");
    QMLHandlerCppSide editSetSpeed(engine.rootObjects()[0], "editSetSpeed");
    QMLHandlerCppSide wheels(engine.rootObjects()[0], "wheels");
    QMLHandlerCppSide carAccelY(engine.rootObjects()[0], "carAccelY");
    QMLHandlerCppSide carGyroX(engine.rootObjects()[0], "carGyroX");
    QMLHandlerCppSide carGyroY(engine.rootObjects()[0], "carGyroY");
    QMLHandlerCppSide carGyroZ(engine.rootObjects()[0], "carGyroZ");
    QMLHandlerCppSide speedGraph(engine.rootObjects()[0], "speedGraph");
    QMLHandlerCppSide buttonConDiscon(engine.rootObjects()[0], "buttonConDiscon");
    QMLHandlerCppSide buttonSendStatus(engine.rootObjects()[0], "buttonSendStatus");
    QMLHandlerCppSide buttonSendSpeed(engine.rootObjects()[0], "buttonSendSpeed");
    QMLHandlerCppSide buttonCarSelfTest(engine.rootObjects()[0], "buttonCarSelfTest");

    GuiHandler guihandle(&alertLamp, &lineSens, &textAccelX, &textAccelY, &textAccelZ, &textGyroX, &textGyroY, &textGyroZ, &textCurStatus, &comboSetStatus, &textCurSpeed, &editSetSpeed, &wheels, &carAccelY, &carGyroX, &carGyroY, &carGyroZ, &speedGraph, &buttonConDiscon, &buttonSendStatus, &buttonSendSpeed, &buttonCarSelfTest);
    Robot mikrobi;

    QObject::connect(&guihandle, SIGNAL(buttonConClicked()), &mikrobi, SLOT(connect()));
    QObject::connect(&guihandle, SIGNAL(buttonDisClicked()), &mikrobi, SLOT(disconnect()));
    QObject::connect(&guihandle, SIGNAL(buttonCarSelfTestClicked()), &mikrobi, SLOT(selfTest()));
    QObject::connect(&guihandle, SIGNAL(buttonSendStatusClicked(QString)), &mikrobi, SLOT(status(QString)));
    QObject::connect(&guihandle, SIGNAL(buttonSendSpeedClicked(float)), &mikrobi, SLOT(speed(float)));

    QObject::connect(&mikrobi, SIGNAL(connected()), &guihandle, SLOT(robotConnected()));
    QObject::connect(&mikrobi, SIGNAL(setAlert(int)), &guihandle, SLOT(setAlert(int)));
    QObject::connect(&mikrobi, SIGNAL(disconnected()), &guihandle, SLOT(robotDisconnected()));

    QObject::connect(&mikrobi, SIGNAL(setLedStrip(QVarLengthArray<bool>)), &guihandle, SLOT(setLedStrip(QVarLengthArray<bool>)));
    QObject::connect(&mikrobi, SIGNAL(setTextAccelX(float)), &guihandle, SLOT(setTextAccelX(float)));
    QObject::connect(&mikrobi, SIGNAL(setTextAccelY(float)), &guihandle, SLOT(setTextAccelY(float)));
    QObject::connect(&mikrobi, SIGNAL(setTextAccelZ(float)), &guihandle, SLOT(setTextAccelZ(float)));
    QObject::connect(&mikrobi, SIGNAL(setTextGyroX(float)), &guihandle, SLOT(setTextGyroX(float)));
    QObject::connect(&mikrobi, SIGNAL(setTextGyroY(float)), &guihandle, SLOT(setTextGyroY(float)));
    QObject::connect(&mikrobi, SIGNAL(setTextGyroZ(float)), &guihandle, SLOT(setTextGyroZ(float)));
    QObject::connect(&mikrobi, SIGNAL(setTextStatus(QString)), &guihandle, SLOT(setTextStatus(QString)));
    QObject::connect(&mikrobi, SIGNAL(setTextSpeed(float)), &guihandle, SLOT(setTextSpeed(float)));
    QObject::connect(&mikrobi, SIGNAL(setWheels(QVarLengthArray<float>, const float)), &guihandle, SLOT(setWheels(QVarLengthArray<float>, const float)));
    QObject::connect(&mikrobi, SIGNAL(setCarAccelY(QVarLengthArray<float>, float)), &guihandle, SLOT(setCarAccelY(QVarLengthArray<float>, float)));
    QObject::connect(&mikrobi, SIGNAL(setCarGyroX(float)), &guihandle, SLOT(setCarGyroX(float)));
    QObject::connect(&mikrobi, SIGNAL(setCarGyroY(float)), &guihandle, SLOT(setCarGyroY(float)));
    QObject::connect(&mikrobi, SIGNAL(setCarGyroZ(float)), &guihandle, SLOT(setCarGyroZ(float)));
    QObject::connect(&mikrobi, SIGNAL(drawSpeedGraph(float)), &guihandle, SLOT(drawSpeedGraph(float)));

    return app.exec();
}
