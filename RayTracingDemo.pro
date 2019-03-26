#-------------------------------------------------
#
# Project created by QtCreator 2019-03-23T19:05:45
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = RayTracingDemo
TEMPLATE = app

# OPENGL
QT   += opengl
LIBS += -lOpengl32 -lGlu32

# disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# c++ version
CONFIG += c++17

SOURCES += \
        main/main.cpp \
        main/mainwindow.cpp \
        opengl/openglwidget.cpp

HEADERS += \
        main/mainwindow.h \
        opengl/openglwidget.h \
        opengl/opengl_header.h

FORMS += \
        main/mainwindow.ui
