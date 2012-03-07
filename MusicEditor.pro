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
    asynchronous_decode.cpp \
    QWave2/WaveformVRuler.cc \
    QWave2/WaveformSelectionProxy.cc \
    QWave2/WaveformScrollBar.cc \
    QWave2/WaveformRuler.cc \
    QWave2/WaveformRegion.cc \
    QWave2/WaveformCursorProxy.cc \
    QWave2/WaveformBar.cc \
    QWave2/Waveform.cc \
    QWave2/Utils.cc \
    QWave2/TimeLabel.cc \
    QWave2/SndFile.cc \
    QWave2/Events.cc \
    mebaseobject.cpp \
    meunity.cpp



HEADERS  += \
    mainwindow.h \
    meaudiodecoder.h \
    debug_string.h \
    ffmpeg.h \
#    AudioData.h \
    asynchronous_decode.h \
    QWave2/QWave2/WaveformVRuler.h \
    QWave2/QWave2/WaveformSelectionProxy.h \
    QWave2/QWave2/WaveformScrollBar.h \
    QWave2/QWave2/WaveformRuler.h \
    QWave2/QWave2/WaveformRegion.h \
    QWave2/QWave2/WaveformCursorProxy.h \
    QWave2/QWave2/WaveformBar.h \
    QWave2/QWave2/Waveform.h \
    QWave2/QWave2/Utils.h \
    QWave2/QWave2/TimeLabel.h \
    QWave2/QWave2/SndFile.h \
    QWave2/QWave2/qwave2defs.h \
    QWave2/QWave2/Exceptions.h \
    QWave2/QWave2/Events.h \
    mebaseobject.h \
    meunity.h

INCLUDEPATH += ./QWave2/

FORMS    +=

unix{



DEFINES += UNIX

LIBS += -L /usr/lib/


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
