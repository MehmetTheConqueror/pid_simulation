#-------------------------------------------------
#
# Project created by QtCreator 2019-09-29T01:32:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PID
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pid.c

HEADERS  += mainwindow.h \
    pid.h

FORMS    += mainwindow.ui
