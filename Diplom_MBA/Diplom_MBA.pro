#-------------------------------------------------
#
# Project created by QtCreator 2017-11-15T17:23:51
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dimplom_MBA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    style.cpp \
    associationrules.cpp

HEADERS  += mainwindow.h \
    database.h \
    style.h \
    associationrules.h

FORMS    += \
    mainwindow.ui

