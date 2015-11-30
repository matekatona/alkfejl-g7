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

private:
    QQuickItem* findItemByName(const QString& name);
    QQuickItem* findItemByName(QObject *rootObject, const QString& name);
    QQuickItem* findItemByName(QList<QObject*> nodes, const QString& name);
public:
    QQuickItem* object;
};
#endif // QMLHANDLERCPPSIDE_H

