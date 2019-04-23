#-------------------------------------------------
#
# Project created by QtCreator 2019-04-23T20:57:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyFramlessWidgetr
TEMPLATE = app

LIBS +=User32.LIB

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

