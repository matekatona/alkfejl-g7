#include <QQmlProperty>
#include "qmlhandlercppside.h"

QMLHandlerCppSide::QMLHandlerCppSide(QObject *rootObject, const QString& name)
    : QObject(nullptr)
{
    if (!rootObject)
    {
        qDebug() << "Nem találom a rootObject-et.";
    }

    mainWindowObject = findItemByName(rootObject, name);

    if (!mainWindowObject)
    {
        qDebug() << "Nem találom a(z) " + name + " objektumot.";
    }

    qDebug() << name + " inicializálva.";
}

QQuickItem* QMLHandlerCppSide::findItemByName(const QString& name)
{
    Q_ASSERT(mainWindowObject != nullptr);
    if (mainWindowObject->objectName() == name)
    {
        return mainWindowObject;
    }
    return findItemByName(mainWindowObject->children(), name);
}

QQuickItem* QMLHandlerCppSide::findItemByName(QObject *rootObject, const QString& name)
{
    Q_ASSERT(rootObject != nullptr);
    if (rootObject->objectName() == name)
    {
        return (QQuickItem*)rootObject;
    }
    return findItemByName(rootObject->children(), name);
}

QQuickItem* QMLHandlerCppSide::findItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // Node keresése
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // Gyerekekben keresés
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = findItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // Nem találtuk.
    return nullptr;
}
