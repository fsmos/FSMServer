#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T07:58:19
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QHomeControlSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    inc/fcmprotocol.h \
    inc/fsm_electrodevice.h \
    inc/fsm_statusstruct.h

FORMS    += mainwindow.ui

RESOURCES +=

LIBS +=-L/usr/include -lfsmctl

target.path = /home/gusenkovs/FSMClient
INSTALLS += target
