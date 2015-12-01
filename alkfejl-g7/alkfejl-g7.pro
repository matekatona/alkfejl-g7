#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T22:26:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = alkfejl-g7
TEMPLATE = app


SOURCES +=\
    robot.cpp \
    linesensor.cpp \
    gyrosensor.cpp \
    accelsensor.cpp \
    abstractsensor.cpp \
    wheelsensor.cpp \
    commandsocket.cpp \
    main.cpp

HEADERS  += \
    robot.h \
    linesensor.h \
    gyrosensor.h \
    accelsensor.h \
    abstractsensor.h \
    wheelsensor.h \
    commandsocket.h

FORMS    +=

CONFIG += c++11

DISTFILES += \
    qmlclient.qml

RESOURCES += \
    qml.qrc
