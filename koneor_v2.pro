#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T14:34:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = koneor_v2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CfgForms/cgeneralcfgform.cpp \
    CfgForms/ciomodulescfgform.cpp \
    CfgForms/cgeneralweathermeasureform.cpp

HEADERS  += mainwindow.h \
    CfgForms/cgeneralcfgform.h \
    CfgForms/ciomodulescfgform.h \
    CfgForms/cgeneralweathermeasureform.h

FORMS    += mainwindow.ui \
    CfgForms/cgeneralcfgform.ui \
    CfgForms/ciomodulescfgform.ui \
    CfgForms/cgeneralweathermeasureform.ui
