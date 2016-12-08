#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T22:46:59
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DGSW_project
TEMPLATE = app


SOURCES += ./app/main.cpp\
        ./app/maindlg.cpp \
    ./app/childdlg.cpp \
    ./lib/stoplanedetect.cpp

HEADERS  += ./include/maindlg.h \
    ./include/childdlg.h \
    ./include/stoplanedetect.h

FORMS    += ./app/maindlg.ui \
    ./app/childdlg.ui

INCLUDEPATH += /usr/local/include/opencv

LIBS += `pkg-config --cflags --libs opencv` \
    -lmyStoplane
