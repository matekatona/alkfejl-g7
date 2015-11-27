#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T22:26:02
#
#-------------------------------------------------

QT       += core gui \
    network \
    qml quick \
    widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = alkfejl-g7
TEMPLATE = app


SOURCES += main.cpp\
        diagclient.cpp \
    robot.cpp \
    linesensor.cpp \
    gyrosensor.cpp \
    accelsensor.cpp \
    abstractsensor.cpp \
    qmlhandlercppside.cpp

HEADERS  += diagclient.h \
    robot.h \
    linesensor.h \
    gyrosensor.h \
    accelsensor.h \
    abstractsensor.h \
    qmlhandlercppside.h

FORMS    += diagclient.ui

CONFIG += c++11

DISTFILES += \
    qmlclient.qml

RESOURCES += \
    qml.qrc
