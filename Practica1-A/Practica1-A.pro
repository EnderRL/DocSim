TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    kshingle.cpp \
    kshingleset.cpp \
    kshinglehash.cpp \
    minhashsignatures.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    kshingle.h \
    kshingleset.h \
    kshinglehash.h \
    minhashsignatures.h

