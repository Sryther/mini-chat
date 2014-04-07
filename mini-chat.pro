#-------------------------------------------------
#
# Project created by QtCreator 2014-03-17T13:05:42
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mini-chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    message.cpp \
    optionswindow.cpp \
    userpersistent.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    message.h \
    optionswindow.h \
    userpersistent.h \
    user.h

FORMS    += mainwindow.ui \
    optionswindow.ui
