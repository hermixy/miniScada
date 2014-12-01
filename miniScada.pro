#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T19:10:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = miniScada
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    graph.cpp \
    line.cpp \
    axis.cpp \
    grid.cpp \
    canvas.cpp \
    datadownloader.cpp \
    filereader.cpp

HEADERS  += widget.h \
    graph.h \
    line.h \
    axis.h \
    grid.h \
    canvas.h \
    datadownloader.h \
    filereader.h

FORMS    += widget.ui
