include (../../../caQtDM_Viewer/qtdefs.pri)
QT += core gui
CONFIG += warn_on
CONFIG += epics3_plugin
include(../../../caQtDM.pri)

TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += .
INCLUDEPATH    += ../
INCLUDEPATH    += ../../src
INCLUDEPATH    += $(EPICSINCLUDE)

HEADERS         = epics3_plugin.h ../controlsinterface.h
SOURCES         = epics3_plugin.cpp epicsSubs.c
TARGET          = epics3_plugin



