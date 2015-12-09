#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T22:26:02
#
#-------------------------------------------------

QT += core gui  \
    network     \
    qml quick   \
    widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = alkfejl-g7
TEMPLATE = app


SOURCES += main.cpp       \
    accelsensor.cpp       \
    alarmgenerator.cpp    \
    robot.cpp             \
    linesensor.cpp        \
    gyrosensor.cpp        \
    qmlhandlercppside.cpp \
    graph.cpp             \
    gridnode.cpp          \
    linenode.cpp          \
    noisynode.cpp         \
    guihandler.cpp        \
    wheelsensor.cpp       \
    simcomm.cpp           \
    robotcontrol.cpp

HEADERS  +=               \
    accelsensor.h         \
    alarmgenerator.h      \
    robot.h               \
    linesensor.h          \
    gyrosensor.h          \
    qmlhandlercppside.h   \
    graph.h               \
    gridnode.h            \
    linenode.h            \
    noisynode.h           \ 
    guihandler.h          \
    wheelsensor.h         \
    simcomm.h             \
    robotcontrol.h

CONFIG += c++11

DISTFILES += \
    qmlclient.qml

RESOURCES += \
    qml.qrc
