TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix.cpp \
    vinograd.cpp

HEADERS += \
    matrix.h \
    vinograd.h

QMAKE_LFLAGS += -pthread
