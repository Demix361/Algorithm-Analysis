TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        controller.cpp \
        main.cpp \
        metering.cpp \
        mult_matrix.cpp \
        test.cpp

HEADERS += \
    controller.h \
    metering.h \
    mult_matrix.h \
    test.h

SUBDIRS += \
    tests.pro
