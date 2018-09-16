QT += core network
QT -= gui widgets

DBLIBS +=

TARGET = radiodumper

PROJECT_ROOT = ..

SOURCES += main.cpp \
    dumpjob.cpp

HEADERS += \
    dumpjob.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/app.pri)
