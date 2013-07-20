#-------------------------------------------------
#
# Project created by QtCreator 2012-07-11T20:58:13
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LanMessenger-VOIP
TEMPLATE = app

CONFIG += release
QMAKE_CXXFLAGS += -std=c++0x

# STATIC LINKING
CONFIG += static
QMAKE_CXXFLAGS += -static -static-libgcc -static-libstdc++
QMAKE_LFLAGS   += -static -static-libgcc -static-libstdc++

SOURCES += main.cpp\
        mainwindow.cpp \
    dialognickname.cpp \
    messenger.cpp \
    peer.cpp \
    pmwindow.cpp \
    roomwindow.cpp \
    dialogroom.cpp \
    dialogabout.cpp \
    voice/voicesocket.cpp \
    voice/voiceio.cpp \
    voice/codec.cpp \
    voice/buffer.cpp \
    voice/codecs/dummycodec.cpp \
    voice/codecs/dpcm.cpp

HEADERS  += mainwindow.h \
    dialognickname.h \
    messenger.h \
    peer.h \
    pmwindow.h \
    roomwindow.h \
    dialogroom.h \
    dialogabout.h \
    voice/voicesocket.h \
    voice/voiceio.h \
    voice/codec.h \
    voice/buffer.h \
    voice/codecs/dummycodec.h \
    voice/codecs/dpcm.h

FORMS    += mainwindow.ui \
    dialognickname.ui \
    pmwindow.ui \
    roomwindow.ui \
    dialogroom.ui \
    dialogabout.ui
