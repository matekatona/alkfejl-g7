//! \file 
//! \brief This file contains the QMLHandlerCppSide class.

#ifndef QMLHANDLERCPPSIDE_H
#define QMLHANDLERCPPSIDE_H
#include <QObject>
#include <QQuickItem>

/*! \brief This class helps referencing objects defined in a QML file. */

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
    QQuickItem* object; //!< It allows you to access the QML element found by the constructor.
};
#endif // QMLHANDLERCPPSIDE_H

