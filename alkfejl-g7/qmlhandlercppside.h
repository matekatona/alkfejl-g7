#ifndef QMLHANDLERCPPSIDE_H
#define QMLHANDLERCPPSIDE_H
#include <QObject>
#include <QQuickItem>

class QMLHandlerCppSide : public QObject
{
    Q_OBJECT

public:
    QMLHandlerCppSide(QObject *rootObject, const QString& name);
    ~QMLHandlerCppSide() = default;

public slots:
    /** Eseménykezelő a QML oldali addGreenEntry signalhoz. */
    void addGreenEntryHandler();
private:
    QQuickItem* findItemByName(const QString& name);
    QQuickItem* findItemByName(QObject *rootObject, const QString& name);
    QQuickItem* findItemByName(QList<QObject*> nodes, const QString& name);
public:
    QQuickItem* mainWindowObject;
};
#endif // QMLHANDLERCPPSIDE_H

