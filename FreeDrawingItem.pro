#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T15:14:22
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FreeDrawingItem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    mygraphicsview.cpp \
    FreeDrawingItem/freedrawingitem.cpp \
    FreeDrawingItem/customitem.cpp \
    FreeDrawingItem/anchorpointitem.cpp \
    FreeDrawingItem/controlpointitem.cpp \
    FreeDrawingItem/controllineitem.cpp \
    FreeDrawingItem/Command/hhcommandfreedrawingitemchange.cpp

HEADERS += \
        widget.h \
    mygraphicsview.h \
    FreeDrawingItem/freedrawingitem.h \
    FreeDrawingItem/customitem.h \
    FreeDrawingItem/anchorpointitem.h \
    FreeDrawingItem/controlpointitem.h \
    FreeDrawingItem/controllineitem.h \
    FreeDrawingItem/anchorpointinfo.h \
    FreeDrawingItem/Command/hhcommandfreedrawingitemchange.h

FORMS += \
        widget.ui
