#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T14:34:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = koneor_v2
TEMPLATE = app

QMAKE_CXXFLAGS += -mno-ms-bitfields

SOURCES += main.cpp\
        mainwindow.cpp \
    CfgForms/cgeneralcfgform.cpp \
    CfgForms/ciomodulescfgform.cpp \
    CfgForms/cgeneralweathermeasureform.cpp \
    CfgForms/cweatherautomform.cpp \
    CfgForms/ctemperaturescfgform.cpp \
    CfgForms/ccircuitcfgform.cpp \
    CfgForms/ciocfgform.cpp \
    CfgForms/cuserscfgform.cpp \
    CfgForms/crs232cfgform.cpp \
    CfgForms/cmodbusslavecfgform.cpp \
    CfgForms/ccancfgform.cpp \
    eor_cfg.cpp \
    CfgForms/cethernetcfgform.cpp \
    CfgForms/cmyform.cpp \
    crc16.cpp

HEADERS  += mainwindow.h \
    CfgForms/cgeneralcfgform.h \
    CfgForms/ciomodulescfgform.h \
    CfgForms/cgeneralweathermeasureform.h \
    CfgForms/cweatherautomform.h \
    CfgForms/ctemperaturescfgform.h \
    eor_cfg.hpp \
    CfgForms/ccircuitcfgform.h \
    CfgForms/ciocfgform.h \
    CfgForms/cuserscfgform.h \
    CfgForms/crs232cfgform.h \
    CfgForms/cmodbusslavecfgform.h \
    CfgForms/ccancfgform.h \
    CfgForms/cethernetcfgform.h \
    CfgForms/cmyform.h \
    crc16.hpp

FORMS    += mainwindow.ui \
    CfgForms/cgeneralcfgform.ui \
    CfgForms/ciomodulescfgform.ui \
    CfgForms/cgeneralweathermeasureform.ui \
    CfgForms/cweatherautomform.ui \
    CfgForms/ctemperaturescfgform.ui \
    CfgForms/ccircuitcfgform.ui \
    CfgForms/ciocfgform.ui \
    CfgForms/cuserscfgform.ui \
    CfgForms/crs232cfgform.ui \
    CfgForms/cmodbusslavecfgform.ui \
    CfgForms/ccancfgform.ui \
    CfgForms/cethernetcfgform.ui
