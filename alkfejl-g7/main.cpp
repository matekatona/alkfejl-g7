#include "diagclient.h"
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVarLengthArray>
#include "qmlhandlercppside.h"

#include "graph.h"
#include "guihandler.h"
#include <QtQml/QQmlContext>

#include "robothistory.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    DiagClient w;
//    w.show();

//    return a.exec();

    QGuiApplication app(argc, argv);

    qmlRegisterType<Graph>("Graph", 1, 0, "Graph");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    app.setWindowIcon(QIcon(":/content/icon.png"));

    QMLHandlerCppSide mainWindow(engine.rootObjects()[0], "mainWindow");
    QMLHandlerCppSide alertLamp(engine.rootObjects()[0], "alertLamp");
    QMLHandlerCppSide lineSens(engine.rootObjects()[0], "lineSens");
    QMLHandlerCppSide textAccelX(engine.rootObjects()[0], "textAccelX");
    QMLHandlerCppSide textAccelY(engine.rootObjects()[0], "textAccelY");
    QMLHandlerCppSide textAccelZ(engine.rootObjects()[0], "textAccelZ");
    QMLHandlerCppSide textGyroX(engine.rootObjects()[0], "textGyroX");
    QMLHandlerCppSide textGyroY(engine.rootObjects()[0], "textGyroY");
    QMLHandlerCppSide textGyroZ(engine.rootObjects()[0], "textGyroZ");
    QMLHandlerCppSide textCurStatus(engine.rootObjects()[0], "textCurStatus");
    QMLHandlerCppSide textCurSpeed(engine.rootObjects()[0], "textCurSpeed");
    QMLHandlerCppSide wheels(engine.rootObjects()[0], "wheels");
    QMLHandlerCppSide carAccelY(engine.rootObjects()[0], "carAccelY");
    QMLHandlerCppSide carGyroX(engine.rootObjects()[0], "carGyroX");
    QMLHandlerCppSide carGyroY(engine.rootObjects()[0], "carGyroY");
    QMLHandlerCppSide carGyroZ(engine.rootObjects()[0], "carGyroZ");
    QMLHandlerCppSide speedGraph(engine.rootObjects()[0], "speedGraph");
    QMLHandlerCppSide buttonSendStatus(engine.rootObjects()[0], "buttonSendStatus");
    QMLHandlerCppSide buttonSendSpeed(engine.rootObjects()[0], "buttonSendSpeed");
    QMLHandlerCppSide buttonCarSelfTest(engine.rootObjects()[0], "buttonCarSelfTest");

    GuiHandler guihandle(&alertLamp, &lineSens, &textAccelX, &textAccelY, &textAccelZ, &textGyroX, &textGyroY, &textGyroZ, &textCurStatus, &textCurSpeed, &wheels, &carAccelY, &carGyroX, &carGyroY, &carGyroZ, &speedGraph, &buttonSendStatus, &buttonSendSpeed, &buttonCarSelfTest);

//    for(int i=0;i<20;i++){
//        QMetaObject::invokeMethod(speedGraph.mainWindowObject, "removeFirstSample", Qt::DirectConnection);
//        QMetaObject::invokeMethod(speedGraph.mainWindowObject, "appendSample", Qt::DirectConnection, Q_ARG(double, i/40.0+0.5));
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

//    QMetaObject::invokeMethod(lineSens.mainWindowObject, "setValues", Qt::DirectConnection, Q_ARG(QVariant, QVariant::fromValue(testVar)));

//    /**
//     * @brief testStrip to QML
//     */

//    float speed = 0.5;
//    QString status = "Run";

//    //QMetaObject::invokeMethod(mainWindow.mainWindowObject, "test", Qt::DirectConnection);
//    QMetaObject::invokeMethod(textCurSpeed.mainWindowObject, "setValue", Qt::DirectConnection, Q_ARG(QVariant, speed));
//    QMetaObject::invokeMethod(textCurStatus.mainWindowObject, "setValue", Qt::DirectConnection, Q_ARG(QVariant, status));
//    /** TODO: QMLHandlerCppSide mainWindowObject tagváltozója legyen private (mint eredetileg) és a nevét is írjuk át valami logikusabbra.
//     *  Legyen callFunc() tagfüggvény, mely implementálva van pár esetre (van/nincs visszatérési érték, nincs/van/több argumentuma is van).
//     */
//    QMetaObject::invokeMethod(gyroX.mainWindowObject, "setAngle", Qt::DirectConnection, Q_ARG(QVariant, 0));

//    RobotHistory testHistory(0);

//    for(int i=0; i<4000; i++){
//        testHistory.addNewAccelData(QVarLengthArray<float>({3.2, 0.2, 4.3}));
//    }

    return app.exec();
}
