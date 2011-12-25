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
    OtherClass/ffmpeg.h \
    mainwindow.h \
    meaudiodecoder.h \
    meauidoencoder.h


FORMS    +=




win32: LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavcodec

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

win32: LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavdevice

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

win32: LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavfilter

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

win32: LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavformat

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

win32: LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lavutil

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include

win32: LIBS += -L$$PWD/FFmpeg-full-SDK-3.2/lib/ -lswscale

INCLUDEPATH += $$PWD/FFmpeg-full-SDK-3.2/include
DEPENDPATH += $$PWD/FFmpeg-full-SDK-3.2/include




































