#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T02:48:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dotandbox_1_1
TEMPLATE = app


SOURCES += main.cpp\
    loginwindow.cpp \
        mainwindow.cpp \
    game_window.cpp \
    map_graphics.cpp \
    level_window.cpp \
    signup.cpp

HEADERS  += mainwindow.h \
    game_window.h \
    loginwindow.h \
    map_graphics.h \
    level_window.h \
    signup.h

FORMS    += mainwindow.ui \
    game_window.ui \
    level_window.ui \
    loginwindow.ui \
    signup.ui

RESOURCES += \
    res.qrc

