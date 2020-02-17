TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        controller.cpp \
        main.cpp \
        metering.cpp \
        sort.cpp \
        test.cpp

HEADERS += \
    controller.h \
    metering.h \
    sort.h \
    test.h

SUBDIRS += \
    tests.pro
