QT += core network
QT -= gui

TARGET = fsmced
CONFIG += console static
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
HEADERS +=
LIBS += -L/usr/lib -lfsmctl

INCLUDEPATH += /usr/include
DEPENDPATH += /usr/include

target.path = /home/gusenkovs/FSMClient/bin
INSTALLS += target
