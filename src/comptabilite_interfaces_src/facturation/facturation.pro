######################################################################
# Automatically generated by qmake (2.01a) sam. mai 11 10:10:05 2013
######################################################################

TEMPLATE = app
TARGET = facturation

DEPENDPATH += $$PWD
INCLUDEPATH += .
include(../../../buildspecs/config.pri)
DESTDIR = $$BUILD_BINARY_PATH
include($$PWD/../../common/common.pri)
include($$PWD/../../common/configure/configure.pri)
include($$PWD/facturation.pri)

SOURCES += $${PWD}/main.cpp

QT+=sql
