# -------------------------------------------------
# Project created by QtCreator 2011-11-19T14:06:29
# -------------------------------------------------
QT += core gui network
TARGET = geoloqi
TEMPLATE = app
SOURCES += main.cpp \
   loqiwindow.cpp \
   qgeoloqi.cpp \
   qgeoloqireply.cpp \
    authdialog.cpp
HEADERS += loqiwindow.h \
   qgeoloqi.h \
   qgeoloqireply.h \
    authdialog.h
LIBS += -lqjson
