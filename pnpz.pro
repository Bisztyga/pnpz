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
        mainwindow.cpp \
    asyncinotify.cpp \
    getidbox.cpp \
    summary.cpp \
    events.cpp \
    getevent.cpp \
    getname.cpp \
    common.cpp

HEADERS  += mainwindow.h \
    asyncinotify.h \
    getidbox.h \
    summary.h \
    events.h \
    getevent.h \
    getname.h \
    common.h

FORMS    += mainwindow.ui \
    getidbox.ui \
    summary.ui \
    events.ui \
    getevent.ui \
    getname.ui


