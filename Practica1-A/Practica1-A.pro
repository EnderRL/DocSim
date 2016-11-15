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
    lsh.cpp \
    kshinglesethashed.cpp \
    reader.cpp \
    kshinglesparsematrix.cpp \
    utils.cpp \
    mainexperimentosjaccard.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    kshingle.h \
    minhashsignatures.h \
    kshingleset.h \
    lsh.h \
    kshinglesethashed.h \
    reader.h \
    utils.h \
    kshinglesparsematrix.h

