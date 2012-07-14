#-------------------------------------------------
#
# Project created by QtCreator 2012-07-11T20:58:13
#
#-------------------------------------------------

QT       += core gui network

TARGET = LanMessenger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialognickname.cpp \
    messenger.cpp \
    peer.cpp \
    pmwindow.cpp \
    roomwindow.cpp \
    dialogroom.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    dialognickname.h \
    messenger.h \
    peer.h \
    pmwindow.h \
    roomwindow.h \
    dialogroom.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    dialognickname.ui \
    pmwindow.ui \
    roomwindow.ui \
    dialogroom.ui \
    dialogabout.ui
