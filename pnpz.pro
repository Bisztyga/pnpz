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
    asyncinotify.cpp

HEADERS  += mainwindow.h \
    asyncinotify.h

FORMS    += mainwindow.ui
