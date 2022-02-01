TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lglfw -lGL -ldl

SOURCES += \
        glad/src/glad.c \
        main.cpp \
        triangle.cpp

HEADERS += \
    glad/include/glad/glad.h \
    triangle.h
