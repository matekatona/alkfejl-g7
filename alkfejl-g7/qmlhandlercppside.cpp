#include <QQmlProperty>
#include "qmlhandlercppside.h"
/*! 
 * The constructor finds a QML element by its name, and initializes 
 * the `object` public member variable with a pointer to it.
 * You access the QML element via `object`.
 * \param rootObject the object to start the search form.
 * \param name the unique name of the QML element to search for, defined in the "objectName" field of the element in the QML file.
 */
QMLHandlerCppSide::QMLHandlerCppSide(QObject *rootObject, const QString& name)
    : QObject(nullptr)
{
    if (!rootObject)
    {
        qDebug() << "rootObject not found";
    }

    object = findItemByName(rootObject, name);

    if (!object)
    {
        qDebug() << "could not find" + name;
    }
}

/*!
 * It finds a QML element with the given name, starting from `object` as the root object.
 * \param name the unique name of the QML element to search for.
 * \return If the element is found, it returns a pointer to it, else it returns a NULL pointer.
 */
QQuickItem* QMLHandlerCppSide::findItemByName(const QString& name)
{
    Q_ASSERT(object != nullptr);
    if (object->objectName() == name)
    {
        return object;
    }
    return findItemByName(object->children(), name);
}

/*!
 * It finds a QML element with the given name, starting from rootObject.
 * \param name the unique name of the QML element to search for.
 * \param rootObject is a pointer to the QML element to start the search from.
 * \return If the element is found, it returns a pointer to it, else it returns a NULL pointer.
 */
QQuickItem* QMLHandlerCppSide::findItemByName(QObject *rootObject, const QString& name)
{
    Q_ASSERT(rootObject != nullptr);
    if (rootObject->objectName() == name)
    {
        return (QQuickItem*)rootObject;
    }
    return findItemByName(rootObject->children(), name);
}

/*!
 * It finds a QML element with the given name, within a list of nodes. It is rather internally used 
 * by the other overloaded findItemByName functions. It is called when the recursive search approaches
 * a QML element that has multiple children.
 * \param name the unique name of the QML element to search for.
 * \param nodes is a list of QML elements to search within.
 * \return If the element is found, it returns a pointer to it, else it returns a NULL pointer.
 */
QQuickItem* QMLHandlerCppSide::findItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // search nodes
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // search nodes in children
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = findItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // none found
    return nullptr;
}
