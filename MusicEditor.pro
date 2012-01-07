#-------------------------------------------------
#
# Project created by QtCreator 2011-12-09T14:44:07
#
#-------------------------------------------------

#QT       += core gui
QT        += phonon
TARGET = MusicEditor
TEMPLATE = app

#DEFINES += FPM_DEFAULT \
#    HAVE_CONFIG_H \
#    HAVE_MPGLIB


SOURCES += main.cpp\
        mainwindow.cpp \
    ffmpeg.cpp \
    meaudiodecoder.cpp \
    meauidoencoder.cpp



HEADERS  += \
    mainwindow.h \
    meaudiodecoder.h \
    meauidoencoder.h \
    debug_string.h \
    ffmpeg.h


FORMS    +=

unix{



DEFINES += UNIX

LIBS += -L /usr/lib/ -lqwt-qt4

INCLUDEPATH += /usr/include/qwt-qt4/

LIBS += -L/usr/lib -lswscale

INCLUDEPATH += /usr/include/
DEPENDPATH += /usr/include/

LIBS += -L/usr/lib -lavutil

INCLUDEPATH += /usr/include/
DEPENDPATH += /usr/include/

LIBS += -L/usr/lib -lavformat

INCLUDEPATH += /usr/include/
DEPENDPATH += /usr/include/

LIBS += -L/usr/lib -lavfilter

INCLUDEPATH += /usr/include/
DEPENDPATH += /usr/include/

LIBS += -L/usr/lib -lavcodec

INCLUDEPATH += /usr/include/
DEPENDPATH += /usr/include/

LIBS += -L/usr/lib -lavdevice

INCLUDEPATH += /usr/include/
DEPENDPATH += /usr/include/
}
win32 {

DEFINES += WIN32
LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavcodec

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavdevice

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavfilter

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavformat

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavutil

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lswscale

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include
}
