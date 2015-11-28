#include "diagclient.h"
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlhandlercppside.h"

#include "graph.h"
#include <QtQml/QQmlContext>

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

    //app.setWindowIcon(QIcon("<file_name>"));

    QMLHandlerCppSide mainWindow(engine.rootObjects()[0], "mainWindow");
    QMLHandlerCppSide gyroX(engine.rootObjects()[0], "gyroX");
    QMLHandlerCppSide speedGraph(engine.rootObjects()[0], "speedGraph");

    for(int i=0;i<20;i++){
        QMetaObject::invokeMethod(speedGraph.mainWindowObject, "removeFirstSample", Qt::DirectConnection);
        QMetaObject::invokeMethod(speedGraph.mainWindowObject, "appendSample", Qt::DirectConnection, Q_ARG(double, i/40.0+0.5));
    }

    QMetaObject::invokeMethod(mainWindow.mainWindowObject, "test", Qt::DirectConnection);
    /** TODO: QMLHandlerCppSide mainWindowObject tagváltozója legyen private (mint eredetileg) és a nevét is írjuk át valami logikusabbra.
     *  Legyen callFunc() tagfüggvény, mely implementálva van pár esetre (van/nincs visszatérési érték, nincs/van/több argumentuma is van).
     */
    QMetaObject::invokeMethod(gyroX.mainWindowObject, "setAngle", Qt::DirectConnection, Q_ARG(QVariant, 0));

    return app.exec();
}
