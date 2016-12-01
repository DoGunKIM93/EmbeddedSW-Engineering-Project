#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T22:46:59
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DGSW_project
TEMPLATE = app


SOURCES += main.cpp\
        maindlg.cpp \
    childdlg.cpp \
    stoplanedetect.cpp

HEADERS  += maindlg.h \
    childdlg.h \
    stoplanedetect.h

FORMS    += maindlg.ui \
    childdlg.ui

INCLUDEPATH += /usr/local/include/opencv

LIBS += `pkg-config --cflags --libs opencv`
