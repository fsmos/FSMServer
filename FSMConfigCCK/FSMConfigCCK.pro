#-------------------------------------------------
#
# Project created by QtCreator 2018-08-13T11:46:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FSMConfigCCK
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix: QMAKE_CXXFLAGS += -std=c++11
unix: QMAKE_LFLAGS_DEBUG += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
    mainwindow.cpp \
    cpp/fsm_cckconfig_clientinfo.pb.cc \
    cpp/fsm_cckconfig_MN.pb.cc \
    cpp/fsm_cckconfig_MN401.pb.cc \
    cpp/fsm_cckconfig_PO.pb.cc \
    cpp/fsm_cckconfig_service.grpc.pb.cc \
    cpp/fsm_cckconfig_service.pb.cc \
    cpp/fsm_cckconfig_VirtPO.pb.cc \
    cpp/nanopb.pb.cc \
    clientcfgform.cpp \
    mn921cfg.cpp \
    abonentmncfg.cpp

FORMS    += mainwindow.ui \
    clientcfgform.ui \
    mn921cfg.ui \
    abonentmncfg.ui

RESOURCES += \
    img.qrc

include(qgrpc-master/grpc.pri)

HEADERS += \
    cpp/fsm_cckconfig_clientinfo.pb.h \
    cpp/fsm_cckconfig_MN.pb.h \
    cpp/fsm_cckconfig_MN401.pb.h \
    cpp/fsm_cckconfig_PO.pb.h \
    cpp/fsm_cckconfig_service.grpc.pb.h \
    cpp/fsm_cckconfig_service.pb.h \
    cpp/fsm_cckconfig_VirtPO.pb.h \
    cpp/nanopb.pb.h \
    mainwindow.h \
    clientcfgform.h \
    mn921cfg.h \
    abonentmncfg.h


