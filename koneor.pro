#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T21:08:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = koneor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eor_cfg.cpp \
    comboboxitemdelegate.cpp \
    crc16.cpp

HEADERS  += mainwindow.h \
    eor_cfg.h \
    comboboxitemdelegate.h \
    crc16.h

FORMS    += mainwindow.ui
