#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T15:46:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mysqlview
TEMPLATE = app
QT           += sql

SOURCES += main.cpp\
        mysqlview.cpp

HEADERS  += mysqlview.h \
    GBK.h

FORMS    += mysqlview.ui

RESOURCES += \
    images.qrc
