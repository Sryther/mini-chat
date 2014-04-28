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
    server.cpp \
    optionswindow.cpp \
    userpersistent.cpp \
    application.cpp \
    client.cpp \
    resolver.cpp

HEADERS  += mainwindow.h \
    message.h \
    server.h \
    optionswindow.h \
    userpersistent.h \
    application.h \
    client.h \
    resolver.h

FORMS    += mainwindow.ui \
    optionswindow.ui
