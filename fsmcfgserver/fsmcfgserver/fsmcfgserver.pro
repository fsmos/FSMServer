TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += QT_DEPRECATED_WARNINGS

unix: QMAKE_CXXFLAGS += -std=c++11
unix: QMAKE_LFLAGS_DEBUG += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    cpp/fsm_cckconfig_clientinfo.pb.cc \
    cpp/fsm_cckconfig_MN.pb.cc \
    cpp/fsm_cckconfig_MN401.pb.cc \
    cpp/fsm_cckconfig_PO.pb.cc \
    cpp/fsm_cckconfig_service.grpc.pb.cc \
    cpp/fsm_cckconfig_service.pb.cc \
    cpp/fsm_cckconfig_VirtPO.pb.cc \
    cpp/nanopb.pb.cc \
    CCKConfigServiceImpl.cpp

HEADERS += \
    cpp/fsm_cckconfig_clientinfo.pb.h \
    cpp/fsm_cckconfig_MN.pb.h \
    cpp/fsm_cckconfig_MN401.pb.h \
    cpp/fsm_cckconfig_PO.pb.h \
    cpp/fsm_cckconfig_service.grpc.pb.h \
    cpp/fsm_cckconfig_service.pb.h \
    cpp/fsm_cckconfig_VirtPO.pb.h \
    cpp/nanopb.pb.h \
    CCKConfigServiceImpl.h

PROTOC3_NAME=protoc
GRPC_PREFIX_PATH=

unix {
    GRPC_CANDIDATES = "/opt/fort" "/usr/local"
    GRPC_PREFIX_PATH=
    for(c, GRPC_CANDIDATES){
                exists($${c}/bin/$$PROTOC3_NAME){
                        GRPC_PREFIX_PATH=$${c}
                        break()
                }
        }

         isEmpty( GRPC_PREFIX_PATH ) {
            error("$$TARGET: Cannot find GRPC path")
        }
}
#specify win32 prefix path here
win32: GRPC_PREFIX_PATH="C:\\Program Files (x86)\\SOME_SDK"

!build_pass:message("$$TARGET: GRPC prefix path = $$GRPC_PREFIX_PATH")

INCLUDEPATH = "$$GRPC_PREFIX_PATH/include" $$INCLUDEPATH
win32: LIBS += -L"$$GRPC_PREFIX_PATH\win32-msvc2015\grpc" #path to libs
###error("$$INCLUDEPATH")

win32 {
  DEFINES += _WIN32_WINNT=0x600 # TODO Guess correct version
  DEFINES += _SCL_SECURE_NO_WARNINGS
  DEFINES += _CRT_SECURE_NO_WARNINGS
  QMAKE_CFLAGS_WARN_ON += -wd4100
  QMAKE_CXXFLAGS_WARN_ON += -wd4100
  QMAKE_LIBDIR = "$$GRPC_PREFIX_PATH\lib\win32-msvc2015\grpc" $${QMAKE_LIBDIR}
  LIBS *= -lgdi32
  CONFIG(debug, debug|release) {
    LIBS *= -lgrpc++d -lgprd -lgrpcd
  } else {
    LIBS *= -lgrpc++ -lgpr -lgrpc
  }

  CONFIG(debug, debug|release) {
    !win32-g++: LIBS *= -llibprotobufd
  } else {
    !win32-g++: LIBS *= -llibprotobuf
  }

  isEqual(GRPC_VERSION, "1.0") {
      LIBS *= -llibeay32 -lssleay32 -lzlib1
  }
  isEqual(GRPC_VERSION, "1.9") {
      LIBS *= -lssl -lcrypto -lzlibstatic
  }

}
unix {
  LIBS *= -L$$GRPC_PREFIX_PATH/lib/ -lgrpc++ -lgrpc \
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
           -L$$GRPC_PREFIX_PATH/lib/protobuf3 -lprotobuf -lpthread -ldl
}

LIBS *= -lfsmcck
