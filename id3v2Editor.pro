#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T13:25:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = id3v2Editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src\main.cpp \
        src\mainwindow.cpp \
    src\audiofilemodel.cpp \
    src\audiofile.cpp \
    src\mp3file.cpp

HEADERS += \
        inc\mainwindow.h \
    inc\audiofilemodel.h \
    inc\audiofile.h \
    inc\mp3file.h

FORMS += \
        mainwindow.ui

LIBS += -L$$PWD/libraries/taglib/taglib-release -llibtaglib
INCLUDEPATH += $$PWD/inc

INCLUDEPATH += $$PWD/libraries/taglib/taglib
INCLUDEPATH += $$PWD/libraries/taglib/taglib/toolkit
INCLUDEPATH += $$PWD/libraries/taglib

INCLUDEPATH += $$PWD/libraries/taglib/taglib/mpeg
INCLUDEPATH += $$PWD/libraries/taglib/taglib/mpeg/id3v2
INCLUDEPATH += $$PWD/libraries/taglib/taglib/mpeg/id3v2/frames

INCLUDEPATH += $$PWD/libraries/taglib/taglib/mp4
