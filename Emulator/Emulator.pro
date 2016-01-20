#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T21:31:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Emulator
TEMPLATE = app
DEFINES += EMULATOR

include(Project.pri)
include(Arduboy.pri)

INCLUDEPATH += Platform

SOURCES += main.cpp\
    DisplayWidget.cpp \
    Emulator.cpp \
    GameInput.cpp \
    MainWindow.cpp \
    Constants.cpp

HEADERS  += \
    DisplayWidget.h \
    Emulator.h \
    GameInput.h \
    MainWindow.h \
    Constants.h

FORMS    += \
    MainWindow.ui

RESOURCES += \
    Images/images.qrc
