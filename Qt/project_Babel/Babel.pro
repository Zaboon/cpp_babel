#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T16:15:24
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Babel
TEMPLATE = app


SOURCES += main.cpp\
        start.cpp \
    connect.cpp \
    home.cpp \
    incomingcall.cpp \
    calling.cpp

HEADERS  += start.h \
    connect.h \
    home.h \
    incomingcall.h \
    calling.h

FORMS    += start.ui \
    connect.ui \
    home.ui \
    incomingcall.ui \
    calling.ui
