#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T12:29:14
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testalarmgen
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testalarmgen.cpp \
    alarmgenerator.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    alarmgenerator.h
