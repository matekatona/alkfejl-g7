/********************************************************************************
** Form generated from reading UI file 'diagclient.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGCLIENT_H
#define UI_DIAGCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiagClient
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DiagClient)
    {
        if (DiagClient->objectName().isEmpty())
            DiagClient->setObjectName(QStringLiteral("DiagClient"));
        DiagClient->resize(400, 300);
        menuBar = new QMenuBar(DiagClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        DiagClient->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DiagClient);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DiagClient->addToolBar(mainToolBar);
        centralWidget = new QWidget(DiagClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DiagClient->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DiagClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DiagClient->setStatusBar(statusBar);

        retranslateUi(DiagClient);

        QMetaObject::connectSlotsByName(DiagClient);
    } // setupUi

    void retranslateUi(QMainWindow *DiagClient)
    {
        DiagClient->setWindowTitle(QApplication::translate("DiagClient", "DiagClient", 0));
    } // retranslateUi

};

namespace Ui {
    class DiagClient: public Ui_DiagClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGCLIENT_H
