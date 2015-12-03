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
    QTimer timer;

    timer.setSingleShot(false);
    timer.setInterval(100);

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
    QMLHandlerCppSide buttonSendStatus(engine.rootObjects()[0], "buttonSendStatus");
    QMLHandlerCppSide buttonSendSpeed(engine.rootObjects()[0], "buttonSendSpeed");
    QMLHandlerCppSide buttonCarSelfTest(engine.rootObjects()[0], "buttonCarSelfTest");

    GuiHandler guihandle(&alertLamp, &lineSens, &textAccelX, &textAccelY, &textAccelZ, &textGyroX, &textGyroY, &textGyroZ, &textCurStatus, &comboSetStatus, &textCurSpeed, &editSetSpeed, &wheels, &carAccelY, &carGyroX, &carGyroY, &carGyroZ, &speedGraph, &buttonSendStatus, &buttonSendSpeed, &buttonCarSelfTest);

    Robot testRobi;

    QObject::connect(&timer, SIGNAL(timeout()), &testRobi, SLOT(update()));
    QObject::connect(&guihandle, SIGNAL(buttonSendStatusClicked(QString)), &testRobi, SLOT(setStatus(QString)));
    QObject::connect(&guihandle, SIGNAL(buttonSendSpeedClicked(QString)), &testRobi, SLOT(setSpeed(QString)));
    QObject::connect(&testRobi, SIGNAL(setLedStrip(QVarLengthArray<bool>)), &guihandle, SLOT(setLedStrip(QVarLengthArray<bool>)));
    QObject::connect(&testRobi, SIGNAL(setTextAccelX(float)), &guihandle, SLOT(setTextAccelX(float)));
    QObject::connect(&testRobi, SIGNAL(setTextAccelY(float)), &guihandle, SLOT(setTextAccelY(float)));
    QObject::connect(&testRobi, SIGNAL(setTextAccelZ(float)), &guihandle, SLOT(setTextAccelZ(float)));
    QObject::connect(&testRobi, SIGNAL(setTextGyroX(float)), &guihandle, SLOT(setTextGyroX(float)));
    QObject::connect(&testRobi, SIGNAL(setTextGyroY(float)), &guihandle, SLOT(setTextGyroY(float)));
    QObject::connect(&testRobi, SIGNAL(setTextGyroZ(float)), &guihandle, SLOT(setTextGyroZ(float)));
    QObject::connect(&testRobi, SIGNAL(setTextStatus(QString)), &guihandle, SLOT(setTextStatus(QString)));
    QObject::connect(&testRobi, SIGNAL(setTextSpeed(float)), &guihandle, SLOT(setTextSpeed(float)));
    QObject::connect(&testRobi, SIGNAL(setWheels(QVarLengthArray<float>, const float)), &guihandle, SLOT(setWheels(QVarLengthArray<float>, const float)));
    QObject::connect(&testRobi, SIGNAL(setCarAccelY(QVarLengthArray<float>, float)), &guihandle, SLOT(setCarAccelY(QVarLengthArray<float>, float)));
    QObject::connect(&testRobi, SIGNAL(setCarGyroX(float)), &guihandle, SLOT(setCarGyroX(float)));
    QObject::connect(&testRobi, SIGNAL(setCarGyroY(float)), &guihandle, SLOT(setCarGyroY(float)));
    QObject::connect(&testRobi, SIGNAL(setCarGyroZ(float)), &guihandle, SLOT(setCarGyroZ(float)));
    QObject::connect(&testRobi, SIGNAL(drawSpeedGraph(float)), &guihandle, SLOT(drawSpeedGraph(float)));

    timer.start();

//    for(int i=0;i<20;i++){
//        QMetaObject::invokeMethod(speedGraph.object, "removeFirstSample", Qt::DirectConnection);
//        QMetaObject::invokeMethod(speedGraph.object, "appendSample", Qt::DirectConnection, Q_ARG(double, i/40.0+0.5));
//    }


//    /**
//     * @brief testStrip to QML
//     */

//    QVarLengthArray<bool> testStrip;

//    for(int i=0; i<21; i++)
//        testStrip.append(true);

//    QVariantList testVar;

//    for(int i=0; i<21; i++)
//        testVar << testStrip.at(i);

//    QMetaObject::invokeMethod(lineSens.object, "setValues", Qt::DirectConnection, Q_ARG(QVariant, QVariant::fromValue(testVar)));

//    /**
//     * @brief testStrip to QML
//     */

//    float speed = 0.5;
//    QString status = "Run";

//    //QMetaObject::invokeMethod(mainWindow.object, "test", Qt::DirectConnection);
//    QMetaObject::invokeMethod(textCurSpeed.object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, speed));
//    QMetaObject::invokeMethod(textCurStatus.object, "setValue", Qt::DirectConnection, Q_ARG(QVariant, status));
//    /** TODO: QMLHandlerCppSide object tagváltozója legyen private (mint eredetileg) és a nevét is írjuk át valami logikusabbra.
//     *  Legyen callFunc() tagfüggvény, mely implementálva van pár esetre (van/nincs visszatérési érték, nincs/van/több argumentuma is van).
//     */
//    QMetaObject::invokeMethod(gyroX.object, "setAngle", Qt::DirectConnection, Q_ARG(QVariant, 0));

//    RobotHistory testHistory(0);

//    for(int i=0; i<4000; i++){
//        testHistory.addNewAccelData(QVarLengthArray<float>({3.2, 0.2, 4.3}));
//    }

    return app.exec();
}
