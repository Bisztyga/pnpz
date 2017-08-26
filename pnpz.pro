#-------------------------------------------------
#
# Project created by QtCreator 2017-08-26T11:24:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pnpz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/vmware-vix-disklib/lib64/ -lvixDiskLib

INCLUDEPATH += $$PWD/../../../../usr/lib/vmware-vix-disklib/include
DEPENDPATH += $$PWD/../../../../usr/lib/vmware-vix-disklib/include
