TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -pthread

SOURCES += \
        main.cpp

HEADERS += \
    IsSeeUnit.hpp \
    csv.h
