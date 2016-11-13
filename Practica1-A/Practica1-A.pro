TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    kshingle.cpp \
    kshingleset.cpp \
    minhashsignatures.cpp \
    kshinglemap.cpp \
    lsh.cpp \
    kshinglesethashed.cpp \
    reader.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    kshingle.h \
    minhashsignatures.h \
    kshinglemap.h \
    kshingleset.h \
    lsh.h \
    kshinglesethashed.h \
    reader.h

