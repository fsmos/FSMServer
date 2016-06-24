QT += core #include <QtNetwork>
QT -= gui

TARGET = fsmsstd
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

target.path = /home/gusenkovs/FSMClient/bin
INSTALLS += target

